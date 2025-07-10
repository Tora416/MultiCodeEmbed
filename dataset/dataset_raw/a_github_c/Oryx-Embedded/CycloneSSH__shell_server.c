


#define TRACE_LEVEL SHELL_TRACE_LEVEL


#include "ssh/ssh.h"
#include "shell/shell_server.h"
#include "shell/shell_server_pty.h"
#include "shell/shell_server_misc.h"
#include "debug.h"


#if (SHELL_SERVER_SUPPORT == ENABLED)




void shellServerGetDefaultSettings(ShellServerSettings *settings)
{
   
   settings->sshServerContext = NULL;

   
   settings->numSessions = 0;
   settings->sessions = NULL;

   
   settings->checkUserCallback = NULL;
   
   settings->commandLineCallback = NULL;
}




error_t shellServerInit(ShellServerContext *context,
   const ShellServerSettings *settings)
{
   uint_t i;

   
   TRACE_INFO("Initializing shell server...\r\n");

   
   if(context == NULL || settings == NULL)
      return ERROR_INVALID_PARAMETER;

   
   if(settings->sessions == NULL || settings->numSessions < 1 ||
      settings->numSessions > SHELL_SERVER_MAX_SESSIONS)
   {
      return ERROR_INVALID_PARAMETER;
   }

   
   osMemset(context, 0, sizeof(ShellServerContext));

   
   context->sshServerContext = settings->sshServerContext;
   context->numSessions = settings->numSessions;
   context->sessions = settings->sessions;
   context->checkUserCallback = settings->checkUserCallback;
   context->commandLineCallback = settings->commandLineCallback;

   
   for(i = 0; i < context->numSessions; i++)
   {
      
      osMemset(&context->sessions[i], 0, sizeof(ShellServerSession));

      
      if(!osCreateEvent(&context->sessions[i].startEvent))
         return ERROR_OUT_OF_RESOURCES;

      
      if(!osCreateEvent(&context->sessions[i].event))
         return ERROR_OUT_OF_RESOURCES;
   }

   
   if(!osCreateEvent(&context->event))
      return ERROR_OUT_OF_RESOURCES;

   
   return NO_ERROR;
}




error_t shellServerStart(ShellServerContext *context)
{
   error_t error;
   uint_t i;
   OsTask *task;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   TRACE_INFO("Starting shell server...\r\n");

   
   if(context->running)
      return ERROR_ALREADY_RUNNING;

   
   error = sshServerRegisterChannelRequestCallback(context->sshServerContext,
      shellServerChannelRequestCallback, context);
   
   if(error)
      return error;

   
   for(i = 0; i < context->numSessions; i++)
   {
      
      task = osCreateTask("Shell Session", shellServerTask,
         &context->sessions[i], SHELL_SERVER_STACK_SIZE,
         SHELL_SERVER_PRIORITY);

      
      if(task == NULL)
         return ERROR_OUT_OF_RESOURCES;
   }

   
   return NO_ERROR;
}




error_t shellServerSetBanner(ShellServerSession *session,
   const char_t *banner)
{
   size_t n;

   
   if(session == NULL || banner == NULL)
      return ERROR_INVALID_PARAMETER;

   
   n = osStrlen(banner);

   
   if(n > SHELL_SERVER_BUFFER_SIZE)
      return ERROR_INVALID_LENGTH;

   
   osStrncpy(session->buffer, banner, n);

   
   session->bufferLen = n;
   session->bufferPos = 0;

   
   return NO_ERROR;
}




error_t shellServerSetPrompt(ShellServerSession *session,
   const char_t *prompt)
{
   
   if(session == NULL || prompt == NULL)
      return ERROR_INVALID_PARAMETER;

   
   if(osStrlen(prompt) > SHELL_SERVER_MAX_PROMPT_LEN)
      return ERROR_INVALID_LENGTH;

   
   osStrcpy(session->prompt, prompt);
   
   session->promptLen = osStrlen(prompt);

   
   return NO_ERROR;
}




error_t shellServerSetTimeout(ShellServerSession *session, systime_t timeout)
{
   error_t error;

   
   if(session != NULL)
   {
      
      error = sshSetChannelTimeout(session->channel, timeout);
   }
   else
   {
      
      error = ERROR_INVALID_PARAMETER;
   }

   
   return error;
}




error_t shellServerWriteStream(ShellServerSession *session, const void *data,
   size_t length, size_t *written, uint_t flags)
{
   error_t error;

   
   if(session != NULL)
   {
      
      error = sshWriteChannel(session->channel, data, length, written, flags);
   }
   else
   {
      
      error = ERROR_INVALID_PARAMETER;
   }

   
   return error;
}




error_t shellServerReadStream(ShellServerSession *session, void *data,
   size_t size, size_t *received, uint_t flags)
{
   error_t error;

   
   if(session != NULL)
   {
      
      error = sshReadChannel(session->channel, data, size, received, flags);
   }
   else
   {
      
      error = ERROR_INVALID_PARAMETER;
   }

   
   return error;
}




void shellServerTask(void *param)
{
   error_t error;
   SshChannel *channel;
   ShellServerSession *session;

   
   session = (ShellServerSession *) param;

   
   TRACE_INFO("Starting shell task...\r\n");

   
   error = NO_ERROR;

   
   while(1)
   {
      
      osWaitForEvent(&session->startEvent, INFINITE_DELAY);

      
      TRACE_INFO("Starting shell session...\r\n");

      
      channel = session->channel;

      
      if(session->state == SHELL_SERVER_SESSION_STATE_OPEN)
      {
         
         sshSetChannelTimeout(channel, INFINITE_DELAY);

         
         if(session->bufferLen > 0)
         {
            
            error = sshWriteChannel(channel, session->buffer,
               session->bufferLen, NULL, 0);
         }

         
         if(!error)
         {
            
            error = sshWriteChannel(channel, session->prompt,
               osStrlen(session->prompt), NULL, 0);
         }

         
         session->bufferLen = 0;
         session->bufferPos = 0;
         session->escSeqLen = 0;

         
         while(!error)
         {
            SshChannelEventDesc eventDesc[1];

            
            eventDesc[0].channel = channel;
            eventDesc[0].eventMask = SSH_CHANNEL_EVENT_RX_READY;
            eventDesc[0].eventFlags = 0;

            
            error = sshPollChannels(eventDesc, 1, &session->event,
               SHELL_SERVER_TICK_INTERVAL);

            
            if(error == NO_ERROR || error == ERROR_TIMEOUT)
            {
               
               if(session->windowResize)
               {
                  
                  error = shellServerProcessWindowResize(session);
               }

               
               if(eventDesc[0].eventFlags != 0)
               {
                  
                  error = shellServerProcessChar(session);
               }
               else
               {
                  
                  error = NO_ERROR;
               }
            }
            else
            {
               
               break;
            }
         }
      }
      else if(session->state == SHELL_SERVER_SESSION_STATE_EXEC)
      {
         
         session->buffer[session->bufferLen] = '\0';
         
         error = shellServerProcessCommandLine(session, session->buffer);
      }
      else
      {
         
      }

      
      sshCloseChannel(channel);

      
      session->state = SHELL_SERVER_SESSION_STATE_CLOSED;

      
      TRACE_INFO("Shell session terminated...\r\n");
   }
}

#endif
