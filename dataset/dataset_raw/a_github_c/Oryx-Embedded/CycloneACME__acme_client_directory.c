


#define TRACE_LEVEL ACME_TRACE_LEVEL


#include "acme/acme_client.h"
#include "acme/acme_client_directory.h"
#include "acme/acme_client_misc.h"
#include "jansson.h"
#include "debug.h"


#if (ACME_CLIENT_SUPPORT == ENABLED)




error_t acmeClientSendDirectoryRequest(AcmeClientContext *context)
{
   error_t error;

   
   error = NO_ERROR;

   
   while(!error)
   {
      
      if(context->requestState == ACME_REQ_STATE_INIT)
      {
         
         TRACE_DEBUG("\r\n");
         TRACE_DEBUG("###############################################################################\r\n");
         TRACE_DEBUG("## GET DIRECTORY ##############################################################\r\n");
         TRACE_DEBUG("###############################################################################\r\n");
         TRACE_DEBUG("\r\n");

         
         if(context->directory.newNonce[0] != '\0' &&
            context->directory.newAccount[0] != '\0' &&
            context->directory.newOrder[0] != '\0' &&
            context->directory.revokeCert[0] != '\0' &&
            context->directory.keyChange[0] != '\0')
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
         
         
         error = acmeClientFormatRequestHeader(context, "GET",
            context->directoryUri);

         
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
         
         error = acmeClientParseDirectoryResponse(context);

         
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




error_t acmeClientParseDirectoryResponse(AcmeClientContext *context)
{
   error_t error;
   const char_t *newNonce;
   const char_t *newAccount;
   const char_t *newOrder;
   const char_t *revokeCert;
   const char_t *keyChange;
   json_t *rootObj;
   json_t *newNonceObj;
   json_t *newAccountObj;
   json_t *newOrderObj;
   json_t *revokeCertObj;
   json_t *keyChangeObj;

   
   if(!HTTP_STATUS_CODE_2YZ(context->statusCode))
      return ERROR_UNEXPECTED_STATUS;

   
   if(osStrcasecmp(context->contentType, "application/json"))
      return ERROR_INVALID_RESPONSE;

   
   if(context->bufferLen >= ACME_CLIENT_BUFFER_SIZE)
      return ERROR_RESPONSE_TOO_LARGE;

   
   error = ERROR_INVALID_RESPONSE;

   
   osMemset(&context->directory, 0, sizeof(AcmeDirectory));

   
   rootObj = json_loads(context->buffer, 0, NULL);

   
   if(json_is_object(rootObj))
   {
      
      
      newNonceObj = json_object_get(rootObj, "newNonce");
      newAccountObj = json_object_get(rootObj, "newAccount");
      newOrderObj = json_object_get(rootObj, "newOrder");
      revokeCertObj = json_object_get(rootObj, "revokeCert");
      keyChangeObj = json_object_get(rootObj, "keyChange");

      
      if(json_is_string(newNonceObj) &&
         json_is_string(newAccountObj) &&
         json_is_string(newOrderObj) &&
         json_is_string(revokeCertObj) &&
         json_is_string(keyChangeObj))
      {
         
         newNonce = json_string_value(newNonceObj);
         newAccount = json_string_value(newAccountObj);
         newOrder = json_string_value(newOrderObj);
         revokeCert = json_string_value(revokeCertObj);
         keyChange = json_string_value(keyChangeObj);

         
         if(osStrlen(newNonce) <= ACME_CLIENT_MAX_URL_LEN &&
            osStrlen(newAccount) <= ACME_CLIENT_MAX_URL_LEN &&
            osStrlen(newOrder) <= ACME_CLIENT_MAX_URL_LEN &&
            osStrlen(revokeCert) <= ACME_CLIENT_MAX_URL_LEN &&
            osStrlen(keyChange) <= ACME_CLIENT_MAX_URL_LEN)
         {
            
            osStrcpy(context->directory.newNonce, newNonce);
            osStrcpy(context->directory.newAccount, newAccount);
            osStrcpy(context->directory.newOrder, newOrder);
            osStrcpy(context->directory.revokeCert, revokeCert);
            osStrcpy(context->directory.keyChange, keyChange);

            
            error = NO_ERROR;
         }
      }
   }

   
   json_decref(rootObj);

   
   return error;
}

#endif
