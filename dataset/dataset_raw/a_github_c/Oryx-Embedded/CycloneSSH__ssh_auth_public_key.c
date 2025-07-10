


#define TRACE_LEVEL SSH_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_algorithms.h"
#include "ssh/ssh_transport.h"
#include "ssh/ssh_auth.h"
#include "ssh/ssh_auth_public_key.h"
#include "ssh/ssh_packet.h"
#include "ssh/ssh_signature.h"
#include "ssh/ssh_misc.h"
#include "debug.h"


#if (SSH_SUPPORT == ENABLED && SSH_PUBLIC_KEY_AUTH_SUPPORT == ENABLED)




error_t sshSendUserAuthPkOk(SshConnection *connection,
   const SshString *publicKeyAlgo, const SshBinaryString *publicKey)
{
#if (SSH_SERVER_SUPPORT == ENABLED)
   error_t error;
   size_t length;
   uint8_t *message;

   
   message = connection->buffer + SSH_PACKET_HEADER_SIZE;

   
   error = sshFormatUserAuthPkOk(connection, publicKeyAlgo, publicKey, message,
      &length);

   
   if(!error)
   {
      
      TRACE_INFO("Sending SSH_MSG_USERAUTH_PK_OK message (%" PRIuSIZE " bytes)...\r\n", length);
      TRACE_VERBOSE_ARRAY("  ", message, length);

      
      error = sshSendPacket(connection, message, length);
   }

   
   return error;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t sshFormatPublicKeyAuthParams(SshConnection *connection,
   const uint8_t *message, size_t messageLen, uint8_t *p, size_t *written)
{
#if (SSH_CLIENT_SUPPORT == ENABLED)
   error_t error;
   size_t n;
   SshHostKey *hostKey;
   const char_t *publicKeyAlgo;

   
   *written = 0;

   
   error = sshFormatString("publickey", p, &n);
   
   if(error)
      return error;

   
   p += n;
   *written += n;

   
   p[0] = connection->publicKeyOk ? TRUE : FALSE;

   
   p += sizeof(uint8_t);
   *written += sizeof(uint8_t);

   
   hostKey = sshGetHostKey(connection);
   
   if(hostKey == NULL)
      return ERROR_INVALID_KEY;

   
   publicKeyAlgo = sshSelectPublicKeyAlgo(hostKey->keyFormatId);
   
   if(publicKeyAlgo == NULL)
      return ERROR_INVALID_KEY;

   
   error = sshFormatString(publicKeyAlgo, p, &n);
   
   if(error)
      return error;

   
   p += n;
   *written += n;

   
   error = sshFormatHostKey(connection, p + sizeof(uint32_t), &n);
   
   if(error)
      return error;

   
   STORE32BE(n, p);

   
   p += sizeof(uint32_t) + n;
   *written += sizeof(uint32_t) + n;

   
   
   if(connection->publicKeyOk)
   {
      
      messageLen += *written;

      
      error = sshGenerateSignature(connection, publicKeyAlgo, hostKey,
         message, messageLen, p + sizeof(uint32_t), &n);
      
      if(error)
         return error;

      
      STORE32BE(n, p);

      
      *written += sizeof(uint32_t) + n;
   }

   
   return NO_ERROR;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t sshFormatUserAuthPkOk(SshConnection *connection,
   const SshString *publicKeyAlgo, const SshBinaryString *publicKey,
   uint8_t *p, size_t *length)
{
#if (SSH_SERVER_SUPPORT == ENABLED)
   error_t error;
   size_t n;

   
   *length = 0;

   
   p[0] = SSH_MSG_USERAUTH_PK_OK;

   
   p += sizeof(uint8_t);
   *length += sizeof(uint8_t);

   
   error = sshFormatBinaryString(publicKeyAlgo->value, publicKeyAlgo->length,
      p, &n);
   
   if(error)
      return error;

   
   p += n;
   *length += n;

   
   error = sshFormatBinaryString(publicKey->value, publicKey->length, p, &n);
   
   if(error)
      return error;

   
   *length += n;

   
   return NO_ERROR;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t sshParsePublicKeyAuthParams(SshConnection *connection,
   const SshString *userName, const uint8_t *message, const uint8_t *p,
   size_t length)
{
#if (SSH_SERVER_SUPPORT == ENABLED)
   error_t error;
   size_t messageLen;
   SshBoolean flag;
   SshString publicKeyAlgo;
   SshBinaryString publicKey;
   SshBinaryString signature;
   SshContext *context;

   
   context = connection->context;

   
   if(length < sizeof(uint8_t))
      return ERROR_INVALID_MESSAGE;

   
   flag = p[0];

   
   p += sizeof(uint8_t);
   length -= sizeof(uint8_t);

   
   error = sshParseString(p, length, &publicKeyAlgo);
   
   if(error)
      return error;

   
   p += sizeof(uint32_t) + publicKeyAlgo.length;
   length -= sizeof(uint32_t) + publicKeyAlgo.length;

   
   error = sshParseBinaryString(p, length, &publicKey);
   
   if(error)
      return error;

   
   p += sizeof(uint32_t) + publicKey.length;
   length -= sizeof(uint32_t) + publicKey.length;

   
   messageLen = p - message;

   
   if(flag)
   {
      
      error = sshParseBinaryString(p, length, &signature);
      
      if(error)
         return error;

      
      p += sizeof(uint32_t) + signature.length;
      length -= sizeof(uint32_t) + signature.length;
   }
   else
   {
      
      signature.value = NULL;
      signature.length = 0;
   }

   
   if(length != 0)
      return ERROR_INVALID_MESSAGE;

   
   
   error = sshCheckHostKey(&publicKeyAlgo, &publicKey);

   
   if(!error)
   {
      
      if(userName->length <= SSH_MAX_USERNAME_LEN &&
         context->publicKeyAuthCallback != NULL)
      {
         
         osMemcpy(connection->user, userName->value, userName->length);
         
         connection->user[userName->length] = '\0';

         
         error = context->publicKeyAuthCallback(connection, connection->user,
            publicKey.value, publicKey.length);
      }
      else
      {
         
         error = ERROR_INVALID_KEY;
      }
   }

   
   if(!error)
   {
      
      if(flag)
      {
         
         
         error = sshVerifySignature(connection, &publicKeyAlgo, &publicKey,
            message, messageLen, &signature);
      }
   }

   
   if(!error)
   {
      
      if(flag)
      {
         
         
         error = sshSendUserAuthSuccess(connection);
      }
      else
      {
         
         if(connection->authAttempts <= SSH_MAX_AUTH_ATTEMPTS)
         {
            
            error = sshSendUserAuthPkOk(connection, &publicKeyAlgo, &publicKey);
         }
         else
         {
            
            
            error = sshSendDisconnect(connection, SSH_DISCONNECT_BY_APPLICATION,
               "Too many authentication attempts");
         }
      }
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




error_t sshParseUserAuthPkOk(SshConnection *connection,
   const uint8_t *message, size_t length)
{
#if (SSH_CLIENT_SUPPORT == ENABLED)
   error_t error;
   const uint8_t *p;
   SshString publicKeyAlgo;
   SshBinaryString publicKey;

   
   TRACE_INFO("SSH_MSG_USERAUTH_PK_OK message received (%" PRIuSIZE " bytes)...\r\n", length);
   TRACE_VERBOSE_ARRAY("  ", message, length);

   
   if(connection->context->mode != SSH_OPERATION_MODE_CLIENT)
      return ERROR_UNEXPECTED_MESSAGE;

   
   if(connection->state != SSH_CONN_STATE_USER_AUTH_REPLY)
      return ERROR_UNEXPECTED_MESSAGE;

   
   if(length < sizeof(uint8_t))
      return ERROR_INVALID_MESSAGE;

   
   p = message + sizeof(uint8_t);
   
   length -= sizeof(uint8_t);

   
   error = sshParseString(p, length, &publicKeyAlgo);
   
   if(error)
      return error;

   
   p += sizeof(uint32_t) + publicKeyAlgo.length;
   length -= sizeof(uint32_t) + publicKeyAlgo.length;

   
   error = sshParseBinaryString(p, length, &publicKey);
   
   if(error)
      return error;

   
   p += sizeof(uint32_t) + publicKey.length;
   length -= sizeof(uint32_t) + publicKey.length;

   
   if(length != 0)
      return ERROR_INVALID_MESSAGE;

   
   if(connection->publicKeyOk)
      return ERROR_UNEXPECTED_MESSAGE;

   
   error = sshCheckHostKey(&publicKeyAlgo, &publicKey);
   
   if(error)
      return error;

   
   connection->publicKeyOk = TRUE;

   
   
   connection->state = SSH_CONN_STATE_USER_AUTH_REQUEST;

   
   return NO_ERROR;
#else
   
   return ERROR_UNEXPECTED_MESSAGE;
#endif
}

#endif
