


#define TRACE_LEVEL SCP_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_connection.h"
#include "ssh/ssh_request.h"
#include "ssh/ssh_misc.h"
#include "scp/scp_client.h"
#include "scp/scp_client_misc.h"
#include "debug.h"


#if (SCP_CLIENT_SUPPORT == ENABLED)




void scpClientChangeState(ScpClientContext *context,
   ScpClientState newState)
{
   
   context->state = newState;

   
   context->timestamp = osGetSystemTime();
}




error_t scpClientOpenConnection(ScpClientContext *context)
{
   error_t error;
   Socket *socket;
   SshConnection *connection;

   
   error = sshInit(&context->sshContext, &context->sshConnection, 1,
      &context->sshChannel, 1);
   
   if(error)
      return error;

   
   error = sshSetOperationMode(&context->sshContext, SSH_OPERATION_MODE_CLIENT);
   
   if(error)
      return error;

   
   if(context->sshInitCallback != NULL)
   {
      
      error = context->sshInitCallback(context, &context->sshContext);
      
      if(error)
         return error;
   }

   
   socket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);

   
   if(socket != NULL)
   {
      
      socketBindToInterface(socket, context->interface);
      
      socketSetTimeout(socket, context->timeout);

      
      connection = sshOpenConnection(&context->sshContext, socket);

      
      if(connection == NULL)
      {
         
         socketClose(socket);
         
         error = ERROR_OPEN_FAILED;
      }
   }
   else
   {
      
      error = ERROR_OPEN_FAILED;
   }

   
   return error;
}




error_t scpClientEstablishConnection(ScpClientContext *context)
{
   error_t error;

   
   if(context->sshConnection.state < SSH_CONN_STATE_OPEN)
   {
      
      error = scpClientProcessEvents(context);
   }
   else if(context->sshConnection.state == SSH_CONN_STATE_OPEN)
   {
      
      scpClientChangeState(context, SCP_CLIENT_STATE_CONNECTED);
      
      error = NO_ERROR;
   }
   else
   {
      
      error = ERROR_WRONG_STATE;
   }

   
   return error;
}




void scpClientCloseConnection(ScpClientContext *context)
{
   
   if(context->sshConnection.state != SSH_CONN_STATE_CLOSED)
   {
      
      sshCloseConnection(&context->sshConnection);
   }

   
   sshDeinit(&context->sshContext);
}




error_t scpClientSendDirective(ScpClientContext *context,
   const ScpDirective *directive)
{
   error_t error;
   size_t n;

   
   error = NO_ERROR;

   
   while(!error)
   {
      
      if(context->bufferLen == 0)
      {
         
         n = scpFormatDirective(directive, context->buffer);

         
         context->bufferLen = n;
         context->bufferPos = 0;
      }
      else if(context->bufferPos < context->bufferLen)
      {
         
         error = sshWriteChannel(&context->sshChannel,
            context->buffer + context->bufferPos,
            context->bufferLen - context->bufferPos, &n, 0);

         
         if(error == NO_ERROR || error == ERROR_TIMEOUT)
         {
            
            context->bufferPos += n;
         }
      }
      else
      {
         
         context->bufferLen = 0;
         context->bufferPos = 0;

         
         break;
      }

      
      if(error == ERROR_WOULD_BLOCK || error == ERROR_TIMEOUT)
      {
         
         error = scpClientProcessEvents(context);
      }
   }

   
   return error;
}




error_t scpClientReceiveDirective(ScpClientContext *context,
   ScpDirective *directive)
{
   error_t error;
   size_t n;
   uint8_t opcode;

   
   error = NO_ERROR;

   
   while(!error)
   {
      
      if(context->bufferLen == 0)
      {
         
         error = sshReadChannel(&context->sshChannel, context->buffer, 1,
            &n, 0);

         
         if(!error)
         {
            
            context->bufferLen += n;
         }
      }
      else if(context->bufferLen < SCP_CLIENT_BUFFER_SIZE)
      {
         
         opcode = context->buffer[0];

         
         if(opcode == SCP_OPCODE_OK ||
            opcode == SCP_OPCODE_END)
         {
            
            error = scpParseDirective(context->buffer, directive);

            
            context->bufferLen = 0;
            context->bufferPos = 0;

            
            break;
         }
         else if(opcode == SCP_OPCODE_WARNING ||
            opcode == SCP_OPCODE_ERROR ||
            opcode == SCP_OPCODE_FILE ||
            opcode == SCP_OPCODE_DIR ||
            opcode == SCP_OPCODE_TIME)
         {
            
            n = SCP_CLIENT_BUFFER_SIZE - context->bufferLen;

            
            error = sshReadChannel(&context->sshChannel, context->buffer +
               context->bufferLen, n, &n, SSH_FLAG_BREAK_CRLF);

            
            if(!error)
            {
               
               context->bufferLen += n;

               
               if(context->bufferLen > 0 &&
                  context->buffer[context->bufferLen - 1] == '\n')
               {
                  
                  context->buffer[context->bufferLen - 1] = '\0';

                  
                  error = scpParseDirective(context->buffer, directive);

                  
                  context->bufferLen = 0;
                  context->bufferPos = 0;

                  
                  break;
               }
               else
               {
                  
                  error = ERROR_WOULD_BLOCK;
               }
            }
         }
         else
         {
            
            error = ERROR_INVALID_COMMAND;
         }
      }
      else
      {
         
         error = ERROR_BUFFER_OVERFLOW;
      }

      
      if(error == ERROR_WOULD_BLOCK || error == ERROR_TIMEOUT)
      {
         
         error = scpClientProcessEvents(context);
      }
   }

   
   return error;
}




error_t scpClientProcessEvents(ScpClientContext *context)
{
   error_t error;
   uint_t i;
   SshContext *sshContext;
   SshConnection *connection;

   
   sshContext = &context->sshContext;

   
   osMemset(sshContext->eventDesc, 0, sizeof(sshContext->eventDesc));

   
   for(i = 0; i < sshContext->numConnections; i++)
   {
      
      connection = &sshContext->connections[i];

      
      if(connection->state != SSH_CONN_STATE_CLOSED)
      {
         
         sshRegisterConnectionEvents(sshContext, connection, &sshContext->eventDesc[i]);
      }
   }

   
   error = socketPoll(sshContext->eventDesc, sshContext->numConnections,
      &sshContext->event, context->timeout);

   
   if(!error)
   {
      
      for(i = 0; i < sshContext->numConnections && !error; i++)
      {
         
         connection = &sshContext->connections[i];

         
         if(connection->state != SSH_CONN_STATE_CLOSED)
         {
            
            if(sshContext->eventDesc[i].eventFlags != 0)
            {
               
               error = sshProcessConnectionEvents(sshContext, connection);
            }
         }
      }
   }

   
   if(error == ERROR_WOULD_BLOCK || error == ERROR_TIMEOUT)
   {
      
      error = scpClientCheckTimeout(context);
   }

   
   return error;
}




error_t scpClientCheckTimeout(ScpClientContext *context)
{
   error_t error;
   systime_t time;

   
   time = osGetSystemTime();

   
   if(timeCompare(time, context->timestamp + context->timeout) >= 0)
   {
      
      error = ERROR_TIMEOUT;
   }
   else
   {
#if (NET_RTOS_SUPPORT == ENABLED)
      
      error = NO_ERROR;
#else
      
      error = ERROR_WOULD_BLOCK;
#endif
   }

   
   return error;
}

#endif
