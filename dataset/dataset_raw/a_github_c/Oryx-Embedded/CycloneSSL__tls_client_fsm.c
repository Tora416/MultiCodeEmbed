


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include "tls.h"
#include "tls_handshake.h"
#include "tls_client.h"
#include "tls_client_fsm.h"
#include "tls_common.h"
#include "tls_record.h"
#include "tls_misc.h"
#include "tls13_client.h"
#include "tls13_client_misc.h"
#include "tls13_common.h"
#include "tls13_key_material.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED && TLS_CLIENT_SUPPORT == ENABLED)




error_t tlsPerformClientHandshake(TlsContext *context)
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

      
      case TLS_STATE_CLIENT_HELLO:
      case TLS_STATE_CLIENT_HELLO_2:
         
         
         error = tlsSendClientHello(context);
         break;

      
      case TLS_STATE_CLIENT_CERTIFICATE:
         
         
         
         error = tlsSendCertificate(context);
         break;

      
      case TLS_STATE_CLIENT_CERTIFICATE_VERIFY:
         
         
         
         
         error = tlsSendCertificateVerify(context);
         break;

      
      case TLS_STATE_CLIENT_CHANGE_CIPHER_SPEC:
      case TLS_STATE_CLIENT_CHANGE_CIPHER_SPEC_2:
         
         
         
         error = tlsSendChangeCipherSpec(context);
         break;

      
      case TLS_STATE_CLIENT_FINISHED:
         
         
         
         error = tlsSendFinished(context);
         break;

#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
      
      case TLS_STATE_CLIENT_KEY_EXCHANGE:
         
         
         
         
         error = tlsSendClientKeyExchange(context);
         break;
#endif

#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
      
      case TLS_STATE_END_OF_EARLY_DATA:
         
         
         
         error = tls13SendEndOfEarlyData(context);
         break;

      
      case TLS_STATE_HANDSHAKE_TRAFFIC_KEYS:
         
         error = tls13GenerateHandshakeTrafficKeys(context);
         break;

      
      case TLS_STATE_SERVER_APP_TRAFFIC_KEYS:
         
         error = tls13GenerateServerAppTrafficKeys(context);
         break;

      
      case TLS_STATE_CLIENT_APP_TRAFFIC_KEYS:
         
         error = tls13GenerateClientAppTrafficKeys(context);
         break;

      
      case TLS_STATE_KEY_UPDATE:
         
         
         error = tls13SendKeyUpdate(context);
         break;
#endif

      
      case TLS_STATE_SERVER_HELLO:
      case TLS_STATE_SERVER_HELLO_2:
      case TLS_STATE_SERVER_HELLO_3:
      case TLS_STATE_ENCRYPTED_EXTENSIONS:
      case TLS_STATE_SERVER_CERTIFICATE:
      case TLS_STATE_SERVER_KEY_EXCHANGE:
      case TLS_STATE_SERVER_CERTIFICATE_VERIFY:
      case TLS_STATE_CERTIFICATE_REQUEST:
      case TLS_STATE_SERVER_HELLO_DONE:
      case TLS_STATE_NEW_SESSION_TICKET:
      case TLS_STATE_SERVER_CHANGE_CIPHER_SPEC:
      case TLS_STATE_SERVER_FINISHED:
         
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

   
   if(error)
   {
      
      tlsProcessError(context, error);
   }

   
   return error;
}




error_t tlsParseServerHandshakeMessage(TlsContext *context, uint8_t msgType,
   const void *message, size_t length)
{
   error_t error;

   
   switch(msgType)
   {
   
   case TLS_TYPE_HELLO_REQUEST:
      
      
      error = tlsParseHelloRequest(context, message, length);
      break;

   
   case TLS_TYPE_SERVER_HELLO:
#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
      
      
      
      if(tls13IsHelloRetryRequest(message, length))
      {
         
         
         
         error = tls13ParseHelloRetryRequest(context, message, length);
      }
      else
#endif
      {
         
         
         error = tlsParseServerHello(context, message, length);
      }

      break;

   
   case TLS_TYPE_CERTIFICATE:
      
      
      
      error = tlsParseCertificate(context, message, length);
      break;

   
   case TLS_TYPE_CERTIFICATE_REQUEST:
      
      
      
      error = tlsParseCertificateRequest(context, message, length);
      break;

   
   case TLS_TYPE_NEW_SESSION_TICKET:
#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
      
      if(context->version == TLS_VERSION_1_3)
      {
         
         
         error = tls13ParseNewSessionTicket(context, message, length);
      }
      else
#endif
      {
         
         
         error = tlsParseNewSessionTicket(context, message, length);
      }

      break;

   
   case TLS_TYPE_FINISHED:
      
      
      
      error = tlsParseFinished(context, message, length);
      break;

#if (DTLS_SUPPORT == ENABLED)
   
   case TLS_TYPE_HELLO_VERIFY_REQUEST:
      
      
      error = dtlsParseHelloVerifyRequest(context, message, length);
      break;
#endif

#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
   
   case TLS_TYPE_SERVER_KEY_EXCHANGE:
      
      
      
      error = tlsParseServerKeyExchange(context, message, length);
      break;

   
   case TLS_TYPE_SERVER_HELLO_DONE:
      
      
      error = tlsParseServerHelloDone(context, message, length);
      break;
#endif

#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
   
   case TLS_TYPE_ENCRYPTED_EXTENSIONS:
      
      
      
      error = tls13ParseEncryptedExtensions(context, message, length);
      break;

   
   case TLS_TYPE_CERTIFICATE_VERIFY:
      
      
      
      error = tlsParseCertificateVerify(context, message, length);
      break;

   
   case TLS_TYPE_KEY_UPDATE:
      
      
      
      error = tls13ParseKeyUpdate(context, message, length);
      break;
#endif

   
   default:
      
      error = ERROR_UNEXPECTED_MESSAGE;
   }

   
   return error;
}

#endif
