


#define TRACE_LEVEL ACME_TRACE_LEVEL


#include "acme/acme_client.h"
#include "acme/acme_client_certificate.h"
#include "acme/acme_client_jose.h"
#include "acme/acme_client_misc.h"
#include "pkix/pem_import.h"
#include "encoding/base64url.h"
#include "jansson.h"
#include "jansson_private.h"
#include "debug.h"


#if (ACME_CLIENT_SUPPORT == ENABLED)




error_t acmeClientSendDownloadCertRequest(AcmeClientContext *context,
   char_t *buffer, size_t size, size_t *length)
{
   error_t error;

   
   error = NO_ERROR;

   
   while(!error)
   {
      
      if(context->requestState == ACME_REQ_STATE_INIT)
      {
         
         TRACE_DEBUG("\r\n");
         TRACE_DEBUG("###############################################################################\r\n");
         TRACE_DEBUG("## DOWNLOAD CERTIFICATE #######################################################\r\n");
         TRACE_DEBUG("###############################################################################\r\n");
         TRACE_DEBUG("\r\n");

         
         context->requestState = ACME_REQ_STATE_FORMAT_BODY;
      }
      else if(context->requestState == ACME_REQ_STATE_FORMAT_BODY)
      {
         
         error = acmeClientFormatDownloadCertRequest(context);

         
         if(!error)
         {
            
            context->requestState = ACME_REQ_STATE_FORMAT_HEADER;
         }
      }
      else if(context->requestState == ACME_REQ_STATE_FORMAT_HEADER)
      {
         
         
         
         error = acmeClientFormatRequestHeader(context, "POST",
            context->order.certificate);

         
         if(!error)
         {
            
            context->requestState = ACME_REQ_STATE_SEND_HEADER;
         }
      }
      else if(context->requestState == ACME_REQ_STATE_SEND_HEADER ||
         context->requestState == ACME_REQ_STATE_SEND_BODY ||
         context->requestState == ACME_REQ_STATE_RECEIVE_HEADER ||
         context->requestState == ACME_REQ_STATE_PARSE_HEADER ||
         context->requestState == ACME_REQ_STATE_RECEIVE_BODY ||
         context->requestState == ACME_REQ_STATE_CLOSE_BODY)
      {
         
         error = acmeClientSendRequest(context);
      }
      else if(context->requestState == ACME_REQ_STATE_PARSE_BODY)
      {
         
         error = acmeClientParseDownloadCertResponse(context, buffer, size,
            length);

         
         context->requestState = ACME_REQ_STATE_INIT;
         break;
      }
      else
      {
         
         error = ERROR_WRONG_STATE;
      }
   }

   
   return error;
}




error_t acmeClientFormatDownloadCertRequest(AcmeClientContext *context)
{
   error_t error;
   size_t n;
   char_t *protected;
   const char_t *payload;

   
   payload = "";

   
   protected = context->buffer;

   
   error = acmeClientFormatJwsProtectedHeader(&context->accountKey,
      context->account.url, context->nonce, context->order.certificate,
      protected, &n);

   
   if(!error)
   {
      
      error = jwsCreate(context->prngAlgo, context->prngContext, protected,
         payload, context->accountKey.alg, context->accountKey.crv,
         context->accountKey.privateKey, context->buffer, &context->bufferLen);
   }

   
   return error;
}




error_t acmeClientParseDownloadCertResponse(AcmeClientContext *context,
   char_t *buffer, size_t size, size_t *length)
{
   error_t error;
   size_t n;

   
   error = NO_ERROR;

   
   if(!HTTP_STATUS_CODE_2YZ(context->statusCode))
      return ERROR_UNEXPECTED_STATUS;

   
   
   if(context->nonce[0] == '\0')
      return ERROR_INVALID_RESPONSE;

   
   if(osStrcasecmp(context->contentType, "application/pem-certificate-chain"))
      return ERROR_INVALID_RESPONSE;

   
   if(context->bufferLen >= ACME_CLIENT_BUFFER_SIZE)
      return ERROR_RESPONSE_TOO_LARGE;

   
   error = pemImportCertificate(context->buffer, context->bufferLen, NULL,
      &n, NULL);
   
   if(error)
      return ERROR_INVALID_RESPONSE;

   
   if(context->bufferLen > size)
      return ERROR_BUFFER_OVERFLOW;

   
   osMemcpy(buffer, context->buffer, context->bufferLen);

   
   *length = context->bufferLen;

   
   return error;
}




error_t acmeClientSendRevokeCertRequest(AcmeClientContext *context,
   const char_t *cert, size_t certLen, AcmeReasonCode reason)
{
   error_t error;

   
   error = NO_ERROR;

   
   while(!error)
   {
      
      if(context->requestState == ACME_REQ_STATE_INIT)
      {
         
         TRACE_DEBUG("\r\n");
         TRACE_DEBUG("###############################################################################\r\n");
         TRACE_DEBUG("## REVOKE CERTIFICATE #########################################################\r\n");
         TRACE_DEBUG("###############################################################################\r\n");
         TRACE_DEBUG("\r\n");

         
         context->requestState = ACME_REQ_STATE_FORMAT_BODY;
      }
      else if(context->requestState == ACME_REQ_STATE_FORMAT_BODY)
      {
         
         error = acmeClientFormatRevokeCertRequest(context, cert, certLen, reason);

         
         if(!error)
         {
            
            context->requestState = ACME_REQ_STATE_FORMAT_HEADER;
         }
      }
      else if(context->requestState == ACME_REQ_STATE_FORMAT_HEADER)
      {
         
         
         
         error = acmeClientFormatRequestHeader(context, "POST",
            context->directory.revokeCert);

         
         if(!error)
         {
            
            context->requestState = ACME_REQ_STATE_SEND_HEADER;
         }
      }
      else if(context->requestState == ACME_REQ_STATE_SEND_HEADER ||
         context->requestState == ACME_REQ_STATE_SEND_BODY ||
         context->requestState == ACME_REQ_STATE_RECEIVE_HEADER ||
         context->requestState == ACME_REQ_STATE_PARSE_HEADER ||
         context->requestState == ACME_REQ_STATE_RECEIVE_BODY ||
         context->requestState == ACME_REQ_STATE_CLOSE_BODY)
      {
         
         error = acmeClientSendRequest(context);
      }
      else if(context->requestState == ACME_REQ_STATE_PARSE_BODY)
      {
         
         error = acmeClientParseRevokeCertResponse(context);

         
         context->requestState = ACME_REQ_STATE_INIT;
         break;
      }
      else
      {
         
         error = ERROR_WRONG_STATE;
      }
   }

   
   return error;
}




error_t acmeClientFormatRevokeCertRequest(AcmeClientContext *context,
   const char_t *cert, size_t certLen, AcmeReasonCode reason)
{
   error_t error;
   int_t ret;
   size_t n;
   char_t *protected;
   char_t *payload;
   json_t *payloadObj;

   
   error = pemImportCertificate(cert, certLen, (uint8_t *) context->buffer,
      &n, NULL);
   
   if(error)
      return error;

   
   base64urlEncode(context->buffer, n, context->buffer, &n);

   
   payloadObj = json_object();

   
   ret = json_object_set_new(payloadObj, "certificate",
      json_string(context->buffer));

   
   ret |= json_object_set_new(payloadObj, "reason",
      json_integer((json_int_t) reason));

   
   if(ret == 0)
   {
      
      payload = json_dumps(payloadObj, JSON_COMPACT);
   }
   else
   {
      
      payload = NULL;
   }

   
   if(payload != NULL)
   {
      
      protected = context->buffer;

      
      error = acmeClientFormatJwsProtectedHeader(&context->accountKey,
         context->account.url, context->nonce, context->directory.revokeCert,
         protected, &n);

      
      if(!error)
      {
         
         error = jwsCreate(context->prngAlgo, context->prngContext, protected,
            payload, context->accountKey.alg, context->accountKey.crv,
            context->accountKey.privateKey, context->buffer, &context->bufferLen);
      }

      
      jsonp_free(payload);
   }
   else
   {
      
      error = ERROR_FAILURE;
   }

   
   json_decref(payloadObj);

   
   return error;
}




error_t acmeClientParseRevokeCertResponse(AcmeClientContext *context)
{
   
   if(!HTTP_STATUS_CODE_2YZ(context->statusCode))
      return ERROR_UNEXPECTED_STATUS;

   
   
   if(context->nonce[0] == '\0')
      return ERROR_INVALID_RESPONSE;

   
   return NO_ERROR;
}

#endif
