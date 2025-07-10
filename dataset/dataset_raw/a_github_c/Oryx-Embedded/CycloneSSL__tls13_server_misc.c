


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include <string.h>
#include "tls.h"
#include "tls_server_misc.h"
#include "tls_transcript_hash.h"
#include "tls_ffdhe.h"
#include "tls_misc.h"
#include "tls13_server_extensions.h"
#include "tls13_server_misc.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED && TLS_SERVER_SUPPORT == ENABLED && \
   TLS_MAX_VERSION >= TLS_VERSION_1_3)




error_t tls13NegotiateCipherSuite(TlsContext *context, const void *clientHello,
   size_t clientHelloLen, const TlsCipherSuites *cipherSuites,
   TlsHelloExtensions *extensions)
{
   error_t error;

   
   
   context->keyExchMethod = TLS_KEY_EXCH_NONE;

   
   
   
   error = tls13ParseClientPreSharedKeyExtension(context, clientHello,
      clientHelloLen, extensions->identityList, extensions->binderList);
   
   if(error)
      return error;

   
   if(context->selectedIdentity >= 0)
   {
      
      error = tlsNegotiateCipherSuite(context, context->cipherSuite.prfHashAlgo,
         cipherSuites, extensions);

      
      if(!error)
      {
         
         context->keyExchMethod = TLS13_KEY_EXCH_PSK;
      }
      else
      {
         
         context->keyExchMethod = TLS_KEY_EXCH_NONE;
         context->selectedIdentity = -1;
      }
   }

   
   if(context->keyExchMethod == TLS_KEY_EXCH_NONE)
   {
      
      error = tlsNegotiateCipherSuite(context, NULL, cipherSuites, extensions);
      
      if(error)
         return ERROR_HANDSHAKE_FAILED;
   }

   
   
   
   if(context->state != TLS_STATE_CLIENT_HELLO_2)
   {
      
      error = tlsInitTranscriptHash(context);
      
      if(error)
         return error;
   }

   
   
   error = tls13ParseClientEarlyDataExtension(context,
      extensions->earlyDataIndication);
   
   if(error)
      return error;

   
   error = tls13ParseClientKeyShareExtension(context, extensions->keyShareList);
   
   if(error)
      return error;

   
   if(extensions->keyShareList != NULL && context->namedGroup == TLS_GROUP_NONE)
   {
      
      error = tls13SelectGroup(context, extensions->supportedGroupList);
      
      if(error)
         return error;

      
      context->state = TLS_STATE_HELLO_RETRY_REQUEST;
   }
   else
   {
      
      if(context->keyExchMethod == TLS13_KEY_EXCH_DHE ||
         context->keyExchMethod == TLS13_KEY_EXCH_ECDHE)
      {
         
      }
      else if(context->keyExchMethod == TLS13_KEY_EXCH_PSK ||
         context->keyExchMethod == TLS13_KEY_EXCH_PSK_DHE ||
         context->keyExchMethod == TLS13_KEY_EXCH_PSK_ECDHE)
      {
         
         
         error = tls13ParsePskKeModesExtension(context,
            extensions->pskKeModeList);
         
         if(error)
            return error;

         
         
         error = tls13VerifyPskBinder(context, clientHello, clientHelloLen,
            extensions->identityList, extensions->binderList,
            context->selectedIdentity);
         
         if(error)
            return error;
      }
      else
      {
         
         
         return ERROR_HANDSHAKE_FAILED;
      }
   }

   
   return NO_ERROR;
}




error_t tls13SelectGroup(TlsContext *context,
   const TlsSupportedGroupList *groupList)
{
   error_t error;

   
   error = ERROR_HANDSHAKE_FAILED;

   
   context->namedGroup = TLS_GROUP_NONE;

#if (TLS13_DHE_KE_SUPPORT == ENABLED || TLS13_ECDHE_KE_SUPPORT == ENABLED || \
   TLS13_PSK_DHE_KE_SUPPORT == ENABLED || TLS13_PSK_ECDHE_KE_SUPPORT == ENABLED)
   
   if(groupList != NULL)
   {
      uint_t i;
      uint_t j;
      uint_t n;
      uint16_t namedGroup;

      
      n = ntohs(groupList->length) / sizeof(uint16_t);

      
      if(context->numSupportedGroups > 0)
      {
         
         for(i = 0; i < context->numSupportedGroups && error; i++)
         {
            
            for(j = 0; j < n && error; j++)
            {
               
               namedGroup = ntohs(groupList->value[j]);

               
               
               if(context->supportedGroups[i] == namedGroup)
               {
                  
                  if(tls13IsGroupSupported(context, namedGroup))
                  {
                     
                     context->namedGroup = namedGroup;
                     error = NO_ERROR;
                  }
               }
            }
         }
      }
      else
      {
         
         
         for(j = 0; j < n && error; j++)
         {
            
            namedGroup = ntohs(groupList->value[j]);

            
            if(tls13IsGroupSupported(context, namedGroup))
            {
               
               context->namedGroup = namedGroup;
               error = NO_ERROR;
            }
         }
      }
   }
#endif

   
   return error;
}




error_t tls13VerifyPskBinder(TlsContext *context, const void *clientHello,
   size_t clientHelloLen, const Tls13PskIdentityList *identityList,
   const Tls13PskBinderList *binderList, int_t selectedIdentity)
{
#if (TLS13_PSK_KE_SUPPORT == ENABLED || TLS13_PSK_DHE_KE_SUPPORT == ENABLED || \
   TLS13_PSK_ECDHE_KE_SUPPORT == ENABLED)
   error_t error;
   int_t i;
   size_t n;
   const uint8_t *p;
   const Tls13PskIdentity *identity;
   const Tls13PskBinder *binder;
   uint8_t calculatedBinder[TLS_MAX_HKDF_DIGEST_SIZE];

   
   identity = NULL;
   binder = NULL;

   
   if(identityList == NULL || binderList == NULL)
      return ERROR_FAILURE;

   
   if(selectedIdentity < 0)
      return ERROR_FAILURE;

   
   
   p = identityList->value;
   n = ntohs(identityList->length);

   
   for(i = 0; i <= selectedIdentity && n > 0; i++)
   {
      
      identity = (Tls13PskIdentity *) p;

      
      if(n < sizeof(TlsPskIdentity))
         return ERROR_DECODING_FAILED;
      if(n < (sizeof(TlsPskIdentity) + ntohs(identity->length)))
         return ERROR_DECODING_FAILED;

      
      p += sizeof(TlsPskIdentity) + ntohs(identity->length);
      n -= sizeof(TlsPskIdentity) + ntohs(identity->length);

      
      if(n < sizeof(uint32_t))
         return ERROR_DECODING_FAILED;

      
      p += sizeof(uint32_t);
      n -= sizeof(uint32_t);
   }

   
   if(selectedIdentity >= i)
      return ERROR_FAILURE;

   
   
   p = binderList->value;
   n = ntohs(binderList->length);

   
   for(i = 0; i <= selectedIdentity && n > 0; i++)
   {
      
      binder = (Tls13PskBinder *) p;

      
      if(n < sizeof(Tls13PskBinder))
         return ERROR_DECODING_FAILED;
      if(n < (sizeof(Tls13PskBinder) + binder->length))
         return ERROR_DECODING_FAILED;

      
      p += sizeof(Tls13PskBinder) + binder->length;
      n -= sizeof(Tls13PskBinder) + binder->length;
   }

   
   if(selectedIdentity >= i)
      return ERROR_FAILURE;

   
   if(binder->length > TLS_MAX_HKDF_DIGEST_SIZE)
      return ERROR_DECRYPTION_FAILED;

   
   
   n = (uint8_t *) binderList - (uint8_t *) clientHello;

   
   error = tls13ComputePskBinder(context, clientHello, clientHelloLen,
      n, identity, calculatedBinder, binder->length);
   
   if(error)
      return ERROR_DECRYPTION_FAILED;

   
   TRACE_DEBUG("PSK binder:\r\n");
   TRACE_DEBUG_ARRAY("  ", binder->value, binder->length);
   TRACE_DEBUG("Calculated PSK binder:\r\n");
   TRACE_DEBUG_ARRAY("  ", calculatedBinder, binder->length);

   
   
   if(osMemcmp(calculatedBinder, binder->value, binder->length))
   {
      
      return ERROR_DECRYPTION_FAILED;
   }

   
   return NO_ERROR;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t tls13ProcessEarlyData(TlsContext *context, const uint8_t *data,
   size_t length)
{
   
   if(context->version != TLS_VERSION_1_3)
      return ERROR_UNEXPECTED_MESSAGE;

   
   if(context->state != TLS_STATE_CLIENT_HELLO_2)
      return ERROR_UNEXPECTED_MESSAGE;

   
   
   if(!context->earlyDataExtReceived)
      return ERROR_UNEXPECTED_MESSAGE;

   
   context->earlyDataLen += length;

   
   
   if(context->earlyDataLen > context->maxEarlyDataSize)
      return ERROR_BAD_RECORD_MAC;

   
   TRACE_INFO("Discarding early data (%" PRIuSIZE " bytes)...\r\n", length);

   
   return NO_ERROR;
}

#endif
