


#define TRACE_LEVEL ACME_TRACE_LEVEL


#include "acme/acme_client.h"
#include "acme/acme_client_auth.h"
#include "acme/acme_client_challenge.h"
#include "acme/acme_client_jose.h"
#include "acme/acme_client_misc.h"
#include "jansson.h"
#include "debug.h"


#if (ACME_CLIENT_SUPPORT == ENABLED)




error_t acmeClientSendAuthorizationRequest(AcmeClientContext *context,
   AcmeAuthorization *authorization)
{
   error_t error;

   
   error = NO_ERROR;

   
   while(!error)
   {
      
      if(context->requestState == ACME_REQ_STATE_INIT)
      {
         
         TRACE_DEBUG("\r\n");
         TRACE_DEBUG("###############################################################################\r\n");
         TRACE_DEBUG("## GET AUTHORIZATION ##########################################################\r\n");
         TRACE_DEBUG("###############################################################################\r\n");
         TRACE_DEBUG("\r\n");

         
         context->requestState = ACME_REQ_STATE_FORMAT_BODY;
      }
      else if(context->requestState == ACME_REQ_STATE_FORMAT_BODY)
      {
         
         error = acmeFormatAuthorizationRequest(context, authorization);

         
         if(!error)
         {
            
            context->requestState = ACME_REQ_STATE_FORMAT_HEADER;
         }
      }
      else if(context->requestState == ACME_REQ_STATE_FORMAT_HEADER)
      {
         
         
         
         
         error = acmeClientFormatRequestHeader(context, "POST",
            authorization->url);

         
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
         
         error = acmeClientParseAuthorizationResponse(context, authorization);

         
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




error_t acmeFormatAuthorizationRequest(AcmeClientContext *context,
   const AcmeAuthorization *authorization)
{
   error_t error;
   size_t n;
   char_t *protected;
   const char_t *payload;

   
   payload = "";

   
   protected = context->buffer;

   
   error = acmeClientFormatJwsProtectedHeader(&context->accountKey,
      context->account.url, context->nonce, authorization->url, protected, &n);

   
   if(!error)
   {
      
      error = jwsCreate(context->prngAlgo, context->prngContext, protected,
         payload, context->accountKey.alg, context->accountKey.crv,
         context->accountKey.privateKey, context->buffer, &context->bufferLen);
   }

   
   return error;
}




error_t acmeClientParseAuthorizationResponse(AcmeClientContext *context,
   AcmeAuthorization *authorization)
{
   error_t error;
   uint_t i;
   uint_t n;
   const char_t *status;
   const char_t *value;
   const char_t *type;
   const char_t *url;
   const char_t *token;
   json_t *rootObj;
   json_t *statusObj;
   json_t *identifierObj;
   json_t *valueObj;
   json_t *wildcardObj;
   json_t *arrayObj;
   json_t *challengeObj;
   json_t *typeObj;
   json_t *urlObj;
   json_t *tokenObj;
   AcmeChallenge *challenge;
   AcmeChallengeType challengeType;

   
   if(!HTTP_STATUS_CODE_2YZ(context->statusCode))
      return ERROR_UNEXPECTED_STATUS;

   
   
   if(context->nonce[0] == '\0')
      return ERROR_INVALID_RESPONSE;

   
   if(osStrcasecmp(context->contentType, "application/json"))
      return ERROR_INVALID_RESPONSE;

   
   if(context->bufferLen >= ACME_CLIENT_BUFFER_SIZE)
      return ERROR_RESPONSE_TOO_LARGE;

   
   error = ERROR_INVALID_RESPONSE;

   
   rootObj = json_loads(context->buffer, 0, NULL);

   
   do
   {
      
      if(!json_is_object(rootObj))
         break;

      
      statusObj = json_object_get(rootObj, "status");

      
      if(!json_is_string(statusObj))
         break;

      
      status = json_string_value(statusObj);
      
      authorization->status = acmeClientParseAuthorizationStatus(status);

      
      identifierObj = json_object_get(rootObj, "identifier");

      
      if(!json_is_object(identifierObj))
         break;

      
      valueObj = json_object_get(identifierObj, "value");

      
      if(!json_is_string(valueObj))
         break;

      
      value = json_string_value(valueObj);

      
      if(osStrlen(value) > ACME_CLIENT_MAX_URL_LEN)
         break;

      
      wildcardObj = json_object_get(rootObj, "wildcard");

      
      if(json_is_boolean(wildcardObj))
      {
         
         authorization->wildcard = json_boolean_value(wildcardObj);
      }

      
      challengeType = acmeClientGetChallengeType(context, value,
         authorization->wildcard);

      
      if(authorization->status == ACME_AUTH_STATUS_PENDING)
      {
         
         arrayObj = json_object_get(rootObj, "challenges");

         
         if(!json_is_array(arrayObj))
            break;

         
         n = json_array_size(arrayObj);

         
         for(i = 0; i < n; i++)
         {
            
            challengeObj = json_array_get(arrayObj, i);

            
            if(!json_is_object(challengeObj))
               break;

            
            typeObj = json_object_get(challengeObj, "type");
            urlObj = json_object_get(challengeObj, "url");
            statusObj = json_object_get(challengeObj, "status");

            
            if(!json_is_string(typeObj) ||
               !json_is_string(urlObj) ||
               !json_is_string(statusObj))
            {
               break;
            }

            
            type = json_string_value(typeObj);
            url = json_string_value(urlObj);
            status = json_string_value(statusObj);

            
            if(acmeClientParseChallengeType(type) == challengeType)
            {
               
               tokenObj = json_object_get(challengeObj, "token");

               
               if(!json_is_string(tokenObj))
                  break;

               
               token = json_string_value(tokenObj);

               
               if(osStrlen(url) <= ACME_CLIENT_MAX_URL_LEN &&
                  osStrlen(token) <= ACME_CLIENT_MAX_URL_LEN &&
                  osStrlen(value) <= ACME_CLIENT_MAX_NAME_LEN)
               {
                  
                  challenge = &context->challenges[context->numChallenges];

                  
                  challenge->status = acmeClientParseChallengeStatus(status);
                  
                  osStrcpy(challenge->url, url);
                  
                  osStrcpy(challenge->token, token);

                  
                  osStrcpy(challenge->identifier, value);
                  challenge->wildcard = authorization->wildcard;

                  
                  challenge->type = challengeType;

                  
                  
                  error = acmeClientGenerateKeyAuthorization(context, challenge);

                  
                  if(!error)
                  {
                     
                     if(challenge->type == ACME_CHALLENGE_TYPE_DNS_01)
                     {
                        
                        
                        error = acmeClientDigestKeyAuthorization(context,
                           challenge);
                     }
                     else if(challenge->type == ACME_CHALLENGE_TYPE_TLS_ALPN_01)
                     {
                        
                        
                        error = acmeClientGenerateTlsAlpnCert(context, challenge);
                     }
                     else
                     {
                        
                     }
                  }

                  
                  if(!error)
                  {
                     
                     context->numChallenges++;
                  }

                  
                  break;
               }
            }
         }
      }
      else
      {
         
         
         error = NO_ERROR;
      }

      
   } while(0);

   
   json_decref(rootObj);

   
   return error;
}




AcmeAuthStatus acmeClientParseAuthorizationStatus(const char_t *label)
{
   AcmeAuthStatus status;

   
   if(!osStrcmp(label, "pending"))
   {
      
      status = ACME_AUTH_STATUS_PENDING;
   }
   else if(!osStrcmp(label, "valid"))
   {
      
      
      status = ACME_AUTH_STATUS_VALID;
   }
   else if(!osStrcmp(label, "invalid"))
   {
      
      
      
      status = ACME_AUTH_STATUS_INVALID;
   }
   else if(!osStrcmp(label, "expired"))
   {
      
      status = ACME_AUTH_STATUS_EXPIRED;
   }
   else if(!osStrcmp(label, "deactivated"))
   {
      
      status = ACME_AUTH_STATUS_DEACTIVATED;
   }
   else if(!osStrcmp(label, "revoked"))
   {
      
      status = ACME_AUTH_STATUS_REVOKED;
   }
   else
   {
      
      status = ACME_AUTH_STATUS_INVALID;
   }

   
   return status;
}

#endif
