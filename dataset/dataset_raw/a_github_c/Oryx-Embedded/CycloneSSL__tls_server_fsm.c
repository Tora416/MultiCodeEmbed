


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include "tls.h"
#include "tls_handshake.h"
#include "tls_server.h"
#include "tls_server_fsm.h"
#include "tls_common.h"
#include "tls_cache.h"
#include "tls_record.h"
#include "tls_misc.h"
#include "tls13_server.h"
#include "tls13_common.h"
#include "tls13_key_material.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED && TLS_SERVER_SUPPORT == ENABLED)




error_t tlsPerformServerHandshake(TlsContext *context)
{
   error_t error;

   
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

      
      if(context->state == TLS_STATE_APPLICATION_DATA)
      {
         
         
         break;
      }

      
      
      switch(context->state)
      {
      
      case TLS_STATE_INIT:
         
         error = tlsInitHandshake(context);
         break;

      
      case TLS_STATE_SERVER_HELLO:
      case TLS_STATE_SERVER_HELLO_2:
         
         
         error = tlsSendServerHello(context);
         break;

      
      case TLS_STATE_SERVER_CERTIFICATE:
         
         
         
         error = tlsSendCertificate(context);
         break;

      
      case TLS_STATE_CERTIFICATE_REQUEST:
         
         
         
         error = tlsSendCertificateRequest(context);
         break;

      
      case TLS_STATE_SERVER_CHANGE_CIPHER_SPEC:
      case TLS_STATE_SERVER_CHANGE_CIPHER_SPEC_2:
         
         
         
         error = tlsSendChangeCipherSpec(context);
         break;

      
      case TLS_STATE_SERVER_FINISHED:
         
         
         
         error = tlsSendFinished(context);
         break;

#if (DTLS_SUPPORT == ENABLED)
      
      case TLS_STATE_HELLO_VERIFY_REQUEST:
         
         
         error = dtlsSendHelloVerifyRequest(context);
         break;
#endif

#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
      
      case TLS_STATE_SERVER_KEY_EXCHANGE:
         
         
         
         error = tlsSendServerKeyExchange(context);
         break;

      
      case TLS_STATE_SERVER_HELLO_DONE:
         
         
         error = tlsSendServerHelloDone(context);
         break;
#endif

#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
      
      case TLS_STATE_HELLO_RETRY_REQUEST:
         
         
         
         error = tls13SendHelloRetryRequest(context);
         break;

      
      case TLS_STATE_HANDSHAKE_TRAFFIC_KEYS:
         
         error = tls13GenerateHandshakeTrafficKeys(context);
         break;

      
      case TLS_STATE_ENCRYPTED_EXTENSIONS:
         
         
         
         error = tls13SendEncryptedExtensions(context);
         break;

      
      case TLS_STATE_SERVER_CERTIFICATE_VERIFY:
         
         
         
         error = tlsSendCertificateVerify(context);
         break;

      
      case TLS_STATE_SERVER_APP_TRAFFIC_KEYS:
         
         error = tls13GenerateServerAppTrafficKeys(context);
         break;

      
      case TLS_STATE_CLIENT_APP_TRAFFIC_KEYS:
         
         error = tls13GenerateClientAppTrafficKeys(context);
         break;

      
      case TLS_STATE_NEW_SESSION_TICKET:
         
         
         error = tls13SendNewSessionTicket(context);
         break;

      
      case TLS_STATE_KEY_UPDATE:
         
         
         error = tls13SendKeyUpdate(context);
         break;
#endif

      
      case TLS_STATE_CLIENT_HELLO:
      case TLS_STATE_CLIENT_HELLO_2:
      case TLS_STATE_CLIENT_CERTIFICATE:
      case TLS_STATE_CLIENT_KEY_EXCHANGE:
      case TLS_STATE_CLIENT_CERTIFICATE_VERIFY:
      case TLS_STATE_CLIENT_CHANGE_CIPHER_SPEC:
      case TLS_STATE_CLIENT_FINISHED:
         
         error = tlsReceiveHandshakeMessage(context);
         break;

      
      case TLS_STATE_CLOSING:
         
         context->state = TLS_STATE_CLOSED;
         break;

      
      case TLS_STATE_CLOSED:
         
         TRACE_WARNING("TLS handshake failure!\r\n");
         
         error = ERROR_HANDSHAKE_FAILED;
         break;

      
      default:
         
         error = ERROR_UNEXPECTED_STATE;
         break;
      }
   }

   
   if(!error)
   {
#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
      
      if(context->version <= TLS_VERSION_1_2)
      {
         
         tlsSaveToCache(context);
      }
#endif
   }
   else
   {
      
      tlsProcessError(context, error);
   }

   
   return error;
}




error_t tlsParseClientHandshakeMessage(TlsContext *context, uint8_t msgType,
   const void *message, size_t length)
{
   error_t error;

   
   switch(msgType)
   {
   
   case TLS_TYPE_CLIENT_HELLO:
      
      
      error = tlsParseClientHello(context, message, length);
      break;

   
   case TLS_TYPE_CERTIFICATE:
      
      
      
      error = tlsParseCertificate(context, message, length);
      break;

   
   case TLS_TYPE_CERTIFICATE_VERIFY:
      
      
      
      
      error = tlsParseCertificateVerify(context, message, length);
      break;

   
   case TLS_TYPE_FINISHED:
      
      
      
      error = tlsParseFinished(context, message, length);
      break;

#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
   
   case TLS_TYPE_CLIENT_KEY_EXCHANGE:
      
      
      
      error = tlsParseClientKeyExchange(context, message, length);
      break;
#endif

#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
   
   case TLS_TYPE_KEY_UPDATE:
      
      
      
      error = tls13ParseKeyUpdate(context, message, length);
      break;
#endif

   
   default:
      
      error = ERROR_UNEXPECTED_MESSAGE;
      break;
   }

   
   return error;
}

#endif
