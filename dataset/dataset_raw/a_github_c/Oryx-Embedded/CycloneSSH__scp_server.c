


#define TRACE_LEVEL SCP_TRACE_LEVEL


#include "ssh/ssh.h"
#include "scp/scp_server.h"
#include "scp/scp_server_misc.h"
#include "path.h"
#include "debug.h"


#if (SCP_SERVER_SUPPORT == ENABLED)




void scpServerGetDefaultSettings(ScpServerSettings *settings)
{
   
   settings->sshServerContext = NULL;

   
   settings->numSessions = 0;
   settings->sessions = NULL;

   
   settings->rootDir = NULL;

   
   settings->checkUserCallback = NULL;
   
   settings->getFilePermCallback = NULL;
}




error_t scpServerInit(ScpServerContext *context,
   const ScpServerSettings *settings)
{
   uint_t i;

   
   TRACE_INFO("Initializing SCP server...\r\n");

   
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   
   if(settings->sessions == NULL || settings->numSessions < 1 ||
      settings->numSessions > SCP_SERVER_MAX_SESSIONS)
   {
      return ERROR_INVALID_PARAMETER;
   }

   
   if(settings->rootDir == NULL ||
      osStrlen(settings->rootDir) > SCP_SERVER_MAX_ROOT_DIR_LEN)
   {
      return ERROR_INVALID_PARAMETER;
   }

   
   osMemset(context, 0, sizeof(ScpServerContext));

   
   context->sshServerContext = settings->sshServerContext;
   context->numSessions = settings->numSessions;
   context->sessions = settings->sessions;
   context->checkUserCallback = settings->checkUserCallback;
   context->getFilePermCallback = settings->getFilePermCallback;

   
   osStrcpy(context->rootDir, settings->rootDir);

   
   pathCanonicalize(context->rootDir);
   pathRemoveSlash(context->rootDir);

   
   for(i = 0; i < context->numSessions; i++)
   {
      
      osMemset(&context->sessions[i], 0, sizeof(ScpServerSession));
   }

   
   if(!osCreateEvent(&context->event))
   {
      
      scpServerDeinit(context);
   }

   
   return NO_ERROR;
}




error_t scpServerStart(ScpServerContext *context)
{
   error_t error;
   OsTask *task;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   TRACE_INFO("Starting SCP server...\r\n");

   
   if(context->running)
      return ERROR_ALREADY_RUNNING;

   
   error = sshServerRegisterChannelRequestCallback(context->sshServerContext,
      scpServerChannelRequestCallback, context);

   
   if(!error)
   {
      
      context->stop = FALSE;
      context->running = TRUE;

      
      task = osCreateTask("SCP Server", scpServerTask, context,
         SCP_SERVER_STACK_SIZE, SCP_SERVER_PRIORITY);
      
      if(task == OS_INVALID_HANDLE)
      {
         error = ERROR_OUT_OF_RESOURCES;
      }
   }

   
   if(error)
   {
      
      context->running = FALSE;

      
      sshServerUnregisterChannelRequestCallback(context->sshServerContext,
         scpServerChannelRequestCallback);
   }

   
   return error;
}




error_t scpServerStop(ScpServerContext *context)
{
   uint_t i;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   TRACE_INFO("Stopping SCP server...\r\n");

   
   if(context->running)
   {
      
      sshServerUnregisterChannelRequestCallback(context->sshServerContext,
         scpServerChannelRequestCallback);

      
      context->stop = TRUE;
      
      osSetEvent(&context->event);

      
      while(context->running)
      {
         osDelayTask(1);
      }

      
      for(i = 0; i < context->numSessions; i++)
      {
         
         if(context->sessions[i].state != SCP_SERVER_SESSION_STATE_CLOSED)
         {
            
            scpServerCloseSession(&context->sessions[i]);
         }
      }
   }

   
   return NO_ERROR;
}




error_t scpServerSetRootDir(ScpServerSession *session, const char_t *rootDir)
{
   ScpServerContext *context;

   
   if(session == NULL || rootDir == NULL)
      return ERROR_INVALID_PARAMETER;

   
   context = session->context;

   
   pathCopy(session->rootDir, context->rootDir, SCP_SERVER_MAX_ROOT_DIR_LEN);
   pathCombine(session->rootDir, rootDir, SCP_SERVER_MAX_ROOT_DIR_LEN);

   
   pathCanonicalize(session->rootDir);
   pathRemoveSlash(session->rootDir);

   
   pathCopy(session->homeDir, session->rootDir, SCP_SERVER_MAX_HOME_DIR_LEN);

   
   return NO_ERROR;
}




error_t scpServerSetHomeDir(ScpServerSession *session, const char_t *homeDir)
{
   ScpServerContext *context;

   
   if(session == NULL || homeDir == NULL)
      return ERROR_INVALID_PARAMETER;

   
   context = session->context;

   
   pathCopy(session->homeDir, context->rootDir, SCP_SERVER_MAX_HOME_DIR_LEN);
   pathCombine(session->homeDir, homeDir, SCP_SERVER_MAX_HOME_DIR_LEN);

   
   pathCanonicalize(session->homeDir);
   pathRemoveSlash(session->homeDir);

   
   return NO_ERROR;
}




void scpServerTask(void *param)
{
   error_t error;
   uint_t i;
   systime_t timeout;
   ScpServerContext *context;
   ScpServerSession *session;

   
   context = (ScpServerContext *) param;

#if (NET_RTOS_SUPPORT == ENABLED)
   
   osEnterTask();

   
   while(1)
   {
#endif
      
      timeout = SCP_SERVER_TICK_INTERVAL;

      
      osMemset(context->eventDesc, 0, sizeof(context->eventDesc));

      
      for(i = 0; i < context->numSessions; i++)
      {
         
         session = &context->sessions[i];

         
         if(session->state != SCP_SERVER_SESSION_STATE_CLOSED)
         {
            
            scpServerRegisterSessionEvents(session, &context->eventDesc[i]);

            
            if(context->eventDesc[i].eventFlags != 0)
            {
               
               timeout = 0;
            }
         }
      }

      
      error = sshPollChannels(context->eventDesc, context->numSessions,
         &context->event, timeout);

      
      if(error == NO_ERROR || error == ERROR_TIMEOUT)
      {
         
         if(context->stop)
         {
            
            context->running = FALSE;
            
            osDeleteTask(NULL);
         }

         
         for(i = 0; i < context->numSessions; i++)
         {
            
            session = &context->sessions[i];

            
            if(session->state != SCP_SERVER_SESSION_STATE_CLOSED)
            {
               
               if(context->eventDesc[i].eventFlags != 0)
               {
                  
                  scpServerProcessSessionEvents(session);
               }
            }
         }
      }

      
      scpServerTick(context);

#if (NET_RTOS_SUPPORT == ENABLED)
   }
#endif
}




void scpServerDeinit(ScpServerContext *context)
{
   
   if(context != NULL)
   {
      
      osDeleteEvent(&context->event);

      
      osMemset(context, 0, sizeof(ScpServerContext));
   }
}

#endif
