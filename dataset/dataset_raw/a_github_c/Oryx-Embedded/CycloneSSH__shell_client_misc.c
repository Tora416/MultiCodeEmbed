


#define TRACE_LEVEL SHELL_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_connection.h"
#include "ssh/ssh_request.h"
#include "ssh/ssh_misc.h"
#include "shell/shell_client.h"
#include "shell/shell_client_misc.h"
#include "debug.h"


#if (SHELL_CLIENT_SUPPORT == ENABLED)




void shellClientChangeState(ShellClientContext *context,
   ShellClientState newState)
{
   
   context->state = newState;

   
   context->timestamp = osGetSystemTime();
}




error_t shellClientChannelRequestCallback(SshChannel *channel,
   const SshString *type, const uint8_t *data, size_t length,
   void *param)
{
   error_t error;
   ShellClientContext *context;

   
   TRACE_INFO("Shell client: SSH channel request callback...\r\n");

   
   context = (ShellClientContext *) param;

   
   if(sshCompareString(type, "exit-status"))
   {
      SshExitStatusReqParams requestParams;

      
      
      
      error = sshParseExitStatusReqParams(data, length, &requestParams);

      
      if(!error)
      {
         
         if(channel == &context->sshChannel)
         {
            
            context->exitStatus = requestParams.exitStatus;
         }
         else
         {
            
            error = ERROR_UNKNOWN_REQUEST;
         }
      }
   }
   else
   {
      
      error = ERROR_UNKNOWN_REQUEST;
   }

   
   return error;
}




error_t shellClientOpenConnection(ShellClientContext *context)
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

   
   error = sshRegisterChannelRequestCallback(&context->sshContext,
      shellClientChannelRequestCallback, context);
   
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




error_t shellClientEstablishConnection(ShellClientContext *context)
{
   error_t error;

   
   if(context->sshConnection.state < SSH_CONN_STATE_OPEN)
   {
      
      error = shellClientProcessEvents(context);
   }
   else if(context->sshConnection.state == SSH_CONN_STATE_OPEN)
   {
      
      shellClientChangeState(context, SHELL_CLIENT_STATE_CONNECTED);
      
      error = NO_ERROR;
   }
   else
   {
      
      error = ERROR_WRONG_STATE;
   }

   
   return error;
}




void shellClientCloseConnection(ShellClientContext *context)
{
   
   if(context->sshConnection.state != SSH_CONN_STATE_CLOSED)
   {
      
      sshCloseConnection(&context->sshConnection);
   }

   
   sshDeinit(&context->sshContext);
}




error_t shellClientProcessEvents(ShellClientContext *context)
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
      
      error = shellClientCheckTimeout(context);
   }

   
   return error;
}




error_t shellClientCheckTimeout(ShellClientContext *context)
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
