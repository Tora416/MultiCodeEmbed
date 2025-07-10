


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include <string.h>
#include "tls.h"
#include "tls_ticket.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED && TLS_TICKET_SUPPORT == ENABLED)




error_t tlsInitTicketContext(TlsTicketContext *ticketContext)
{
   
   if(ticketContext == NULL)
      return ERROR_INVALID_PARAMETER;

   
   osMemset(ticketContext, 0, sizeof(TlsTicketContext));

   
   if(!osCreateMutex(&ticketContext->mutex))
   {
      
      return ERROR_OUT_OF_RESOURCES;
   }

   
   return NO_ERROR;
}




error_t tlsEncryptTicket(TlsContext *context, const uint8_t *plaintext,
   size_t plaintextLen, uint8_t *ciphertext, size_t *ciphertextLen, void *param)
{
   error_t error;
   uint8_t *iv;
   uint8_t *data;
   uint8_t *tag;
   systime_t time;
   TlsTicketContext *ticketContext;
   TlsTicketEncryptionState *state;

   
   if(context == NULL || param == NULL)
      return ERROR_INVALID_PARAMETER;
   if(plaintext == NULL || ciphertext == NULL || ciphertextLen == NULL)
      return ERROR_INVALID_PARAMETER;

   
   error = NO_ERROR;

   
   iv = NULL;
   data = NULL;
   tag = NULL;

   
   ticketContext = (TlsTicketContext *) param;

   
   osAcquireMutex(&ticketContext->mutex);

   
   tlsCheckTicketKeyLifetime(&ticketContext->encryptionState);
   tlsCheckTicketKeyLifetime(&ticketContext->prevEncryptionState);

   
   state = &ticketContext->encryptionState;

   
   if(state->valid)
   {
      
      time = osGetSystemTime();

      
      if((time - state->timestamp) >= TLS_TICKET_LIFETIME)
      {
         
         ticketContext->prevEncryptionState = ticketContext->encryptionState;
         ticketContext->encryptionState.valid = FALSE;
      }
   }

   
   if(!state->valid)
   {
      
      error = tlsGenerateTicketKeys(ticketContext, context->prngAlgo,
         context->prngContext);
   }

   
   if(!error)
   {
      
      iv = ciphertext + TLS_TICKET_KEY_NAME_SIZE;
      
      data = iv + TLS_TICKET_IV_SIZE;
      
      tag = data + plaintextLen;

      
      osMemmove(data, plaintext, plaintextLen);
      
      osMemcpy(ciphertext, state->keyName, TLS_TICKET_KEY_NAME_SIZE);

      
      error = context->prngAlgo->read(context->prngContext, iv,
         TLS_TICKET_IV_SIZE);
   }

   
   if(!error)
   {
      
      error = aesInit(&ticketContext->aesContext, state->key,
         TLS_TICKET_KEY_SIZE);
   }

   
   if(!error)
   {
      
      error = gcmInit(&ticketContext->gcmContext, AES_CIPHER_ALGO,
         &ticketContext->aesContext);
   }

   
   if(!error)
   {
      
      *ciphertextLen = plaintextLen + TLS_TICKET_KEY_NAME_SIZE +
         TLS_TICKET_IV_SIZE + TLS_TICKET_TAG_SIZE;

      
      error = gcmEncrypt(&ticketContext->gcmContext, iv, TLS_TICKET_IV_SIZE,
         state->keyName, TLS_TICKET_KEY_NAME_SIZE, data, data, plaintextLen,
         tag, TLS_TICKET_TAG_SIZE);
   }

   
   osReleaseMutex(&ticketContext->mutex);

   
   return error;
}




error_t tlsDecryptTicket(TlsContext *context, const uint8_t *ciphertext,
   size_t ciphertextLen, uint8_t *plaintext, size_t *plaintextLen, void *param)
{
   error_t error;
   const uint8_t *iv;
   const uint8_t *data;
   const uint8_t *tag;
   TlsTicketContext *ticketContext;
   TlsTicketEncryptionState *state;

   
   if(context == NULL || param == NULL)
      return ERROR_INVALID_PARAMETER;
   if(ciphertext == NULL || plaintext == NULL || plaintextLen == NULL)
      return ERROR_INVALID_PARAMETER;

   
   if(ciphertextLen < (TLS_TICKET_KEY_NAME_SIZE + TLS_TICKET_IV_SIZE +
      TLS_TICKET_TAG_SIZE))
   {
      
      return ERROR_DECRYPTION_FAILED;
   }

   
   error = NO_ERROR;

   
   iv = NULL;
   data = NULL;
   tag = NULL;
   state = NULL;

   
   ticketContext = (TlsTicketContext *) param;

   
   osAcquireMutex(&ticketContext->mutex);

   
   tlsCheckTicketKeyLifetime(&ticketContext->encryptionState);
   tlsCheckTicketKeyLifetime(&ticketContext->prevEncryptionState);

   
   if(tlsCompareTicketKeyName(ciphertext, ciphertextLen,
      &ticketContext->encryptionState))
   {
      
      state = &ticketContext->encryptionState;
   }
   else if(tlsCompareTicketKeyName(ciphertext, ciphertextLen,
      &ticketContext->prevEncryptionState))
   {
      
      state = &ticketContext->prevEncryptionState;
   }
   else
   {
      
      error = ERROR_DECRYPTION_FAILED;
   }

   
   if(!error)
   {
      
      iv = ciphertext + TLS_TICKET_KEY_NAME_SIZE;
      
      data = iv + TLS_TICKET_IV_SIZE;
      
      tag = ciphertext + ciphertextLen - TLS_TICKET_TAG_SIZE;

      
      *plaintextLen = ciphertextLen - TLS_TICKET_KEY_NAME_SIZE -
         TLS_TICKET_IV_SIZE - TLS_TICKET_TAG_SIZE;

      
      error = aesInit(&ticketContext->aesContext, state->key,
         TLS_TICKET_KEY_SIZE);
   }

   
   if(!error)
   {
      
      error = gcmInit(&ticketContext->gcmContext, AES_CIPHER_ALGO,
         &ticketContext->aesContext);
   }

   
   if(!error)
   {
      
      error = gcmDecrypt(&ticketContext->gcmContext, iv, TLS_TICKET_IV_SIZE,
         state->keyName, TLS_TICKET_KEY_NAME_SIZE, data, plaintext,
         *plaintextLen, tag, TLS_TICKET_TAG_SIZE);
   }

   
   osReleaseMutex(&ticketContext->mutex);

   
   return error;
}




error_t tlsGenerateTicketKeys(TlsTicketContext *ticketContext,
   const PrngAlgo *prngAlgo, void *prngContext)
{
   error_t error;
   TlsTicketEncryptionState *state;

   
   state = &ticketContext->encryptionState;

   
   state->valid = FALSE;

   
   
   error = prngAlgo->read(prngContext, state->keyName,
      TLS_TICKET_KEY_NAME_SIZE);
   
   if(error)
      return error;

   
   error = prngAlgo->read(prngContext, state->key, TLS_TICKET_KEY_SIZE);
   
   if(error)
      return error;

   
   state->timestamp = osGetSystemTime();
   
   state->valid = TRUE;

   
   return NO_ERROR;
}




void tlsCheckTicketKeyLifetime(TlsTicketEncryptionState *state)
{
   systime_t time;

   
   time = osGetSystemTime();

   
   if(state->valid)
   {
      
      if((time - state->timestamp) >= (2 * TLS_TICKET_LIFETIME))
      {
         
         osMemset(state, 0, sizeof(TlsTicketEncryptionState));
      }
   }
}




bool_t tlsCompareTicketKeyName(const uint8_t *ticket, size_t ticketLen,
   const TlsTicketEncryptionState *state)
{
   bool_t res;

   
   res = FALSE;

   
   if(state->valid)
   {
      
      
      if(ticketLen >= TLS_TICKET_KEY_NAME_SIZE)
      {
         
         if(osMemcmp(ticket, state->keyName, TLS_TICKET_KEY_NAME_SIZE) == 0)
         {
            
            res = TRUE;
         }
      }
   }

   
   return res;
}




void tlsFreeTicketContext(TlsTicketContext *ticketContext)
{
   
   if(ticketContext != NULL)
   {
      
      osDeleteMutex(&ticketContext->mutex);

      
      osMemset(ticketContext, 0, sizeof(TlsTicketContext));
   }
}

#endif
