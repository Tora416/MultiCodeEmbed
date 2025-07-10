


#define TRACE_LEVEL SFTP_TRACE_LEVEL


#include "ssh/ssh.h"
#include "sftp/sftp_server.h"
#include "sftp/sftp_server_misc.h"
#include "path.h"
#include "debug.h"


#if (SFTP_SERVER_SUPPORT == ENABLED)




void sftpServerGetDefaultSettings(SftpServerSettings *settings)
{
   
   settings->sshServerContext = NULL;

   
   settings->numSessions = 0;
   settings->sessions = NULL;

   
   settings->numFileObjects = 0;
   settings->fileObjects = NULL;

   
   settings->rootDir = NULL;

   
   settings->checkUserCallback = NULL;
   
   settings->getFilePermCallback = NULL;
}




error_t sftpServerInit(SftpServerContext *context,
   const SftpServerSettings *settings)
{
   uint_t i;

   
   TRACE_INFO("Initializing SFTP server...\r\n");

   
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   
   if(settings->sessions == NULL || settings->numSessions < 1 ||
      settings->numSessions > SFTP_SERVER_MAX_SESSIONS)
   {
      return ERROR_INVALID_PARAMETER;
   }

   
   if(settings->fileObjects == NULL || settings->numFileObjects < 1)
   {
      return ERROR_INVALID_PARAMETER;
   }

   
   if(settings->rootDir == NULL ||
      osStrlen(settings->rootDir) > SFTP_SERVER_MAX_ROOT_DIR_LEN)
   {
      return ERROR_INVALID_PARAMETER;
   }

   
   osMemset(context, 0, sizeof(SftpServerContext));

   
   context->sshServerContext = settings->sshServerContext;
   context->numSessions = settings->numSessions;
   context->sessions = settings->sessions;
   context->numFileObjects = settings->numFileObjects;
   context->fileObjects = settings->fileObjects;
   context->checkUserCallback = settings->checkUserCallback;
   context->getFilePermCallback = settings->getFilePermCallback;

   
   osStrcpy(context->rootDir, settings->rootDir);

   
   pathCanonicalize(context->rootDir);
   pathRemoveSlash(context->rootDir);

   
   for(i = 0; i < context->numSessions; i++)
   {
      
      osMemset(&context->sessions[i], 0, sizeof(SftpServerSession));
   }

   
   for(i = 0; i < context->numFileObjects; i++)
   {
      
      osMemset(&context->fileObjects[i], 0, sizeof(SftpFileObject));
   }

   
   if(!osCreateEvent(&context->event))
   {
      
      sftpServerDeinit(context);
   }

   
   return NO_ERROR;
}




error_t sftpServerStart(SftpServerContext *context)
{
   error_t error;
   OsTask *task;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   TRACE_INFO("Starting SFTP server...\r\n");

   
   if(context->running)
      return ERROR_ALREADY_RUNNING;

   
   error = sshServerRegisterChannelRequestCallback(context->sshServerContext,
      sftpServerChannelRequestCallback, context);

   
   if(!error)
   {
      
      context->stop = FALSE;
      context->running = TRUE;

      
      task = osCreateTask("SFTP Server", sftpServerTask, context,
         SFTP_SERVER_STACK_SIZE, SFTP_SERVER_PRIORITY);
      
      if(task == OS_INVALID_HANDLE)
      {
         error = ERROR_OUT_OF_RESOURCES;
      }
   }

   
   if(error)
   {
      
      context->running = FALSE;

      
      sshServerUnregisterChannelRequestCallback(context->sshServerContext,
         sftpServerChannelRequestCallback);
   }

   
   return error;
}




error_t sftpServerStop(SftpServerContext *context)
{
   uint_t i;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   TRACE_INFO("Stopping SFTP server...\r\n");

   
   if(context->running)
   {
      
      sshServerUnregisterChannelRequestCallback(context->sshServerContext,
         sftpServerChannelRequestCallback);

      
      context->stop = TRUE;
      
      osSetEvent(&context->event);

      
      while(context->running)
      {
         osDelayTask(1);
      }

      
      for(i = 0; i < context->numSessions; i++)
      {
         
         if(context->sessions[i].state != SFTP_SERVER_SESSION_STATE_CLOSED)
         {
            
            sftpServerCloseSession(&context->sessions[i]);
         }
      }
   }

   
   return NO_ERROR;
}




error_t sftpServerSetRootDir(SftpServerSession *session, const char_t *rootDir)
{
   SftpServerContext *context;

   
   if(session == NULL || rootDir == NULL)
      return ERROR_INVALID_PARAMETER;

   
   context = session->context;

   
   pathCopy(session->rootDir, context->rootDir, SFTP_SERVER_MAX_ROOT_DIR_LEN);
   pathCombine(session->rootDir, rootDir, SFTP_SERVER_MAX_ROOT_DIR_LEN);

   
   pathCanonicalize(session->rootDir);
   pathRemoveSlash(session->rootDir);

   
   pathCopy(session->homeDir, session->rootDir, SFTP_SERVER_MAX_HOME_DIR_LEN);

   
   return NO_ERROR;
}




error_t sftpServerSetHomeDir(SftpServerSession *session, const char_t *homeDir)
{
   SftpServerContext *context;

   
   if(session == NULL || homeDir == NULL)
      return ERROR_INVALID_PARAMETER;

   
   context = session->context;

   
   pathCopy(session->homeDir, context->rootDir, SFTP_SERVER_MAX_HOME_DIR_LEN);
   pathCombine(session->homeDir, homeDir, SFTP_SERVER_MAX_HOME_DIR_LEN);

   
   pathCanonicalize(session->homeDir);
   pathRemoveSlash(session->homeDir);

   
   return NO_ERROR;
}




void sftpServerTask(void *param)
{
   error_t error;
   uint_t i;
   systime_t timeout;
   SftpServerContext *context;
   SftpServerSession *session;

   
   context = (SftpServerContext *) param;

#if (NET_RTOS_SUPPORT == ENABLED)
   
   osEnterTask();

   
   while(1)
   {
#endif
      
      timeout = SFTP_SERVER_TICK_INTERVAL;

      
      osMemset(context->eventDesc, 0, sizeof(context->eventDesc));

      
      for(i = 0; i < context->numSessions; i++)
      {
         
         session = &context->sessions[i];

         
         if(session->state != SFTP_SERVER_SESSION_STATE_CLOSED)
         {
            
            sftpServerRegisterSessionEvents(session, &context->eventDesc[i]);

            
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

            
            if(session->state != SFTP_SERVER_SESSION_STATE_CLOSED)
            {
               
               if(context->eventDesc[i].eventFlags != 0)
               {
                  
                  sftpServerProcessSessionEvents(session);
               }
            }
         }
      }

      
      sftpServerTick(context);

#if (NET_RTOS_SUPPORT == ENABLED)
   }
#endif
}




void sftpServerDeinit(SftpServerContext *context)
{
   
   if(context != NULL)
   {
      
      osDeleteEvent(&context->event);

      
      osMemset(context, 0, sizeof(SftpServerContext));
   }
}

#endif
