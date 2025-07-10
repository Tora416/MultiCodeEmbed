


#define TRACE_LEVEL SSH_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_transport.h"
#include "ssh/ssh_auth.h"
#include "ssh/ssh_auth_password.h"
#include "ssh/ssh_misc.h"
#include "debug.h"


#if (SSH_SUPPORT == ENABLED && SSH_PASSWORD_AUTH_SUPPORT == ENABLED)




error_t sshFormatPasswordAuthParams(SshConnection *connection, uint8_t *p,
   size_t *written)
{
#if (SSH_CLIENT_SUPPORT == ENABLED)
   error_t error;
   size_t n;

   
   *written = 0;

   
   error = sshFormatString("password", p, &n);
   
   if(error)
      return error;

   
   p += n;
   *written += n;

   
   p[0] = FALSE;

   
   p += sizeof(uint8_t);
   *written += sizeof(uint8_t);

   
   error = sshFormatString(connection->context->password, p, &n);
   
   if(error)
      return error;

   
   *written += n;

   
   return NO_ERROR;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t sshParsePasswordAuthParams(SshConnection *connection,
   const SshString *userName, const uint8_t *p, size_t length)
{
#if (SSH_SERVER_SUPPORT == ENABLED)
   error_t error;
   SshBoolean flag;
   SshString oldPassword;
   SshString newPassword;
   SshAccessStatus status;
   SshContext *context;

   
   context = connection->context;

   
   if(length < sizeof(uint8_t))
      return ERROR_INVALID_MESSAGE;

   
   flag = p[0];

   
   p += sizeof(uint8_t);
   length -= sizeof(uint8_t);

   
   error = sshParseString(p, length, &oldPassword);
   
   if(error)
      return error;

   
   p += sizeof(uint32_t) + oldPassword.length;
   length -= sizeof(uint32_t) + oldPassword.length;

   
   if(flag)
   {
      
      error = sshParseString(p, length, &newPassword);
      
      if(error)
         return error;

      
      p += sizeof(uint32_t) + newPassword.length;
      length -= sizeof(uint32_t) + newPassword.length;
   }
   else
   {
      
      newPassword.value = NULL;
      newPassword.length = 0;
   }

   
   if(length != 0)
      return ERROR_INVALID_MESSAGE;

   
   if(userName->length <= SSH_MAX_USERNAME_LEN)
   {
      
      osMemcpy(connection->user, userName->value, userName->length);
      
      connection->user[userName->length] = '\0';

      
      if(context->passwordAuthCallback != NULL)
      {
         
         status = context->passwordAuthCallback(connection, connection->user,
            oldPassword.value, oldPassword.length);
      }
      else
      {
         
         status = SSH_ACCESS_DENIED;
      }
   }
   else
   {
      
      status = SSH_ACCESS_DENIED;
   }

   
   if(status == SSH_ACCESS_ALLOWED)
   {
      
      
      error = sshSendUserAuthSuccess(connection);
   }
   else
   {
      
      
      error = sshRejectAuthRequest(connection);
   }

   
   return error;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t sshParseUserAuthPasswdChangeReq(SshConnection *connection,
   const uint8_t *message, size_t length)
{
#if (SSH_CLIENT_SUPPORT == ENABLED)
   error_t error;
   const uint8_t *p;
   SshString prompt;
   SshString languageTag;

   
   TRACE_INFO("SSH_USERAUTH_PASSWD_CHANGEREQ message received (%" PRIuSIZE " bytes)...\r\n", length);
   TRACE_VERBOSE_ARRAY("  ", message, length);

   
   if(connection->context->mode != SSH_OPERATION_MODE_CLIENT)
      return ERROR_UNEXPECTED_MESSAGE;

   
   if(connection->state != SSH_CONN_STATE_USER_AUTH_REPLY)
      return ERROR_UNEXPECTED_MESSAGE;

   
   if(length < sizeof(uint8_t))
      return ERROR_INVALID_MESSAGE;

   
   p = message + sizeof(uint8_t);
   
   length -= sizeof(uint8_t);

   
   error = sshParseString(p, length, &prompt);
   
   if(error)
      return error;

   
   p += sizeof(uint32_t) + prompt.length;
   length -= sizeof(uint32_t) + prompt.length;

   
   error = sshParseString(p, length, &languageTag);
   
   if(error)
      return error;

   
   p += sizeof(uint32_t) + languageTag.length;
   length -= sizeof(uint32_t) + languageTag.length;

   
   if(length != 0)
      return ERROR_INVALID_MESSAGE;

   
   
   return ERROR_AUTHENTICATION_FAILED;
#else
   
   return ERROR_UNEXPECTED_MESSAGE;
#endif
}

#endif
