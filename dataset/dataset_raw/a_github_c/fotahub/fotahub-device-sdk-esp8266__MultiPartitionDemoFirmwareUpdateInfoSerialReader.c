
#include "MultiPartitionDemoFirmwareUpdateInfoSerialReader.h"

#include "DemoFOTAUpdateWorkflow.h"
#include "BinHexConverter.h"
#include "FotaHub.h"
#include "DemoProductInfo.h"
#include "ctype.h"
#include <stdlib.h>
#include <string.h>

enum FirmwareUpdateInfoParser__inevents {
  FirmwareUpdateInfoParser_characterReceived__event,
  FirmwareUpdateInfoParser_updateInfoPickedUp__event
};
typedef enum FirmwareUpdateInfoParser__inevents FirmwareUpdateInfoParser__inevents_t;

enum FirmwareUpdateInfoParser__states {
  FirmwareUpdateInfoParser_receiving_receivingUpdateVersion__state = 0,
  FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state,
  FirmwareUpdateInfoParser_receiving_receivingUpdateVerificationData__state,
  FirmwareUpdateInfoParser_yielding__state
};
typedef enum FirmwareUpdateInfoParser__states FirmwareUpdateInfoParser__states_t;

struct FirmwareUpdateInfoParser__data {
  FirmwareUpdateInfoParser__states_t __currentState;
  size_t characterIdx;
  size_t partitionIdx;
  uint8_t *pCurrentVerificationData;
};
typedef struct FirmwareUpdateInfoParser__data FirmwareUpdateInfoParser__data_t;

static void ICACHE_FLASH_ATTR FirmwareUpdateInfoParser__init(FirmwareUpdateInfoParser__data_t *instance);

static bool ICACHE_FLASH_ATTR FirmwareUpdateInfoParser__execute(FirmwareUpdateInfoParser__data_t *instance, FirmwareUpdateInfoParser__inevents_t event, void **arguments);

static char updateVersion[MAX_DEMO_FIRMWARE_UPDATE_VERSION_LENGTH + 1] = { 0 };

static uint8_t *updateVerificationData[UPDATE_PARTITION_COUNT] = { NULL, NULL };

static FirmwareUpdateInfoParser__data_t updateInfoParser;

void ICACHE_FLASH_ATTR firmwareUpdateInfoReader_init(void)
{
  FirmwareUpdateInfoParser__init(&updateInfoParser);
  
  size_t updateVerificationDataSize = getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM);
  updateVerificationData[0] = ((uint8_t *)(os_malloc(updateVerificationDataSize)));
  updateVerificationData[1] = ((uint8_t *)(os_malloc(updateVerificationDataSize)));
  os_memset(updateVerificationData[0], 0, updateVerificationDataSize);
  os_memset(updateVerificationData[1], 0, updateVerificationDataSize);
}

void ICACHE_FLASH_ATTR firmwareUpdateInfoReader_run(void)
{
  if ((updateInfoParser.__currentState == FirmwareUpdateInfoParser_yielding__state)) 
  {
    os_printf("Firmware update request towards version %s received\n", updateVersion);
    fotaUpdateWorkflow_onFirmwareUpdateVersionChanged(updateVersion);
    FirmwareUpdateInfoParser__execute(&updateInfoParser, FirmwareUpdateInfoParser_updateInfoPickedUp__event, NULL);
  }
}

void ICACHE_FLASH_ATTR firmwareUpdateInfoReader_onCharacterReceived(uint8_t character)
{
  uint8_t ___FirmwareUpdateInfoParser_characterReceived_character__arg = character;
  void *___FirmwareUpdateInfoParser_characterReceived__args[1] = { &___FirmwareUpdateInfoParser_characterReceived_character__arg };
  FirmwareUpdateInfoParser__execute(&updateInfoParser, FirmwareUpdateInfoParser_characterReceived__event, ___FirmwareUpdateInfoParser_characterReceived__args);
}

static void ICACHE_FLASH_ATTR FirmwareUpdateInfoParser__init(FirmwareUpdateInfoParser__data_t *instance)
{
  instance->characterIdx = 0;
  instance->partitionIdx = 0;
  instance->pCurrentVerificationData = updateVerificationData[0];
  instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingUpdateVersion__state;
}

static bool ICACHE_FLASH_ATTR FirmwareUpdateInfoParser__execute(FirmwareUpdateInfoParser__data_t *instance, FirmwareUpdateInfoParser__inevents_t event, void **arguments)
{
  switch (instance->__currentState)
  {
    case FirmwareUpdateInfoParser_receiving_receivingUpdateVersion__state:
    {
      switch (event)
      {
        case FirmwareUpdateInfoParser_characterReceived__event:
        {
          if ((*((uint8_t *)((arguments[0])))) != COLON && isspace((*((uint8_t *)((arguments[0]))))) == 0 && instance->characterIdx < MAX_DEMO_FIRMWARE_UPDATE_VERSION_LENGTH - 1) 
          {
            
            
            updateVersion[instance->characterIdx++] = ((char)((*((uint8_t *)((arguments[0]))))));
            
            
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == COLON && instance->characterIdx > 0) 
          {
            
            
            updateVersion[instance->characterIdx] = '\0';
            instance->characterIdx = 0;
            instance->pCurrentVerificationData = updateVerificationData[instance->partitionIdx];
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingUpdateVerificationData__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) != COLON && isspace((*((uint8_t *)((arguments[0]))))) == 0 && instance->characterIdx >= MAX_DEMO_FIRMWARE_UPDATE_VERSION_LENGTH - 1) 
          {
            
            os_printf("Received firmware update version too long (max. length = %d)\n", MAX_DEMO_FIRMWARE_UPDATE_VERSION_LENGTH);
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == COLON && instance->characterIdx == 0) 
          {
            
            os_printf("Firmware update request with missing version received\n");
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx == 0) 
          {
            
            os_printf("Empty firmware update request received\n");
            instance->characterIdx = 0;
            instance->partitionIdx = 0;
            
            
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx > 0) 
          {
            
            os_printf("Firmware update request with missing verification data received\n");
            memset(updateVersion, 0, sizeof(updateVersion));
            instance->characterIdx = 0;
            instance->partitionIdx = 0;
            
            
          }
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    case FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state:
    {
      switch (event)
      {
        case FirmwareUpdateInfoParser_characterReceived__event:
        {
          if ((*((uint8_t *)((arguments[0])))) != LF) 
          {
            
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF) 
          {
            
            memset(updateVersion, 0, sizeof(updateVersion));
            os_memset(updateVerificationData[0], 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
            os_memset(updateVerificationData[1], 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
            instance->characterIdx = 0;
            instance->partitionIdx = 0;
            
            if (instance->__currentState == FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state) 
            {
              
              instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingUpdateVersion__state;
            }
          }
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    case FirmwareUpdateInfoParser_receiving_receivingUpdateVerificationData__state:
    {
      switch (event)
      {
        case FirmwareUpdateInfoParser_characterReceived__event:
        {
          if (isxdigit((*((uint8_t *)((arguments[0]))))) != 0 && instance->characterIdx < getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM) << 1) 
          {
            
            
            if (((instance->characterIdx & (1)) == 0)) 
            {
              
              instance->pCurrentVerificationData[instance->characterIdx >> 1] = convertHexDigitToBinValue(((char)((*((uint8_t *)((arguments[0]))))))) << 4;
            }
            else
            {
              
              (instance->pCurrentVerificationData[instance->characterIdx >> 1] |= (convertHexDigitToBinValue(((char)((*((uint8_t *)((arguments[0])))))))));
            }
            instance->characterIdx++;
            
            
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == COMMA && instance->characterIdx > 0 && instance->partitionIdx < UPDATE_PARTITION_COUNT - 1) 
          {
            
            instance->characterIdx = 0;
            instance->partitionIdx++;
            instance->pCurrentVerificationData = updateVerificationData[instance->partitionIdx];
            
            
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx > 0 && instance->partitionIdx == UPDATE_PARTITION_COUNT - 1) 
          {
            
            instance->__currentState = FirmwareUpdateInfoParser_yielding__state;
            break;
          }
          if (isxdigit((*((uint8_t *)((arguments[0]))))) != 0 && instance->characterIdx >= getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM) << 1) 
          {
            
            os_printf("Received firmware update verification data #%d too long (max. length = %d)\n", instance->partitionIdx + 1, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM) << 1);
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == COMMA && instance->characterIdx == 0) 
          {
            
            os_printf("Firmware update request with missing verification data #%d received\n", instance->partitionIdx + 1);
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == COMMA && instance->characterIdx > 0 && instance->partitionIdx >= UPDATE_PARTITION_COUNT - 1) 
          {
            
            os_printf("Firmware update request with too many verifications data received (max. # = %d)\n", UPDATE_PARTITION_COUNT);
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx == 0) 
          {
            
            os_printf("Firmware update request with missing verification data #%d received\n", instance->partitionIdx + 1);
            memset(updateVersion, 0, sizeof(updateVersion));
            os_memset(updateVerificationData[0], 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
            os_memset(updateVerificationData[1], 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
            instance->characterIdx = 0;
            instance->partitionIdx = 0;
            
            if (instance->__currentState == FirmwareUpdateInfoParser_receiving_receivingUpdateVerificationData__state) 
            {
              
              instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingUpdateVersion__state;
            }
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx > 0 && instance->partitionIdx < UPDATE_PARTITION_COUNT - 1) 
          {
            
            os_printf("Firmware update request with missing verification data #%d received\n", instance->partitionIdx + 2);
            memset(updateVersion, 0, sizeof(updateVersion));
            os_memset(updateVerificationData[0], 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
            os_memset(updateVerificationData[1], 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
            instance->characterIdx = 0;
            instance->partitionIdx = 0;
            
            if (instance->__currentState == FirmwareUpdateInfoParser_receiving_receivingUpdateVerificationData__state) 
            {
              
              instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingUpdateVersion__state;
            }
          }
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    case FirmwareUpdateInfoParser_yielding__state:
    {
      switch (event)
      {
        case FirmwareUpdateInfoParser_updateInfoPickedUp__event:
        {
          
          instance->characterIdx = 0;
          instance->partitionIdx = 0;
          
          
          instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingUpdateVersion__state;
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    default: {
      break;
    }
  }
  return true;
}

void ICACHE_FLASH_ATTR fotahub_onProvideFirmwareUpdateVerificationInfo(FirmwareUpdateInfo_t const *pUpdateInfo, FOTAUpdateVerificationAlgorithm_t *pVerificationAlgorithm, uint8_t const  **ppVerificationData)
{
  *pVerificationAlgorithm = DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM;
  if (pUpdateInfo->partitionIdx >= 0 && pUpdateInfo->partitionIdx < UPDATE_PARTITION_COUNT) 
  {
    *ppVerificationData = updateVerificationData[((size_t)(pUpdateInfo->partitionIdx))];
  }
  else
  {
    *ppVerificationData = NULL;
  }
}
