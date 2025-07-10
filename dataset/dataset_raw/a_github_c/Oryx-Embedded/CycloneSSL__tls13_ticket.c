


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include "tls.h"
#include "tls_misc.h"
#include "tls13_key_material.h"
#include "tls13_ticket.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED && TLS_MAX_VERSION >= TLS_VERSION_1_3)




bool_t tls13IsTicketValid(TlsContext *context)
{
   bool_t valid = FALSE;

   
   if(tlsGetHashAlgo(context->ticketHashAlgo) != NULL)
   {
      
      if(context->ticketPskLen > 0)
      {
         
         if(context->entity == TLS_CONNECTION_END_CLIENT)
         {
            
            if(context->ticket != NULL && context->ticketLen > 0)
            {
               valid = TRUE;
            }
         }
         else
         {
            valid = TRUE;
         }
      }
   }

   
   return valid;
}




error_t tls13SaveSessionTicket(const TlsContext *context,
   TlsSessionState *session)
{
   const HashAlgo *hashAlgo;

   
   if(context->version != TLS_VERSION_1_3)
      return ERROR_INVALID_VERSION;

   
   if(context->ticket == NULL || context->ticketLen == 0)
      return ERROR_INVALID_TICKET;

   
   if(context->cipherSuite.identifier == 0 ||
      context->cipherSuite.prfHashAlgo == NULL)
   {
      return ERROR_INVALID_SESSION;
   }

   
   hashAlgo = context->cipherSuite.prfHashAlgo;

   
   session->ticket = tlsAllocMem(context->ticketLen);
   
   if(session->ticket == NULL)
      return ERROR_OUT_OF_MEMORY;

   
   session->timestamp = osGetSystemTime();

   
   session->version = context->version;
   session->cipherSuite = context->cipherSuite.identifier;
   session->ticketTimestamp = context->ticketTimestamp;
   session->ticketLifetime = context->ticketLifetime;
   session->ticketAgeAdd = context->ticketAgeAdd;
   session->maxEarlyDataSize = context->maxEarlyDataSize;

   
   osMemcpy(session->ticket, context->ticket, context->ticketLen);
   session->ticketLen = context->ticketLen;

   
   
   if(hashAlgo == tlsGetHashAlgo(TLS_HASH_ALGO_SHA256))
   {
      session->ticketHashAlgo = TLS_HASH_ALGO_SHA256;
   }
   else if(hashAlgo == tlsGetHashAlgo(TLS_HASH_ALGO_SHA384))
   {
      session->ticketHashAlgo = TLS_HASH_ALGO_SHA384;
   }
   else
   {
      session->ticketHashAlgo = TLS_HASH_ALGO_NONE;
   }

   
   osMemcpy(session->secret, context->ticketPsk, hashAlgo->digestSize);

#if (TLS_ALPN_SUPPORT == ENABLED)
   
   if(context->selectedProtocol != NULL)
   {
      size_t n;

      
      n = osStrlen(context->selectedProtocol);

      
      session->ticketAlpn = tlsAllocMem(n + 1);
      
      if(session->ticketAlpn == NULL)
         return ERROR_OUT_OF_MEMORY;

      
      osStrcpy(session->ticketAlpn, context->selectedProtocol);
   }
#endif

   
   return NO_ERROR;
}




error_t tls13RestoreSessionTicket(TlsContext *context,
   const TlsSessionState *session)
{
   systime_t serverTicketAge;

   
   if(session->version != TLS_VERSION_1_3)
      return ERROR_INVALID_VERSION;

   
   if(session->ticket == NULL || session->ticketLen == 0)
      return ERROR_INVALID_TICKET;

   
   if(session->cipherSuite == 0 ||
      session->ticketHashAlgo == TLS_HASH_ALGO_NONE)
   {
      return ERROR_INVALID_SESSION;
   }

   
   serverTicketAge = osGetSystemTime() - session->ticketTimestamp;

   
   if(serverTicketAge >= (session->ticketLifetime * 1000))
      return ERROR_TICKET_EXPIRED;

   
   context->version = session->version;
   context->ticketCipherSuite = session->cipherSuite;
   context->ticketHashAlgo = session->ticketHashAlgo;
   context->ticketTimestamp = session->ticketTimestamp;
   context->ticketLifetime = session->ticketLifetime;
   context->ticketAgeAdd = session->ticketAgeAdd;
   context->maxEarlyDataSize = session->maxEarlyDataSize;
   context->sessionIdLen = 0;

   
   if(context->ticket != NULL)
   {
      osMemset(context->ticket, 0, context->ticketLen);
      tlsFreeMem(context->ticket);
      context->ticket = NULL;
      context->ticketLen = 0;
   }

   
   context->ticket = tlsAllocMem(session->ticketLen);
   
   if(context->ticket == NULL)
      return ERROR_OUT_OF_MEMORY;

   
   osMemcpy(context->ticket, session->ticket, session->ticketLen);
   context->ticketLen = session->ticketLen;

   
   
   if(session->ticketHashAlgo == TLS_HASH_ALGO_SHA256)
   {
      context->ticketPskLen = SHA256_DIGEST_SIZE;
   }
   else if(session->ticketHashAlgo == TLS_HASH_ALGO_SHA384)
   {
      context->ticketPskLen = SHA384_DIGEST_SIZE;
   }
   else
   {
      context->ticketPskLen = 0;
   }

   
   osMemcpy(context->ticketPsk, session->secret, context->ticketPskLen);

#if (TLS_ALPN_SUPPORT == ENABLED)
   
   if(context->ticketAlpn != NULL)
   {
      tlsFreeMem(context->ticketAlpn);
      context->ticketAlpn = NULL;
   }

   
   if(session->ticketAlpn != NULL)
   {
      size_t n;

      
      n = osStrlen(session->ticketAlpn);

      
      context->ticketAlpn = tlsAllocMem(n + 1);
      
      if(context->ticketAlpn == NULL)
         return ERROR_OUT_OF_MEMORY;

      
      osStrcpy(context->ticketAlpn, session->ticketAlpn);
   }
#endif

   
   return NO_ERROR;
}




error_t tls13GenerateTicket(TlsContext *context,
   const Tls13NewSessionTicket *message, uint8_t *ticket, size_t *length)
{
#if (TLS_TICKET_SUPPORT == ENABLED)
   error_t error;
   size_t n;
   Tls13PlaintextSessionState *state;
   const HashAlgo *hashAlgo;

   
   state = (Tls13PlaintextSessionState *) ticket;

   
   state->version = context->version;
   state->cipherSuite = context->cipherSuite.identifier;
   state->ticketTimestamp = osGetSystemTime();
   state->ticketLifetime = ntohl(message->ticketLifetime);
   state->ticketAgeAdd = ntohl(message->ticketAgeAdd);
   osMemcpy(state->ticketNonce, message->ticketNonce, message->ticketNonceLen);
   osMemset(state->ticketPsk, 0, TLS_MAX_HKDF_DIGEST_SIZE);

   
   hashAlgo = context->cipherSuite.prfHashAlgo;
   
   if(hashAlgo == NULL)
      return ERROR_FAILURE;

   
   error = tls13HkdfExpandLabel(hashAlgo, context->resumptionMasterSecret,
      hashAlgo->digestSize, "resumption", message->ticketNonce,
      message->ticketNonceLen, state->ticketPsk, hashAlgo->digestSize);
   
   if(error)
      return error;

   
   state->ticketPskLen = hashAlgo->digestSize;

   
   n = sizeof(Tls13PlaintextSessionState);

   
   if(context->ticketEncryptCallback == NULL)
      return ERROR_FAILURE;

   
   error = context->ticketEncryptCallback(context, (uint8_t *) state, n,
      ticket, length, context->ticketParam);
   
   if(error)
      return error;

   
   return NO_ERROR;
#else
   
   return ERROR_NOT_IMPLEMENTED;
#endif
}




error_t tls13VerifyTicket(TlsContext *context, const uint8_t *ticket,
   size_t length, uint32_t obfuscatedTicketAge)
{
#if (TLS_TICKET_SUPPORT == ENABLED)
   error_t error;
   systime_t serverTicketAge;
   Tls13PlaintextSessionState *state;
   const HashAlgo *hashAlgo;
#if (TLS13_EARLY_DATA_SUPPORT == ENABLED)
   systime_t delta;
   systime_t clientTicketAge;
#endif

   
   if(context->ticketDecryptCallback == NULL)
      return ERROR_DECRYPTION_FAILED;

   
   if(length == 0)
      return ERROR_DECRYPTION_FAILED;

   
   state = tlsAllocMem(length);
   
   if(state == NULL)
      return ERROR_OUT_OF_MEMORY;

   
   do
   {
      
      error = context->ticketDecryptCallback(context, ticket, length,
         (uint8_t *) state, &length, context->ticketParam);
      
      if(error)
         break;

      
      if(length != sizeof(Tls13PlaintextSessionState))
      {
         
         error = ERROR_INVALID_TICKET;
         break;
      }

      
      if(state->version != TLS_VERSION_1_3)
      {
         
         error = ERROR_INVALID_TICKET;
         break;
      }

      
      serverTicketAge = osGetSystemTime() - state->ticketTimestamp;

      
      if(serverTicketAge >= (state->ticketLifetime * 1000))
      {
         
         error = ERROR_INVALID_TICKET;
         break;
      }

#if (TLS13_EARLY_DATA_SUPPORT == ENABLED)
      
      
      clientTicketAge = obfuscatedTicketAge - state->ticketAgeAdd;

      
      
      if(clientTicketAge < serverTicketAge)
      {
         delta = serverTicketAge - clientTicketAge;
      }
      else
      {
         delta = clientTicketAge - serverTicketAge;
      }

      
      
      
      if(delta >= TLS13_TICKET_AGE_TOLERANCE)
      {
         
         
         
         context->earlyDataRejected = TRUE;
      }
#endif

      
      
      error = tlsSelectCipherSuite(context, state->cipherSuite);
      
      if(error)
         break;

      
      hashAlgo = context->cipherSuite.prfHashAlgo;
      
      if(hashAlgo == NULL)
      {
         
         error = ERROR_INVALID_TICKET;
         break;
      }

      
      if(state->ticketPskLen != hashAlgo->digestSize)
      {
         
         error = ERROR_INVALID_TICKET;
         break;
      }

      
      osMemcpy(context->ticketPsk, state->ticketPsk, state->ticketPskLen);
      context->ticketPskLen = state->ticketPskLen;

      
      if(hashAlgo == tlsGetHashAlgo(TLS_HASH_ALGO_SHA256))
      {
         context->ticketHashAlgo = TLS_HASH_ALGO_SHA256;
      }
      else if(hashAlgo == tlsGetHashAlgo(TLS_HASH_ALGO_SHA384))
      {
         context->ticketHashAlgo = TLS_HASH_ALGO_SHA384;
      }
      else
      {
         context->ticketHashAlgo = TLS_HASH_ALGO_NONE;
      }

      
   } while(0);

   
   osMemset(state, 0, length);
   tlsFreeMem(state);

   
   return error;
#else
   
   return ERROR_DECRYPTION_FAILED;
#endif
}

#endif
