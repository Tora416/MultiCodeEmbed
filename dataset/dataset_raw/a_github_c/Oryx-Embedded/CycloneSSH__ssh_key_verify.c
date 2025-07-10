


#define TRACE_LEVEL SSH_TRACE_LEVEL


#include "ssh/ssh.h"
#include "ssh/ssh_key_import.h"
#include "ssh/ssh_key_verify.h"
#include "debug.h"


#if (SSH_SUPPORT == ENABLED)




error_t sshVerifyHostKey(const uint8_t *hostKey, size_t hostKeyLen,
   const char_t *trustedKey, size_t trustedKeyLen)
{
   error_t error;
   size_t n;
   uint8_t *buffer;

   
   error = sshDecodePublicKeyFile(trustedKey, trustedKeyLen, NULL, &n);

   
   if(!error)
   {
      
      buffer = sshAllocMem(n);

      
      if(buffer != NULL)
      {
         
         error = sshDecodePublicKeyFile(trustedKey, trustedKeyLen, buffer, &n);

         
         if(hostKeyLen == n && !osMemcmp(hostKey, buffer, n))
         {
            
            error = NO_ERROR;
         }
         else
         {
            
            error = ERROR_INVALID_KEY;
         }

         
         sshFreeMem(buffer);
      }
      else
      {
         
         error = ERROR_OUT_OF_MEMORY;
      }
   }

   
   return error;
}

#endif
