
#include "BinHexConverter.h"

#include <stdio.h>
#include <string.h>

static inline char ICACHE_FLASH_ATTR convertBinValueToHexDigit(uint8_t value, bool upperCase);

static inline char ICACHE_FLASH_ATTR convertBinValueToHexDigit(uint8_t value, bool upperCase)
{
  char hexA = (upperCase) ? ('A') : ('a');
  return ((char)((value < 10) ? ('0' + value) : (hexA + value - 10)));
}

uint8_t ICACHE_FLASH_ATTR convertHexDigitToBinValue(char inputChr)
{
  if (inputChr >= '0' && inputChr <= '9') 
  {
    return ((uint8_t)(inputChr - '0'));
  }
  else if (inputChr >= 'a' && inputChr <= 'f') {
    return 10 + ((uint8_t)(inputChr - 'a'));
  }
  else if (inputChr >= 'A' && inputChr <= 'F') {
    return 10 + ((uint8_t)(inputChr - 'A'));
  }
  return 0;
}

size_t ICACHE_FLASH_ATTR convertBinValueToHexString8(uint8_t inputValue, char *outputStr, size_t outputStrSize, bool upperCase)
{
  if (outputStrSize < 2) 
  {
    return 0;
  }
  outputStr[0] = convertBinValueToHexDigit(((inputValue & 0xF0u) >> 4), upperCase);
  outputStr[1] = convertBinValueToHexDigit((inputValue & 0x0Fu), upperCase);
  return 2;
}

uint8_t ICACHE_FLASH_ATTR convertHexString8ToBinValue(char *inputStr, size_t inputStrLength)
{
  if (inputStrLength != 2) 
  {
    return 0;
  }
  uint8_t outputValue = convertHexDigitToBinValue(inputStr[0]) << 4;
  outputValue |= convertHexDigitToBinValue(inputStr[1]);
  return outputValue;
}

size_t ICACHE_FLASH_ATTR convertBinDataToHexString8(uint8_t *inputData, size_t inputDataSize, char *outputStr, size_t outputStrSize, bool upperCase)
{
  if (outputStrSize < inputDataSize * 2) 
  {
    return 0;
  }
  outputStr[0] = '\0';
  size_t count = 0;
  for ( size_t i = 0 ; i < inputDataSize; i++ )
  {
    count += convertBinValueToHexString8(inputData[i], outputStr + 2 * i, outputStrSize - count, upperCase);
  }
  if (outputStrSize > count) 
  {
    outputStr[count++] = '\0';
  }
  return count;
}

size_t ICACHE_FLASH_ATTR convertHexString8ToBinData(char *inputStr, size_t inputStrLength, uint8_t *pOutputData, size_t outputDataSize)
{
  if (outputDataSize < inputStrLength >> 1) 
  {
    return 0;
  }
  if ((inputStrLength & 0x01u) != 0) 
  {
    return 0;
  }
  os_memset(pOutputData, 0x00u, outputDataSize);
  for ( size_t i = 0 ; i < inputStrLength; i = i + 2 )
  {
    pOutputData[i >> 1] = convertHexString8ToBinValue(inputStr + i, 2);
  }
  return inputStrLength >> 1;
}
