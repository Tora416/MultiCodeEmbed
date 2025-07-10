


#define TRACE_LEVEL SSH_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_misc.h"
#include "ssh/ssh_server.h"
#include "ssh/ssh_server_misc.h"
#include "debug.h"


#if (SSH_SUPPORT == ENABLED && SSH_SERVER_SUPPORT == ENABLED)




void sshServerGetDefaultSettings(SshServerSettings *settings)
{
   
   settings->interface = NULL;

   
   settings->port = SSH_PORT;

   
   settings->numConnections = 0;
   settings->connections = NULL;

   
   settings->numChannels = 0;
   settings->channels = NULL;

   
   settings->prngAlgo = NULL;
   settings->prngContext = NULL;

   
   settings->passwordAuthCallback = NULL;
   
   settings->publicKeyAuthCallback = NULL;
}




error_t sshServerInit(SshServerContext *context,
   const SshServerSettings *settings)
{
   error_t error;

   
   TRACE_INFO("Initializing SSH server...\r\n");

   
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   
   if(settings->numConnections < 1 ||
      settings->numConnections > SSH_MAX_CONNECTIONS)
   {
      return ERROR_INVALID_PARAMETER;
   }

   
   if(settings->numChannels < settings->numConnections)
      return ERROR_INVALID_PARAMETER;

   
   error = sshInit(&context->sshContext, settings->connections,
      settings->numConnections, settings->channels, settings->numChannels);
   
   if(error)
      return error;

   
   context->interface = settings->interface;
   context->port = settings->port;

   
   do
   {
      
      error = sshSetOperationMode(&context->sshContext,
         SSH_OPERATION_MODE_SERVER);
      
      if(error)
         break;

      
      error = sshSetPrng(&context->sshContext, settings->prngAlgo,
         settings->prngContext);
      
      if(error)
         break;

      
      if(settings->passwordAuthCallback != NULL)
      {
         
         error = sshRegisterPasswordAuthCallback(&context->sshContext,
            settings->passwordAuthCallback);
         
         if(error)
            break;
      }

      
      if(settings->publicKeyAuthCallback != NULL)
      {
         
         error = sshRegisterPublicKeyAuthCallback(&context->sshContext,
            settings->publicKeyAuthCallback);
         
         if(error)
            break;
      }

      
   } while(0);

   
   if(error)
   {
      
      sshServerDeinit(context);
   }

   
   return error;
}




error_t sshServerRegisterGlobalRequestCallback(SshServerContext *context,
   SshGlobalReqCallback callback, void *param)
{
   
   return sshRegisterGlobalRequestCallback(&context->sshContext, callback,
      param);
}




error_t sshServerUnregisterGlobalRequestCallback(SshServerContext *context,
   SshGlobalReqCallback callback)
{
   
   return sshUnregisterGlobalRequestCallback(&context->sshContext, callback);
}




error_t sshServerRegisterChannelRequestCallback(SshServerContext *context,
   SshChannelReqCallback callback, void *param)
{
   
   return sshRegisterChannelRequestCallback(&context->sshContext, callback,
      param);
}




error_t sshServerUnregisterChannelRequestCallback(SshServerContext *context,
   SshChannelReqCallback callback)
{
   
   return sshUnregisterChannelRequestCallback(&context->sshContext, callback);
}




error_t sshServerLoadHostKey(SshServerContext *context, const char_t *publicKey,
   size_t publicKeyLen, const char_t *privateKey, size_t privateKeyLen)
{
   error_t error;

   
   if(!context->running)
   {
      
      error = sshLoadHostKey(&context->sshContext, publicKey, publicKeyLen,
         privateKey, privateKeyLen);
   }
   else
   {
      
      error = ERROR_WRONG_STATE;
   }

   
   return error;
}




error_t sshServerUnloadAllHostKeys(SshServerContext *context)
{
   error_t error;

   
   if(!context->running)
   {
      
      error = sshUnloadAllHostKeys(&context->sshContext);
   }
   else
   {
      
      error = ERROR_WRONG_STATE;
   }

   
   return error;
}




error_t sshServerStart(SshServerContext *context)
{
   error_t error;
   OsTask *task;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   TRACE_INFO("Starting SSH server...\r\n");

   
   if(context->running)
      return ERROR_ALREADY_RUNNING;

   
   do
   {
      
      context->socket = socketOpen(SOCKET_TYPE_STREAM, SOCKET_IP_PROTO_TCP);

      
      if(context->socket == NULL)
      {
         
         error = ERROR_OPEN_FAILED;
         
         break;
      }

      
      error = socketSetTimeout(context->socket, 0);
      
      if(error)
         break;

      
      error = socketBindToInterface(context->socket, context->interface);
      
      if(error)
         break;

      
      error = socketBind(context->socket, &IP_ADDR_ANY, context->port);
      
      if(error)
         break;

      
      error = socketListen(context->socket, 0);
      
      if(error)
         break;

      
      context->stop = FALSE;
      context->running = TRUE;

      
      task = osCreateTask("SSH Server", (OsTaskCode) sshServerTask, context,
         SSH_SERVER_STACK_SIZE, SSH_SERVER_PRIORITY);
      
      if(task == OS_INVALID_HANDLE)
      {
         
         error = ERROR_OUT_OF_RESOURCES;
         break;
      }

      
   } while(0);

   
   if(error)
   {
      
      context->running = FALSE;
      
      socketClose(context->socket);
   }

   
   return error;
}




error_t sshServerStop(SshServerContext *context)
{
   uint_t i;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   TRACE_INFO("Stopping SSH server...\r\n");

   
   if(context->running)
   {
      
      context->stop = TRUE;
      
      sshNotifyEvent(&context->sshContext);

      
      while(context->running)
      {
         osDelayTask(1);
      }

      
      for(i = 0; i < context->sshContext.numConnections; i++)
      {
         
         if(context->sshContext.connections[i].state != SSH_CONN_STATE_CLOSED)
         {
            
            sshCloseConnection(&context->sshContext.connections[i]);
         }
      }

      
      socketClose(context->socket);
      context->socket = NULL;
   }

   
   return NO_ERROR;
}




void sshServerTask(SshServerContext *context)
{
   error_t error;
   uint_t i;
   SshContext *sshContext;
   SshConnection *connection;

   
   sshContext = &context->sshContext;

#if (NET_RTOS_SUPPORT == ENABLED)
   
   osEnterTask();

   
   while(1)
   {
#endif
      
      osMemset(sshContext->eventDesc, 0, sizeof(sshContext->eventDesc));

      
      for(i = 0; i < sshContext->numConnections; i++)
      {
         
         connection = &sshContext->connections[i];

         
         if(connection->state != SSH_CONN_STATE_CLOSED)
         {
            
            sshRegisterConnectionEvents(sshContext, connection,
               &sshContext->eventDesc[i]);
         }
      }

      
      sshContext->eventDesc[i].socket = context->socket;
      sshContext->eventDesc[i].eventMask = SOCKET_EVENT_ACCEPT;

      
      error = socketPoll(sshContext->eventDesc, sshContext->numConnections + 1,
         &sshContext->event, SSH_SERVER_TICK_INTERVAL);

      
      if(error == NO_ERROR || error == ERROR_TIMEOUT)
      {
         
         if(context->stop)
         {
            
            context->running = FALSE;
            
            osDeleteTask(NULL);
         }

         
         for(i = 0; i < sshContext->numConnections; i++)
         {
            
            connection = &sshContext->connections[i];

            
            if(connection->state != SSH_CONN_STATE_CLOSED)
            {
               
               if(sshContext->eventDesc[i].eventFlags != 0)
               {
                  
                  error = sshProcessConnectionEvents(sshContext, connection);

                  
                  if(error != NO_ERROR && error != ERROR_TIMEOUT)
                  {
                     
                     sshCloseConnection(connection);
                  }
               }
            }
         }

         
         if(sshContext->eventDesc[i].eventFlags != 0)
         {
            
            sshServerAcceptConnection(context);
         }
      }

      
      sshServerTick(context);

#if (NET_RTOS_SUPPORT == ENABLED)
   }
#endif
}




void sshServerDeinit(SshServerContext *context)
{
   
   if(context != NULL)
   {
      
      socketClose(context->socket);

      
      sshDeinit(&context->sshContext);

      
      osMemset(context, 0, sizeof(SshServerContext));
   }
}

#endif
