


#define TRACE_LEVEL ACME_DNS_TRACE_LEVEL


#include "dns_api/acme_dns_client.h"
#include "dns_api/acme_dns_client_misc.h"
#include "jansson.h"
#include "debug.h"


#if (ACME_DNS_CLIENT_SUPPORT == ENABLED)




error_t acmeDnsClientFormatRegisterRequest(AcmeDnsClientContext *context)
{
   bool_t defaultPort;

   
   httpClientCreateRequest(&context->httpClientContext);
   httpClientSetMethod(&context->httpClientContext, "POST");
   httpClientSetUri(&context->httpClientContext, "/register");

#if (ACME_DNS_CLIENT_TLS_SUPPORT == ENABLED)
   
   if(context->tlsInitCallback != NULL)
   {
      
      defaultPort = (context->serverPort == HTTPS_PORT) ? TRUE : FALSE;
   }
   else
#endif
   
   {
      
      defaultPort = (context->serverPort == HTTP_PORT) ? TRUE : FALSE;
   }

   
   
   if(defaultPort)
   {
      
      
      httpClientAddHeaderField(&context->httpClientContext, "Host",
         context->serverName);
   }
   else
   {
      
      httpClientFormatHeaderField(&context->httpClientContext,
         "Host", "%s:%" PRIu16, context->serverName, context->serverPort);
   }

   
   httpClientAddHeaderField(&context->httpClientContext, "User-Agent",
      "Mozilla/5.0");

   httpClientAddHeaderField(&context->httpClientContext, "Content-Type",
      "application/json");

   
   httpClientSetContentLength(&context->httpClientContext, 0);

   
   return NO_ERROR;
}




error_t acmeDnsClientParseRegisterResponse(AcmeDnsClientContext *context)
{
   error_t error;
   const char_t *username;
   const char_t *password;
   const char_t *subDomain;
   const char_t *fullDomain;
   json_t *rootObj;
   json_t *usernameObj;
   json_t *passwordObj;
   json_t *subDomainObj;
   json_t *fullDomainObj;

   
   if(!HTTP_STATUS_CODE_2YZ(context->statusCode))
      return ERROR_UNEXPECTED_STATUS;

   
   if(context->bufferLen >= ACME_DNS_CLIENT_BUFFER_SIZE)
      return ERROR_RESPONSE_TOO_LARGE;

   
   error = ERROR_INVALID_RESPONSE;

   
   context->username[0] = '\0';
   context->password[0] = '\0';
   context->subDomain[0] = '\0';
   context->fullDomain[0] = '\0';

   
   rootObj = json_loads(context->buffer, 0, NULL);

   
   if(json_is_object(rootObj))
   {
      
      
      usernameObj = json_object_get(rootObj, "username");
      passwordObj = json_object_get(rootObj, "password");
      subDomainObj = json_object_get(rootObj, "subdomain");
      fullDomainObj = json_object_get(rootObj, "fulldomain");

      
      if(json_is_string(usernameObj) &&
         json_is_string(passwordObj) &&
         json_is_string(subDomainObj) &&
         json_is_string(fullDomainObj))
      {
         
         username = json_string_value(usernameObj);
         password = json_string_value(passwordObj);
         subDomain = json_string_value(subDomainObj);
         fullDomain = json_string_value(fullDomainObj);

         
         if(osStrlen(username) <= ACME_DNS_CLIENT_MAX_USERNAME_LEN &&
            osStrlen(password) <= ACME_DNS_CLIENT_MAX_PASSWORD_LEN &&
            osStrlen(subDomain) <= ACME_DNS_CLIENT_MAX_SUB_DOMAIN_LEN &&
            osStrlen(fullDomain) <= ACME_DNS_CLIENT_MAX_FULL_DOMAIN_LEN)
         {
            
            osStrcpy(context->username, username);
            osStrcpy(context->password, password);
            osStrcpy(context->subDomain, subDomain);
            osStrcpy(context->fullDomain, fullDomain);

            
            error = NO_ERROR;
         }
      }
   }

   
   json_decref(rootObj);

   
   return error;
}




error_t acmeDnsClientFormatUpdateRequest(AcmeDnsClientContext *context,
   const char_t *txt)
{
   bool_t defaultPort;

   
   if(osStrlen(txt) != ACME_DNS_TXT_RECORD_LEN)
      return ERROR_INVALID_LENGTH;

   
   httpClientCreateRequest(&context->httpClientContext);
   httpClientSetMethod(&context->httpClientContext, "POST");
   httpClientSetUri(&context->httpClientContext, "/update");

#if (ACME_DNS_CLIENT_TLS_SUPPORT == ENABLED)
   
   if(context->tlsInitCallback != NULL)
   {
      
      defaultPort = (context->serverPort == HTTPS_PORT) ? TRUE : FALSE;
   }
   else
#endif
   
   {
      
      defaultPort = (context->serverPort == HTTP_PORT) ? TRUE : FALSE;
   }

   
   
   if(defaultPort)
   {
      
      
      httpClientAddHeaderField(&context->httpClientContext, "Host",
         context->serverName);
   }
   else
   {
      
      httpClientFormatHeaderField(&context->httpClientContext,
         "Host", "%s:%" PRIu16, context->serverName, context->serverPort);
   }

   
   httpClientAddHeaderField(&context->httpClientContext, "User-Agent",
      "Mozilla/5.0");

   httpClientAddHeaderField(&context->httpClientContext, "X-Api-User",
      context->username);

   httpClientAddHeaderField(&context->httpClientContext, "X-Api-Key",
      context->password);

   httpClientAddHeaderField(&context->httpClientContext, "Content-Type",
      "application/json");

   
   context->bufferLen = osSprintf(context->buffer,
      "{\"subdomain\":\"%s\",\"txt\":\"%s\"}", context->subDomain, txt);

   
   httpClientSetContentLength(&context->httpClientContext, context->bufferLen);

   
   return NO_ERROR;
}




error_t acmeDnsClientParseUpdateResponse(AcmeDnsClientContext *context)
{
   
   if(!HTTP_STATUS_CODE_2YZ(context->statusCode))
      return ERROR_UNEXPECTED_STATUS;

   
   if(context->bufferLen >= ACME_DNS_CLIENT_BUFFER_SIZE)
      return ERROR_RESPONSE_TOO_LARGE;

   
   return NO_ERROR;
}

#endif
