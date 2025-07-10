


#define TRACE_LEVEL ACME_TRACE_LEVEL


#include "acme/acme_client.h"
#include "acme/acme_client_nonce.h"
#include "acme/acme_client_misc.h"
#include "debug.h"


#if (ACME_CLIENT_SUPPORT == ENABLED)




error_t acmeClientSendNewNonceRequest(AcmeClientContext *context)
{
   error_t error;

   
   error = NO_ERROR;

   
   while(!error)
   {
      
      if(context->requestState == ACME_REQ_STATE_INIT)
      {
         
         TRACE_DEBUG("\r\n");
         TRACE_DEBUG("################################################################################\r\n");
         TRACE_DEBUG("## GET NEW NONCE ###############################################################\r\n");
         TRACE_DEBUG("################################################################################\r\n");
         TRACE_DEBUG("\r\n");

         
         if(context->nonce[0] != '\0')
         {
            
            break;
         }
         else
         {
            
            context->requestState = ACME_REQ_STATE_FORMAT_HEADER;
         }
      }
      else if(context->requestState == ACME_REQ_STATE_FORMAT_HEADER)
      {
         
         
         error = acmeClientFormatRequestHeader(context, "HEAD",
            context->directory.newNonce);

         
         if(!error)
         {
            
            context->requestState = ACME_REQ_STATE_SEND_HEADER;
         }
      }
      else if(context->requestState == ACME_REQ_STATE_SEND_HEADER ||
         context->requestState == ACME_REQ_STATE_RECEIVE_HEADER ||
         context->requestState == ACME_REQ_STATE_PARSE_HEADER ||
         context->requestState == ACME_REQ_STATE_RECEIVE_BODY ||
         context->requestState == ACME_REQ_STATE_CLOSE_BODY)
      {
         
         error = acmeClientSendRequest(context);
      }
      else if(context->requestState == ACME_REQ_STATE_PARSE_BODY)
      {
         
         error = acmeClientParseNewNonceResponse(context);

         
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




error_t acmeClientParseNewNonceResponse(AcmeClientContext *context)
{
   
   if(!HTTP_STATUS_CODE_2YZ(context->statusCode))
      return ERROR_UNEXPECTED_STATUS;

   
   
   if(context->nonce[0] == '\0')
      return ERROR_INVALID_RESPONSE;

   
   return NO_ERROR;
}

#endif
