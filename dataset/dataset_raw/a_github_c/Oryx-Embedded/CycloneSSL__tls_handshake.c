


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include "tls.h"
#include "tls_handshake.h"
#include "tls_client_fsm.h"
#include "tls_server_fsm.h"
#include "tls_common.h"
#include "tls_transcript_hash.h"
#include "tls_record.h"
#include "tls13_server_misc.h"
#include "dtls_record.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED)




error_t tlsInitHandshake(TlsContext *context)
{
   
   if(context->txBuffer == NULL)
   {
      
      context->txBuffer = tlsAllocMem(context->txBufferSize);

      
      if(context->txBuffer == NULL)
         return ERROR_OUT_OF_MEMORY;

      
      osMemset(context->txBuffer, 0, context->txBufferSize);
   }

   
   if(context->rxBuffer == NULL)
   {
      
      context->rxBuffer = tlsAllocMem(context->rxBufferSize);

      
      if(context->rxBuffer == NULL)
         return ERROR_OUT_OF_MEMORY;

      
      osMemset(context->rxBuffer, 0, context->rxBufferSize);
   }

#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
   
   if(context->entity == TLS_CONNECTION_END_SERVER)
   {
      
      context->earlyDataRejected = TRUE;
   }
#endif

   
   
   context->state = TLS_STATE_CLIENT_HELLO;

   
   return NO_ERROR;
}




error_t tlsPerformHandshake(TlsContext *context)
{
   error_t error;

#if (TLS_CLIENT_SUPPORT == ENABLED)
   
   if(context->entity == TLS_CONNECTION_END_CLIENT)
   {
      
      error = tlsPerformClientHandshake(context);
   }
   else
#endif
#if (TLS_SERVER_SUPPORT == ENABLED)
   
   if(context->entity == TLS_CONNECTION_END_SERVER)
   {
      
      error = tlsPerformServerHandshake(context);
   }
   else
#endif
   
   {
      
      error = ERROR_INVALID_PARAMETER;
   }

   
   return error;
}




error_t tlsSendHandshakeMessage(TlsContext *context, const void *data,
   size_t length, TlsMessageType type)
{
   error_t error;

#if (DTLS_SUPPORT == ENABLED)
   
   if(context->transportProtocol == TLS_TRANSPORT_PROTOCOL_DATAGRAM)
   {
      DtlsHandshake *message;

      
      message = (DtlsHandshake *) data;

      
      osMemmove(message->data, data, length);

      
      message->msgType = type;
      
      STORE24BE(length, message->length);
      
      message->msgSeq = htons(context->txMsgSeq);
      
      STORE24BE(0, message->fragOffset);
      
      STORE24BE(length, message->fragLength);

      
      
      context->txMsgSeq++;

      
      length += sizeof(DtlsHandshake);
   }
   else
#endif
   
   {
      TlsHandshake *message;

      
      message = (TlsHandshake *) data;

      
      osMemmove(message->data, data, length);

      
      message->msgType = type;
      
      STORE24BE(length, message->length);

      
      length += sizeof(TlsHandshake);
   }

   
   
   
   if(type != TLS_TYPE_HELLO_REQUEST)
   {
      tlsUpdateTranscriptHash(context, data, length);
   }

#if (DTLS_SUPPORT == ENABLED)
   
   if(context->transportProtocol == TLS_TRANSPORT_PROTOCOL_DATAGRAM)
   {
      
      error = dtlsWriteProtocolData(context, data, length, TLS_TYPE_HANDSHAKE);
   }
   else
#endif
   
   {
      
      error = tlsWriteProtocolData(context, data, length, TLS_TYPE_HANDSHAKE);
   }

   
   return error;
}




error_t tlsReceiveHandshakeMessage(TlsContext *context)
{
   error_t error;
   size_t length;
   uint8_t *data;
   TlsContentType contentType;

#if (DTLS_SUPPORT == ENABLED)
   
   if(context->transportProtocol == TLS_TRANSPORT_PROTOCOL_DATAGRAM)
   {
      
      error = dtlsReadProtocolData(context, &data, &length, &contentType);
   }
   else
#endif
   
   {
      
      error = tlsReadProtocolData(context, &data, &length, &contentType);
   }

   
   if(!error)
   {
      
      context->rxBufferPos += length;
      
      context->rxBufferLen -= length;

      
      if(contentType == TLS_TYPE_HANDSHAKE)
      {
         
         error = tlsParseHandshakeMessage(context, data, length);
      }
      
      else if(contentType == TLS_TYPE_CHANGE_CIPHER_SPEC)
      {
         
         
         
         error = tlsParseChangeCipherSpec(context, (TlsChangeCipherSpec *) data,
            length);
      }
      
      else if(contentType == TLS_TYPE_ALERT)
      {
         
         error = tlsParseAlert(context, (TlsAlert *) data, length);
      }
#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
      
      else if(contentType == TLS_TYPE_APPLICATION_DATA)
      {
#if (TLS_SERVER_SUPPORT == ENABLED)
         
         if(context->entity == TLS_CONNECTION_END_SERVER)
         {
            
            error = tls13ProcessEarlyData(context, data, length);
         }
         else
#endif
         {
            
            
            error = ERROR_UNEXPECTED_MESSAGE;
         }
      }
#endif
      
      else
      {
         
         error = ERROR_UNEXPECTED_MESSAGE;
      }
   }

   
   return error;
}




error_t tlsParseHandshakeMessage(TlsContext *context, const uint8_t *message,
   size_t length)
{
   error_t error;
   uint8_t msgType;
   size_t n;
   const void *p;

#if (DTLS_SUPPORT == ENABLED)
   
   if(context->transportProtocol == TLS_TRANSPORT_PROTOCOL_DATAGRAM)
   {
      
      msgType = ((DtlsHandshake *) message)->msgType;
      
      p = message + sizeof(DtlsHandshake);
      
      n = length - sizeof(DtlsHandshake);
   }
   else
#endif
   
   {
      
      msgType = ((TlsHandshake *) message)->msgType;
      
      p = message + sizeof(TlsHandshake);
      
      n = length - sizeof(TlsHandshake);
   }

#if (TLS_MAX_KEY_UPDATE_MESSAGES > 0)
   
   if(msgType != TLS_TYPE_KEY_UPDATE)
      context->keyUpdateCount = 0;
#endif

#if (TLS_CLIENT_SUPPORT == ENABLED)
   
   if(context->entity == TLS_CONNECTION_END_CLIENT)
   {
      
      error = tlsParseServerHandshakeMessage(context, msgType, p, n);

      
      tlsUpdateTranscriptHash(context, message, length);
   }
   else
#endif
#if (TLS_SERVER_SUPPORT == ENABLED)
   
   if(context->entity == TLS_CONNECTION_END_SERVER)
   {
      
      if(msgType == TLS_TYPE_CLIENT_KEY_EXCHANGE)
      {
         tlsUpdateTranscriptHash(context, message, length);
      }

      
      error = tlsParseClientHandshakeMessage(context, msgType, p, n);

      
      if(msgType != TLS_TYPE_CLIENT_KEY_EXCHANGE)
      {
         tlsUpdateTranscriptHash(context, message, length);
      }
   }
   else
#endif
   
   {
      
      error = ERROR_FAILURE;
   }

   
   return error;
}

#endif
