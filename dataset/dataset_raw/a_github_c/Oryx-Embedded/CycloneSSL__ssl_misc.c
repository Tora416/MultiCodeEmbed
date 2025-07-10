


#define TRACE_LEVEL TLS_TRACE_LEVEL


#include <string.h>
#include "core/crypto.h"
#include "tls.h"
#include "ssl_misc.h"
#include "debug.h"


#if (TLS_SUPPORT == ENABLED && TLS_MIN_VERSION <= SSL_VERSION_3_0)


const uint8_t sslPad1[48] =
{
   0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
   0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36,
   0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36, 0x36
};


const uint8_t sslPad2[48] =
{
   0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C,
   0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C,
   0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C, 0x5C
};




error_t sslExpandKey(const uint8_t *secret, size_t secretLen,
   const uint8_t *random, size_t randomLen, uint8_t *output, size_t outputLen)
{
   uint_t i;
   size_t n;
   char_t pad[16];
   Md5Context *md5Context;
   Sha1Context *sha1Context;

   
   if(outputLen > (sizeof(pad) * MD5_DIGEST_SIZE))
      return ERROR_INVALID_LENGTH;

   
   md5Context = tlsAllocMem(sizeof(Md5Context));
   
   if(md5Context == NULL)
   {
      
      return ERROR_OUT_OF_MEMORY;
   }

   
   sha1Context = tlsAllocMem(sizeof(Sha1Context));
   
   if(sha1Context == NULL)
   {
      
      tlsFreeMem(md5Context);
      
      return ERROR_OUT_OF_MEMORY;
   }

   
   for(i = 0; outputLen > 0; i++)
   {
      
      osMemset(pad, 'A' + i, i + 1);

      
      sha1Init(sha1Context);
      sha1Update(sha1Context, pad, i + 1);
      sha1Update(sha1Context, secret, secretLen);
      sha1Update(sha1Context, random, randomLen);
      sha1Final(sha1Context, NULL);

      
      md5Init(md5Context);
      md5Update(md5Context, secret, secretLen);
      md5Update(md5Context, sha1Context->digest, SHA1_DIGEST_SIZE);
      md5Final(md5Context, NULL);

      
      n = MIN(outputLen, MD5_DIGEST_SIZE);
      
      osMemcpy(output, md5Context->digest, n);

      
      output += n;
      
      outputLen -= n;
   }

   
   tlsFreeMem(md5Context);
   tlsFreeMem(sha1Context);

   
   return NO_ERROR;
}




error_t sslComputeMac(TlsEncryptionEngine *encryptionEngine,
   const TlsRecord *record, const uint8_t *data, size_t dataLen, uint8_t *mac)
{
   size_t padLen;
   const HashAlgo *hashAlgo;
   HashContext *hashContext;

   
   hashAlgo = encryptionEngine->hashAlgo;
   
   hashContext = (HashContext *) encryptionEngine->hmacContext->hashContext;

   
   if(hashAlgo == MD5_HASH_ALGO)
   {
      
      padLen = 48;
   }
   else if(hashAlgo == SHA1_HASH_ALGO)
   {
      
      padLen = 40;
   }
   else
   {
      
      return ERROR_INVALID_PARAMETER;
   }

   
   hashAlgo->init(hashContext);
   hashAlgo->update(hashContext, encryptionEngine->macKey, encryptionEngine->macKeyLen);
   hashAlgo->update(hashContext, sslPad1, padLen);
   hashAlgo->update(hashContext, &encryptionEngine->seqNum, sizeof(TlsSequenceNumber));
   hashAlgo->update(hashContext, &record->type, sizeof(record->type));
   hashAlgo->update(hashContext, (void *) &record->length, sizeof(record->length));
   hashAlgo->update(hashContext, data, dataLen);
   hashAlgo->final(hashContext, mac);

   
   hashAlgo->init(hashContext);
   hashAlgo->update(hashContext, encryptionEngine->macKey, encryptionEngine->macKeyLen);
   hashAlgo->update(hashContext, sslPad2, padLen);
   hashAlgo->update(hashContext, mac, hashAlgo->digestSize);
   hashAlgo->final(hashContext, mac);

   
   return NO_ERROR;
}




uint32_t sslVerifyPadding(TlsEncryptionEngine *decryptionEngine,
   const uint8_t *data, size_t dataLen, size_t *paddingLen)
{
   size_t i;
   size_t n;
   uint8_t b;
   uint8_t mask;
   uint32_t c;
   uint32_t bad;
   uint32_t bad1;
   uint32_t bad2;

   
   n = data[dataLen - 1];

   
   bad = CRYPTO_TEST_GTE_32(n, dataLen);

   
   
   bad |= CRYPTO_TEST_GTE_32(n, decryptionEngine->cipherAlgo->blockSize);

   
   
   for(bad1 = 0, i = 1; i < dataLen && i < 256; i++)
   {
      
      b = data[dataLen - 1 - i];

      
      c = CRYPTO_TEST_LTE_32(i, n);
      mask = CRYPTO_SELECT_8(b, n, c);
      bad1 |= CRYPTO_TEST_NEQ_8(b, mask);
   }

   
   
   for(bad2 = 0, i = 1; i < dataLen && i < 256; i++)
   {
      
      b = data[dataLen - 1 - i];

      
      c = CRYPTO_TEST_LTE_32(i, n);
      mask = CRYPTO_SELECT_8(b, 0, c);
      bad2 |= CRYPTO_TEST_NEQ_8(b, mask);
   }

   
   bad |= bad1 & bad2;

   
   *paddingLen = CRYPTO_SELECT_32(n, 0, bad);

   
   return bad;
}




uint32_t sslVerifyMac(TlsEncryptionEngine *decryptionEngine,
   const TlsRecord *record, const uint8_t *data, size_t dataLen,
   size_t maxDataLen, const uint8_t *mac)
{
   size_t i;
   size_t j;
   size_t n;
   size_t padLen;
   size_t headerLen;
   size_t paddingLen;
   size_t blockSizeMask;
   uint8_t b;
   uint32_t c;
   uint64_t bitLen;
   const HashAlgo *hashAlgo;
   HashContext *hashContext;
   uint8_t temp1[SHA1_DIGEST_SIZE];
   uint8_t temp2[SHA1_DIGEST_SIZE];

   
   hashAlgo = decryptionEngine->hashAlgo;
   
   hashContext = (HashContext *) decryptionEngine->hmacContext->hashContext;

   
   if(hashAlgo == MD5_HASH_ALGO)
   {
      
      padLen = 48;
   }
   else if(hashAlgo == SHA1_HASH_ALGO)
   {
      
      padLen = 40;
   }
   else
   {
      
      return 1;
   }

   
   blockSizeMask = hashAlgo->blockSize - 1;

   
   
   headerLen = decryptionEngine->macKeyLen + padLen + 11;

   
   paddingLen = (headerLen + dataLen + hashAlgo->minPadSize - 1) & blockSizeMask;
   paddingLen = hashAlgo->blockSize - paddingLen;

   
   bitLen = (headerLen + dataLen) << 3;

   
   if(hashAlgo->bigEndian)
   {
      
      bitLen = swapInt64(bitLen);
   }

   
   n = headerLen + maxDataLen + hashAlgo->minPadSize;
   n = (n + hashAlgo->blockSize - 1) & ~blockSizeMask;
   n -= headerLen;

   
   hashAlgo->init(hashContext);
   hashAlgo->update(hashContext, decryptionEngine->macKey, decryptionEngine->macKeyLen);
   hashAlgo->update(hashContext, sslPad1, padLen);
   hashAlgo->update(hashContext, &decryptionEngine->seqNum, sizeof(TlsSequenceNumber));
   hashAlgo->update(hashContext, &record->type, sizeof(record->type));
   hashAlgo->update(hashContext, (void *) &record->length, sizeof(record->length));

   
   i = 0;

   
   
   if(maxDataLen > 255)
   {
      
      hashAlgo->update(hashContext, data, maxDataLen - 255);
      i += maxDataLen - 255;
   }

   
   while(i < n)
   {
      
      b = 0;

      
      c = CRYPTO_TEST_LT_32(i, dataLen);
      b = CRYPTO_SELECT_8(b, data[i], c);

      c = CRYPTO_TEST_EQ_32(i, dataLen);
      b = CRYPTO_SELECT_8(b, 0x80, c);

      j = dataLen + paddingLen;
      c = CRYPTO_TEST_GTE_32(i, j);
      j += 8;
      c &= CRYPTO_TEST_LT_32(i, j);
      b = CRYPTO_SELECT_8(b, bitLen & 0xFF, c);
      bitLen = CRYPTO_SELECT_64(bitLen, bitLen >> 8, c);

      
      hashAlgo->update(hashContext, &b, sizeof(uint8_t));

      
      i++;

      
      if(((i + headerLen) & blockSizeMask) == 0)
      {
         
         hashAlgo->finalRaw(hashContext, temp1);

         
         c = CRYPTO_TEST_EQ_32(i, dataLen + paddingLen + 8);

         
         
         for(j = 0; j < hashAlgo->digestSize; j++)
         {
            temp2[j] = CRYPTO_SELECT_8(temp2[j], temp1[j], c);
         }
      }
   }

   
   hashAlgo->init(hashContext);
   hashAlgo->update(hashContext, decryptionEngine->macKey, decryptionEngine->macKeyLen);
   hashAlgo->update(hashContext, sslPad2, padLen);
   hashAlgo->update(hashContext, temp2, hashAlgo->digestSize);
   hashAlgo->final(hashContext, temp1);

   
   TRACE_DEBUG("Read sequence number:\r\n");
   TRACE_DEBUG_ARRAY("  ", &decryptionEngine->seqNum, sizeof(TlsSequenceNumber));
   TRACE_DEBUG("Computed MAC:\r\n");
   TRACE_DEBUG_ARRAY("  ", temp1, hashAlgo->digestSize);

   
   
   for(b = 0, i = 0; i < hashAlgo->digestSize; i++)
   {
      b |= mac[i] ^ temp1[i];
   }

   
   return CRYPTO_TEST_NEQ_8(b, 0);
}

#endif
