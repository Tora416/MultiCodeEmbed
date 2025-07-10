


#define TRACE_LEVEL SSH_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_signature.h"
#include "ssh/ssh_exchange_hash.h"
#include "ssh/ssh_misc.h"
#include "debug.h"


#if (SSH_SUPPORT == ENABLED)




error_t sshInitExchangeHash(SshConnection *connection)
{
   error_t error;
   const HashAlgo *hashAlgo;

   
   error = NO_ERROR;

#if (SSH_SHA1_SUPPORT == ENABLED)
   
   if(sshCompareAlgo(connection->kexAlgo, "diffie-hellman-group1-sha1") ||
      sshCompareAlgo(connection->kexAlgo, "diffie-hellman-group14-sha1") ||
      sshCompareAlgo(connection->kexAlgo, "diffie-hellman-group-exchange-sha1"))
   {
      
      hashAlgo = SHA1_HASH_ALGO;
   }
   else
#endif
#if (SSH_SHA256_SUPPORT == ENABLED)
   
   if(sshCompareAlgo(connection->kexAlgo, "diffie-hellman-group14-sha256") ||
      sshCompareAlgo(connection->kexAlgo, "diffie-hellman-group-exchange-sha256") ||
      sshCompareAlgo(connection->kexAlgo, "ecdh-sha2-nistp256") ||
      sshCompareAlgo(connection->kexAlgo, "curve25519-sha256") ||
      sshCompareAlgo(connection->kexAlgo, "curve25519-sha256@libssh.org"))
   {
      
      hashAlgo = SHA256_HASH_ALGO;
   }
   else
#endif
#if (SSH_SHA384_SUPPORT == ENABLED)
   
   if(sshCompareAlgo(connection->kexAlgo, "ecdh-sha2-nistp384"))
   {
      
      hashAlgo = SHA384_HASH_ALGO;
   }
   else
#endif
#if (SSH_SHA512_SUPPORT == ENABLED)
   
   if(sshCompareAlgo(connection->kexAlgo, "diffie-hellman-group15-sha512") ||
      sshCompareAlgo(connection->kexAlgo, "diffie-hellman-group16-sha512") ||
      sshCompareAlgo(connection->kexAlgo, "ecdh-sha2-nistp521") ||
      sshCompareAlgo(connection->kexAlgo, "curve448-sha512"))
   {
      
      hashAlgo = SHA512_HASH_ALGO;
   }
   else
#endif
   
   {
      
      hashAlgo = NULL;
   }

   
   if(hashAlgo != NULL)
   {
      
      
      connection->hashAlgo = hashAlgo;

      
      hashAlgo->init(connection->hashContext);
   }
   else
   {
      
      error = ERROR_UNSUPPORTED_KEY_EXCH_METHOD;
   }

   
   return error;
}




error_t sshUpdateExchangeHash(SshConnection *connection, const void *data,
   size_t length)
{
   error_t error;
   uint8_t temp[4];

   
   error = NO_ERROR;

   
   if(connection->hashAlgo != NULL)
   {
      
      STORE32BE(length, temp);

      
      connection->hashAlgo->update(connection->hashContext, temp, sizeof(temp));
      
      connection->hashAlgo->update(connection->hashContext, data, length);
   }
   else
   {
      
      error = ERROR_FAILURE;
   }

   
   return error;
}




error_t sshFinalizeExchangeHash(SshConnection *connection, uint8_t *digest,
   size_t *digestLen)
{
   error_t error;

   
   error = NO_ERROR;

   
   if(connection->hashAlgo != NULL)
   {
      
      connection->hashAlgo->final(connection->hashContext, digest);
      
      *digestLen = connection->hashAlgo->digestSize;
   }
   else
   {
      
      error = ERROR_FAILURE;
   }

   
   return error;
}




error_t sshGenerateExchangeHashSignature(SshConnection *connection, uint8_t *p,
   size_t *written)
{
   error_t error;
   SshHostKey *hostKey;

   
   error = sshFinalizeExchangeHash(connection, connection->h,
      &connection->hLen);

   
   if(!error)
   {
      
      if(!connection->newKeysSent)
      {
         
         
         
         
         osMemcpy(connection->sessionId, connection->h, connection->hLen);
         connection->sessionIdLen = connection->hLen;
      }

      
      hostKey = sshGetHostKey(connection);

      
      if(hostKey != NULL)
      {
         
         error = sshGenerateSignature(connection, connection->serverHostKeyAlgo,
            hostKey, connection->h, connection->hLen, p, written);
      }
      else
      {
         
         error = ERROR_INVALID_KEY;
      }
   }

   
   return error;
}




error_t sshVerifyExchangeHashSignature(SshConnection *connection,
   const SshBinaryString *serverHostKey, const SshBinaryString *signature)
{
   error_t error;
   SshString serverHostKeyAlgo;

   
   error = sshFinalizeExchangeHash(connection, connection->h,
      &connection->hLen);

   
   if(!error)
   {
      
      if(!connection->newKeysSent)
      {
         
         
         
         
         osMemcpy(connection->sessionId, connection->h, connection->hLen);
         connection->sessionIdLen = connection->hLen;
      }

      
      serverHostKeyAlgo.value = connection->serverHostKeyAlgo;
      serverHostKeyAlgo.length = osStrlen(connection->serverHostKeyAlgo);

      
      error = sshVerifySignature(connection, &serverHostKeyAlgo, serverHostKey,
         connection->h, connection->hLen, signature);
   }

   
   return error;
}

#endif
