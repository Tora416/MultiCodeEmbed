


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include <string.h>
#include "tls.h"
#include "tls_cache.h"
#include "tls_misc.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED)




TlsCache *tlsInitCache(uint_t size)
{
   size_t n;
   TlsCache *cache;

   
   if(size < 1)
      return NULL;

   
   n = sizeof(TlsCache) + size * sizeof(TlsSessionState);

   
   cache = tlsAllocMem(n);
   
   if(cache == NULL)
      return NULL;

   
   osMemset(cache, 0, n);

   
   if(!osCreateMutex(&cache->mutex))
   {
      
      tlsFreeMem(cache);
      
      return NULL;
   }

   
   cache->size = size;

   
   return cache;
}




TlsSessionState *tlsFindCache(TlsCache *cache, const uint8_t *sessionId,
   size_t sessionIdLen)
{
#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
   uint_t i;
   systime_t time;
   TlsSessionState *session;

   
   if(cache == NULL || sessionId == NULL || sessionIdLen == 0)
      return NULL;

   
   session = NULL;

   
   time = osGetSystemTime();

   
   osAcquireMutex(&cache->mutex);

   
   for(i = 0; i < cache->size; i++)
   {
      
      if(cache->sessions[i].sessionIdLen != 0)
      {
         
         if((time - cache->sessions[i].timestamp) >= TLS_SESSION_CACHE_LIFETIME)
         {
            
            tlsFreeSessionState(&cache->sessions[i]);
         }
      }
   }

   
   for(i = 0; i < cache->size; i++)
   {
      
      if(cache->sessions[i].sessionIdLen == sessionIdLen &&
         !osMemcmp(cache->sessions[i].sessionId, sessionId, sessionIdLen))
      {
         
         session = &cache->sessions[i];
         break;
      }
   }

   
   osReleaseMutex(&cache->mutex);

   
   return session;
#else
   
   return NULL;
#endif
}




error_t tlsSaveToCache(TlsContext *context)
{
#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
   error_t error;
   uint_t i;
   systime_t time;
   TlsSessionState *session;
   TlsSessionState *firstFreeEntry;
   TlsSessionState *oldestEntry;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   if(context->cache == NULL)
      return ERROR_FAILURE;

   
   if(context->sessionIdLen == 0)
      return NO_ERROR;

   
   osAcquireMutex(&context->cache->mutex);

   
   time = osGetSystemTime();

   
   firstFreeEntry = NULL;
   
   oldestEntry = NULL;

   
   for(i = 0; i < context->cache->size; i++)
   {
      
      session = &context->cache->sessions[i];

      
      if(session->sessionIdLen == context->sessionIdLen &&
         !osMemcmp(session->sessionId, context->sessionId, session->sessionIdLen))
      {
         
         firstFreeEntry = NULL;
         oldestEntry = NULL;
         
         break;
      }

      
      if(session->sessionIdLen == 0)
      {
         
         if(!firstFreeEntry)
         {
            firstFreeEntry = session;
         }
      }
      else
      {
         
         if(oldestEntry == NULL)
         {
            oldestEntry = session;
         }
         else if((time - session->timestamp) > (time - oldestEntry->timestamp))
         {
            oldestEntry = session;
         }
      }
   }

   
   if(firstFreeEntry != NULL)
   {
      error = tlsSaveSessionId(context, firstFreeEntry);
   }
   else if(oldestEntry != NULL)
   {
      error = tlsSaveSessionId(context, oldestEntry);
   }
   else
   {
      error = NO_ERROR;
   }

   
   osReleaseMutex(&context->cache->mutex);

   
   return error;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t tlsRemoveFromCache(TlsContext *context)
{
#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
   uint_t i;
   TlsSessionState *session;

   
   if(context == NULL)
      return ERROR_INVALID_PARAMETER;

   
   if(context->cache == NULL)
      return ERROR_FAILURE;

   
   if(context->sessionIdLen == 0)
      return NO_ERROR;

   
   osAcquireMutex(&context->cache->mutex);

   
   for(i = 0; i < context->cache->size; i++)
   {
      
      session = &context->cache->sessions[i];

      
      if(session->sessionIdLen == context->sessionIdLen &&
         !osMemcmp(session->sessionId, context->sessionId, session->sessionIdLen))
      {
         
         tlsFreeSessionState(session);
      }
   }

   
   osReleaseMutex(&context->cache->mutex);
#endif

   
   return NO_ERROR;
}




void tlsFreeCache(TlsCache *cache)
{
   uint_t i;

   
   if(cache != NULL)
   {
      
      for(i = 0; i < cache->size; i++)
      {
         
         tlsFreeSessionState(&cache->sessions[i]);
      }

      
      osDeleteMutex(&cache->mutex);

      
      tlsFreeMem(cache);
   }
}

#endif
