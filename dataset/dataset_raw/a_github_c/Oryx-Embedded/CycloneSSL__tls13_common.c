


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include <string.h>
#include "tls.h"
#include "tls_handshake.h"
#include "tls_misc.h"
#include "tls13_common.h"
#include "tls13_key_material.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED && TLS_MAX_VERSION >= TLS_VERSION_1_3)




error_t tls13SendKeyUpdate(TlsContext *context)
{
   error_t error;
   size_t length;
   uint8_t *appTrafficSecret;
   Tls13KeyUpdate *message;
   const HashAlgo *hash;

   
   appTrafficSecret = NULL;

   
   message = (Tls13KeyUpdate *) (context->txBuffer + context->txBufferLen);

   
   error = tls13FormatKeyUpdate(context, message, &length);

   
   if(!error)
   {
      
      TRACE_INFO("Sending KeyUpdate message (%" PRIuSIZE " bytes)...\r\n", length);
      TRACE_DEBUG_ARRAY("  ", message, length);

      
      error = tlsSendHandshakeMessage(context, message, length,
         TLS_TYPE_KEY_UPDATE);
   }

   
   if(error == NO_ERROR || error == ERROR_WOULD_BLOCK || error == ERROR_TIMEOUT)
   {
      
      hash = context->cipherSuite.prfHashAlgo;

      
      if(hash != NULL)
      {
         
         if(context->entity == TLS_CONNECTION_END_CLIENT)
            appTrafficSecret = context->clientAppTrafficSecret;
         else
            appTrafficSecret = context->serverAppTrafficSecret;

         
         error = tls13HkdfExpandLabel(hash, appTrafficSecret, hash->digestSize,
            "traffic upd", NULL, 0, appTrafficSecret, hash->digestSize);
      }
      else
      {
         
         error = ERROR_FAILURE;
      }
   }

   
   if(!error)
   {
      
      tlsFreeEncryptionEngine(&context->encryptionEngine);

      
      
      error = tlsInitEncryptionEngine(context, &context->encryptionEngine,
         context->entity, appTrafficSecret);
   }

   
   if(!error)
   {
      
      
      context->state = TLS_STATE_APPLICATION_DATA;
   }

   
   return error;
}




error_t tls13FormatKeyUpdate(TlsContext *context, Tls13KeyUpdate *message,
   size_t *length)
{
   
   
   message->requestUpdate = TLS_KEY_UPDATE_NOT_REQUESTED;

   
   *length = sizeof(Tls13KeyUpdate);

   
   return NO_ERROR;
}




error_t tls13ParseKeyUpdate(TlsContext *context, const Tls13KeyUpdate *message,
   size_t length)
{
   error_t error;
   uint8_t *appTrafficSecret;
   TlsConnectionEnd entity;
   const HashAlgo *hash;

   
   TRACE_INFO("KeyUpdate message received (%" PRIuSIZE " bytes)...\r\n", length);
   TRACE_DEBUG_ARRAY("  ", message, length);

   
   if(context->version != TLS_VERSION_1_3)
      return ERROR_UNEXPECTED_MESSAGE;

   
   if(length != sizeof(Tls13KeyUpdate))
      return ERROR_DECODING_FAILED;

   
   if(message->requestUpdate != TLS_KEY_UPDATE_NOT_REQUESTED &&
      message->requestUpdate != TLS_KEY_UPDATE_REQUESTED)
   {
      
      
      return ERROR_ILLEGAL_PARAMETER;
   }

   
   
   if(context->state != TLS_STATE_APPLICATION_DATA &&
      context->state != TLS_STATE_CLOSING)
   {
      
      return ERROR_UNEXPECTED_MESSAGE;
   }

#if (TLS_MAX_KEY_UPDATE_MESSAGES > 0)
   
   context->keyUpdateCount++;

   
   if(context->keyUpdateCount > TLS_MAX_KEY_UPDATE_MESSAGES)
      return ERROR_UNEXPECTED_MESSAGE;
#endif

   
   hash = context->cipherSuite.prfHashAlgo;
   
   if(hash == NULL)
      return ERROR_FAILURE;

   
   if(context->entity == TLS_CONNECTION_END_CLIENT)
   {
      entity = TLS_CONNECTION_END_SERVER;
      appTrafficSecret = context->serverAppTrafficSecret;
   }
   else
   {
      entity = TLS_CONNECTION_END_CLIENT;
      appTrafficSecret = context->clientAppTrafficSecret;
   }

   
   error = tls13HkdfExpandLabel(hash, appTrafficSecret, hash->digestSize,
      "traffic upd", NULL, 0, appTrafficSecret, hash->digestSize);
   
   if(error)
      return error;

   
   
   if(context->rxBufferLen != 0)
      return ERROR_UNEXPECTED_MESSAGE;

   
   tlsFreeEncryptionEngine(&context->decryptionEngine);

   
   
   error = tlsInitEncryptionEngine(context, &context->decryptionEngine,
      entity, appTrafficSecret);
   
   if(error)
      return error;

   
   if(message->requestUpdate == TLS_KEY_UPDATE_REQUESTED &&
      context->state == TLS_STATE_APPLICATION_DATA)
   {
#if (TLS_MAX_KEY_UPDATE_MESSAGES > 0)
      if(context->keyUpdateCount == 1)
#endif
      {
         
         
         
         context->state = TLS_STATE_KEY_UPDATE;
      }
   }

   
   return NO_ERROR;
}

#endif
