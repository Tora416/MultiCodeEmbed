


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include <string.h>
#include "tls.h"
#include "tls_record.h"
#include "tls_record_encryption.h"
#include "tls_misc.h"
#include "ssl_misc.h"
#include "cipher_mode/cbc.h"
#include "aead/ccm.h"
#include "aead/gcm.h"
#include "aead/chacha20_poly1305.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED)




error_t tlsEncryptRecord(TlsContext *context,
   TlsEncryptionEngine *encryptionEngine, void *record)
{
   error_t error;

#if (TLS_CCM_CIPHER_SUPPORT == ENABLED || TLS_CCM_8_CIPHER_SUPPORT == ENABLED || \
   TLS_GCM_CIPHER_SUPPORT == ENABLED || TLS_CHACHA20_POLY1305_SUPPORT == ENABLED)
   
   if(encryptionEngine->cipherMode == CIPHER_MODE_CCM ||
      encryptionEngine->cipherMode == CIPHER_MODE_GCM ||
      encryptionEngine->cipherMode == CIPHER_MODE_CHACHA20_POLY1305)
   {
      
      error = tlsEncryptAeadRecord(context, encryptionEngine, record);
   }
   else
#endif
#if (TLS_CBC_CIPHER_SUPPORT == ENABLED)
   
   if(encryptionEngine->cipherMode == CIPHER_MODE_CBC)
   {
      
      error = tlsAppendMessageAuthCode(context, encryptionEngine, record);

      
      if(!error)
      {
         
         error = tlsEncryptCbcRecord(context, encryptionEngine, record);
      }
   }
   else
#endif
#if (TLS_STREAM_CIPHER_SUPPORT == ENABLED)
   
   if(encryptionEngine->cipherMode == CIPHER_MODE_STREAM)
   {
      
      error = tlsAppendMessageAuthCode(context, encryptionEngine, record);

      
      if(!error)
      {
         
         error = tlsEncryptStreamRecord(context, encryptionEngine, record);
      }
   }
   else
#endif
#if (TLS_NULL_CIPHER_SUPPORT == ENABLED)
   
   if(encryptionEngine->cipherMode == CIPHER_MODE_NULL)
   {
      
      error = tlsAppendMessageAuthCode(context, encryptionEngine, record);
   }
   else
#endif
   
   {
      
      error = ERROR_UNSUPPORTED_CIPHER_MODE;
   }

   
   return error;
}




error_t tlsEncryptAeadRecord(TlsContext *context,
   TlsEncryptionEngine *encryptionEngine, void *record)
{
#if (TLS_CCM_CIPHER_SUPPORT == ENABLED || TLS_CCM_8_CIPHER_SUPPORT == ENABLED || \
   TLS_GCM_CIPHER_SUPPORT == ENABLED || TLS_CHACHA20_POLY1305_SUPPORT == ENABLED)
   error_t error;
   size_t length;
   size_t aadLen;
   size_t nonceLen;
   uint8_t *tag;
   uint8_t *data;
   uint8_t aad[13];
   uint8_t nonce[12];

   
   length = tlsGetRecordLength(context, record);
   
   data = tlsGetRecordData(context, record);

   
   TRACE_DEBUG("Record to be encrypted (%" PRIuSIZE " bytes):\r\n", length);
   TRACE_DEBUG_ARRAY("  ", record, length + sizeof(TlsRecord));

   
   if(encryptionEngine->version == TLS_VERSION_1_3)
   {
      
      
      data[length++] = tlsGetRecordType(context, record);

      
      
      tlsSetRecordType(context, record, TLS_TYPE_APPLICATION_DATA);

      
      tlsSetRecordLength(context, record, length +
         encryptionEngine->authTagLen);
   }

   
   tlsFormatAad(context, encryptionEngine, record, aad, &aadLen);

   
   if(encryptionEngine->recordIvLen != 0)
   {
      
      osMemmove(data + encryptionEngine->recordIvLen, data, length);

      
      
      error = context->prngAlgo->read(context->prngContext, data,
         encryptionEngine->recordIvLen);
      
      if(error)
         return error;
   }

   
   tlsFormatNonce(context, encryptionEngine, record, data, nonce,
      &nonceLen);

   
   data += encryptionEngine->recordIvLen;
   
   tag = data + length;

#if (TLS_CCM_CIPHER_SUPPORT == ENABLED || TLS_CCM_8_CIPHER_SUPPORT == ENABLED)
   
   if(encryptionEngine->cipherMode == CIPHER_MODE_CCM)
   {
      
      error = ccmEncrypt(encryptionEngine->cipherAlgo,
         encryptionEngine->cipherContext, nonce, nonceLen, aad, aadLen,
         data, data, length, tag, encryptionEngine->authTagLen);
   }
   else
#endif
#if (TLS_GCM_CIPHER_SUPPORT == ENABLED)
   
   if(encryptionEngine->cipherMode == CIPHER_MODE_GCM)
   {
      
      error = gcmEncrypt(encryptionEngine->gcmContext, nonce, nonceLen,
         aad, aadLen, data, data, length, tag, encryptionEngine->authTagLen);
   }
   else
#endif
#if (TLS_CHACHA20_POLY1305_SUPPORT == ENABLED)
   
   if(encryptionEngine->cipherMode == CIPHER_MODE_CHACHA20_POLY1305)
   {
      
      error = chacha20Poly1305Encrypt(encryptionEngine->encKey,
         encryptionEngine->encKeyLen, nonce, nonceLen, aad, aadLen,
         data, data, length, tag, encryptionEngine->authTagLen);
   }
   else
#endif
   
   {
      
      error = ERROR_UNSUPPORTED_CIPHER_MODE;
   }

   
   if(error)
      return error;

   
   length += encryptionEngine->recordIvLen + encryptionEngine->authTagLen;
   
   tlsSetRecordLength(context, record, length);

   
   tlsIncSequenceNumber(&encryptionEngine->seqNum);

   
   TRACE_DEBUG("Encrypted record (%" PRIuSIZE " bytes):\r\n", length);
   TRACE_DEBUG_ARRAY("  ", record, length + sizeof(TlsRecord));

   
   return NO_ERROR;
#else
   
   return ERROR_UNSUPPORTED_CIPHER_MODE;
#endif
}




error_t tlsEncryptCbcRecord(TlsContext *context,
   TlsEncryptionEngine *encryptionEngine, void *record)
{
#if (TLS_CBC_CIPHER_SUPPORT == ENABLED)
   error_t error;
   size_t i;
   size_t length;
   size_t paddingLen;
   uint8_t *data;
   const CipherAlgo *cipherAlgo;

   
   cipherAlgo = encryptionEngine->cipherAlgo;

   
   length = tlsGetRecordLength(context, record);
   
   data = tlsGetRecordData(context, record);

   
   TRACE_DEBUG("Record to be encrypted (%" PRIuSIZE " bytes):\r\n", length);
   TRACE_DEBUG_ARRAY("  ", record, length + sizeof(TlsRecord));

#if (TLS_MAX_VERSION >= TLS_VERSION_1_1 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
   
   if(encryptionEngine->version >= TLS_VERSION_1_1)
   {
      
      osMemmove(data + encryptionEngine->recordIvLen, data, length);

      
      error = context->prngAlgo->read(context->prngContext, data,
         encryptionEngine->recordIvLen);
      
      if(error)
         return error;

      
      length += encryptionEngine->recordIvLen;
   }
#endif

   
   paddingLen = (length + 1) % cipherAlgo->blockSize;

   
   
   if(paddingLen > 0)
      paddingLen = cipherAlgo->blockSize - paddingLen;

   
   for(i = 0; i <= paddingLen; i++)
   {
      data[length + i] = (uint8_t) paddingLen;
   }

   
   length += paddingLen + 1;
   
   tlsSetRecordLength(context, record, length);

   
   TRACE_DEBUG("Record with padding (%" PRIuSIZE " bytes):\r\n", length);
   TRACE_DEBUG_ARRAY("  ", record, length + sizeof(TlsRecord));

   
   error = cbcEncrypt(cipherAlgo, encryptionEngine->cipherContext,
      encryptionEngine->iv, data, data, length);
   
   if(error)
      return error;

   
   TRACE_DEBUG("Encrypted record (%" PRIuSIZE " bytes):\r\n", length);
   TRACE_DEBUG_ARRAY("  ", record, length + sizeof(TlsRecord));

   
   return NO_ERROR;
#else
   
   return ERROR_UNSUPPORTED_CIPHER_MODE;
#endif
}




error_t tlsEncryptStreamRecord(TlsContext *context,
   TlsEncryptionEngine *encryptionEngine, void *record)
{
#if (TLS_STREAM_CIPHER_SUPPORT == ENABLED)
   size_t length;
   uint8_t *data;

   
   length = tlsGetRecordLength(context, record);
   
   data = tlsGetRecordData(context, record);

   
   TRACE_DEBUG("Record to be encrypted (%" PRIuSIZE " bytes):\r\n", length);
   TRACE_DEBUG_ARRAY("  ", record, length + sizeof(TlsRecord));

   
   encryptionEngine->cipherAlgo->encryptStream(
      encryptionEngine->cipherContext, data, data, length);

   
   TRACE_DEBUG("Encrypted record (%" PRIuSIZE " bytes):\r\n", length);
   TRACE_DEBUG_ARRAY("  ", record, length + sizeof(TlsRecord));

   
   return NO_ERROR;
#else
   
   return ERROR_UNSUPPORTED_CIPHER_MODE;
#endif
}




error_t tlsAppendMessageAuthCode(TlsContext *context,
   TlsEncryptionEngine *encryptionEngine, void *record)
{
   error_t error;
   size_t length;
   uint8_t *data;

   
   length = tlsGetRecordLength(context, record);
   
   data = tlsGetRecordData(context, record);

#if (TLS_MAX_VERSION >= SSL_VERSION_3_0 && TLS_MIN_VERSION <= SSL_VERSION_3_0)
   
   if(encryptionEngine->version == SSL_VERSION_3_0)
   {
      
      error = sslComputeMac(encryptionEngine, record, data, length,
         data + length);
   }
   else
#endif
#if (TLS_MAX_VERSION >= TLS_VERSION_1_0 && TLS_MIN_VERSION <= TLS_VERSION_1_2)
   
   if(encryptionEngine->version >= TLS_VERSION_1_0 &&
      encryptionEngine->version <= TLS_VERSION_1_2)
   {
      
      error = tlsComputeMac(context, encryptionEngine, record, data,
         length, data + length);
   }
   else
#endif
#if (TLS_MAX_VERSION >= TLS_VERSION_1_3 && TLS_MIN_VERSION <= TLS_VERSION_1_3)
   
   if(encryptionEngine->version == TLS_VERSION_1_3)
   {
      
      
      data[length++] = tlsGetRecordType(context, record);

      
      
      tlsSetRecordType(context, record, TLS_TYPE_APPLICATION_DATA);

      
      tlsSetRecordLength(context, record, length +
         encryptionEngine->hashAlgo->digestSize);

      
      error = tls13ComputeMac(context, encryptionEngine, record, data,
         length, data + length);
   }
   else
#endif
   
   {
      
      error = ERROR_INVALID_VERSION;
   }

   
   if(error)
      return error;

   
   TRACE_DEBUG("Write sequence number:\r\n");
   TRACE_DEBUG_ARRAY("  ", &encryptionEngine->seqNum, sizeof(TlsSequenceNumber));
   TRACE_DEBUG("Computed MAC:\r\n");
   TRACE_DEBUG_ARRAY("  ", data + length, encryptionEngine->hashAlgo->digestSize);

   
   length += encryptionEngine->hashAlgo->digestSize;
   
   tlsSetRecordLength(context, record, length);

   
   tlsIncSequenceNumber(&encryptionEngine->seqNum);

   
   return NO_ERROR;
}




error_t tlsComputeMac(TlsContext *context, TlsEncryptionEngine *encryptionEngine,
   void *record, const uint8_t *data, size_t dataLen, uint8_t *mac)
{
   HmacContext *hmacContext;

   
   hmacContext = encryptionEngine->hmacContext;

   
   hmacInit(hmacContext, encryptionEngine->hashAlgo,
      encryptionEngine->macKey, encryptionEngine->macKeyLen);

#if (DTLS_SUPPORT == ENABLED)
   
   if(context->transportProtocol == TLS_TRANSPORT_PROTOCOL_DATAGRAM)
   {
      const DtlsRecord *dtlsRecord;

      
      dtlsRecord = (DtlsRecord *) record;

      
      
      hmacUpdate(hmacContext, (void *) &dtlsRecord->epoch, 2);
      hmacUpdate(hmacContext, &dtlsRecord->seqNum, 6);

      
      hmacUpdate(hmacContext, &dtlsRecord->type, 3);
      hmacUpdate(hmacContext, (void *) &dtlsRecord->length, 2);
      hmacUpdate(hmacContext, data, dataLen);
   }
   else
#endif
   
   {
      const TlsRecord *tlsRecord;

      
      tlsRecord = (TlsRecord *) record;

      
      hmacUpdate(hmacContext, &encryptionEngine->seqNum,
         sizeof(TlsSequenceNumber));

      
      hmacUpdate(hmacContext, tlsRecord, sizeof(TlsRecord));
      hmacUpdate(hmacContext, data, dataLen);
   }

   
   hmacFinal(hmacContext, mac);

   
   return NO_ERROR;
}

#endif
