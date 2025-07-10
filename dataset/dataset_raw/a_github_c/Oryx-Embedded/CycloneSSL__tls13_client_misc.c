


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include <string.h>
#include "tls.h"
#include "tls_handshake.h"
#include "tls_client.h"
#include "tls_common.h"
#include "tls_transcript_hash.h"
#include "tls_record.h"
#include "tls_misc.h"
#include "tls13_client_misc.h"
#include "tls13_key_material.h"
#include "tls13_ticket.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED && TLS_CLIENT_SUPPORT == ENABLED && \
   TLS_MAX_VERSION >= TLS_VERSION_1_3)




bool_t tls13IsHelloRetryRequest(const TlsServerHello *message, size_t length)
{
   bool_t res;

   
   res = FALSE;

   
   if(length >= sizeof(TlsServerHello))
   {
      
      
      if(!osMemcmp(&message->random, tls13HelloRetryRequestRandom,
         sizeof(tls13HelloRetryRequestRandom)))
      {
         
         res = TRUE;
      }
   }

   
   return res;
}




error_t tls13ComputePskBinders(TlsContext *context, const void *clientHello,
   size_t clientHelloLen, const Tls13PskIdentityList *identityList,
   Tls13PskBinderList *binderList)
{
   error_t error;
   size_t n;
   size_t m;
   size_t truncatedClientHelloLen;
   uint8_t *q;
   const uint8_t *p;
   Tls13PskBinder *binder;
   const Tls13PskIdentity *identity;

   
   error = NO_ERROR;

#if (TLS13_PSK_KE_SUPPORT == ENABLED || TLS13_PSK_DHE_KE_SUPPORT == ENABLED || \
   TLS13_PSK_ECDHE_KE_SUPPORT == ENABLED)
   
   if(identityList != NULL && binderList != NULL)
   {
      
      
      p = identityList->value;
      n = ntohs(identityList->length);

      
      
      q = binderList->value;
      m = ntohs(binderList->length);

      
      
      truncatedClientHelloLen = (uint8_t *) binderList - (uint8_t *) clientHello;

      
      while(n > 0)
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

         
         binder = (Tls13PskBinder *) q;

         
         if(m < sizeof(Tls13PskBinder))
            return ERROR_DECODING_FAILED;
         if(m < (sizeof(Tls13PskBinder) + binder->length))
            return ERROR_DECODING_FAILED;

         
         q += sizeof(Tls13PskBinder) + binder->length;
         m -= sizeof(Tls13PskBinder) + binder->length;

         
         error = tls13ComputePskBinder(context, clientHello, clientHelloLen,
            truncatedClientHelloLen, identity, binder->value, binder->length);
         
         if(error)
            break;
      }
   }
#endif

   
   return error;
}




error_t tls13SendEarlyData(TlsContext *context, const void *data,
   size_t length, size_t *written)
{
#if (TLS13_EARLY_DATA_SUPPORT == ENABLED)
   error_t error;
   size_t n;

   
   *written = 0;

   
   if(tls13IsPskValid(context))
   {
      
      if(context->pskCipherSuite == 0)
         return ERROR_END_OF_STREAM;
   }
   else if(tls13IsTicketValid(context))
   {
      
      if(context->ticketCipherSuite == 0)
         return ERROR_END_OF_STREAM;
   }
   else
   {
      
      return ERROR_END_OF_STREAM;
   }

   
   error = NO_ERROR;

   
   while(!error)
   {
      
      if(context->transportProtocol == TLS_TRANSPORT_PROTOCOL_STREAM)
      {
         
         if(context->state != TLS_STATE_INIT &&
            context->state != TLS_STATE_CLOSED)
         {
            
            error = tlsWriteProtocolData(context, NULL, 0, TLS_TYPE_NONE);
            
            if(error)
               break;
         }
      }

      
      
      if(context->state == TLS_STATE_INIT)
      {
         
         error = tlsInitHandshake(context);
      }
      else if(context->state == TLS_STATE_CLIENT_HELLO)
      {
         
         
         
         context->earlyDataEnabled = TRUE;

         
         
         error = tlsSendClientHello(context);
      }
      else if(context->state == TLS_STATE_SERVER_HELLO)
      {
         
         error = tlsInitTranscriptHash(context);

#if (TLS13_MIDDLEBOX_COMPAT_SUPPORT == ENABLED)
         
         
         context->state = TLS_STATE_CLIENT_CHANGE_CIPHER_SPEC;
#else
         
         context->state = TLS_STATE_CLIENT_HELLO_2;
#endif
      }
      else if(context->state == TLS_STATE_CLIENT_CHANGE_CIPHER_SPEC)
      {
         
         error = tlsSendChangeCipherSpec(context);
      }
      else if(context->state == TLS_STATE_CLIENT_HELLO_2)
      {
         
         error = tls13GenerateEarlyTrafficKeys(context);
      }
      else if(context->state == TLS_STATE_EARLY_DATA)
      {
         
         if(*written < length &&
            context->earlyDataLen < context->maxEarlyDataSize)
         {
            
            n = MIN(context->txBufferMaxLen, length - *written);
            n = MIN(n, context->maxEarlyDataSize - context->earlyDataLen);

            
            n = MIN(n, TLS_MAX_RECORD_LENGTH);

            
            TRACE_INFO("Sending early data (%" PRIuSIZE " bytes)...\r\n", n);

            
            error = tlsWriteProtocolData(context, data, n,
               TLS_TYPE_APPLICATION_DATA);

            
            if(!error)
            {
               
               data = (uint8_t *) data + n;
               
               *written += n;

               
               context->earlyDataLen += n;
            }
         }
         else
         {
            
            break;
         }
      }
      else
      {
         
         error = ERROR_UNEXPECTED_STATE;
      }
   }

   
   if(error == NO_ERROR && length != 0 && *written == 0)
   {
      error = ERROR_END_OF_STREAM;
   }

   
   return error;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}

#endif
