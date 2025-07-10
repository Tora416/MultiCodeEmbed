
#include "SinglePartitionDemoFirmwareUpdateInfoSerialReader.h"

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
};
typedef struct FirmwareUpdateInfoParser__data FirmwareUpdateInfoParser__data_t;

static void FirmwareUpdateInfoParser__init(FirmwareUpdateInfoParser__data_t *instance);

static bool FirmwareUpdateInfoParser__execute(FirmwareUpdateInfoParser__data_t *instance, FirmwareUpdateInfoParser__inevents_t event, void **arguments);

static char updateVersion[MAX_DEMO_FIRMWARE_UPDATE_VERSION_LENGTH + 1] = { 0 };

static uint8_t *updateVerificationData = NULL;

static FirmwareUpdateInfoParser__data_t updateInfoParser;

void firmwareUpdateInfoReader_init(void)
{
  FirmwareUpdateInfoParser__init(&updateInfoParser);
  
  size_t updateVerificationDataSize = getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM);
  updateVerificationData = ((uint8_t *)(malloc(updateVerificationDataSize)));
  memset(updateVerificationData, 0, updateVerificationDataSize);
}

void firmwareUpdateInfoReader_run(void)
{
  if ((updateInfoParser.__currentState == FirmwareUpdateInfoParser_yielding__state)) 
  {
    printf("Firmware update request towards version %s received\n", updateVersion);
    fotaUpdateWorkflow_onFirmwareUpdateVersionChanged(updateVersion);
    FirmwareUpdateInfoParser__execute(&updateInfoParser, FirmwareUpdateInfoParser_updateInfoPickedUp__event, NULL);
  }
}

void firmwareUpdateInfoReader_onCharacterReceived(uint8_t character)
{
  uint8_t ___FirmwareUpdateInfoParser_characterReceived_character__arg = character;
  void *___FirmwareUpdateInfoParser_characterReceived__args[1] = { &___FirmwareUpdateInfoParser_characterReceived_character__arg };
  FirmwareUpdateInfoParser__execute(&updateInfoParser, FirmwareUpdateInfoParser_characterReceived__event, ___FirmwareUpdateInfoParser_characterReceived__args);
}

static void FirmwareUpdateInfoParser__init(FirmwareUpdateInfoParser__data_t *instance)
{
  instance->characterIdx = 0;
  instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingUpdateVersion__state;
}

static bool FirmwareUpdateInfoParser__execute(FirmwareUpdateInfoParser__data_t *instance, FirmwareUpdateInfoParser__inevents_t event, void **arguments)
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
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingUpdateVerificationData__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) != COLON && isspace((*((uint8_t *)((arguments[0]))))) == 0 && instance->characterIdx >= MAX_DEMO_FIRMWARE_UPDATE_VERSION_LENGTH - 1) 
          {
            
            printf("Received firmware update version too long (max. length = %hhu)\n", MAX_DEMO_FIRMWARE_UPDATE_VERSION_LENGTH);
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == COLON && instance->characterIdx == 0) 
          {
            
            printf("Firmware update request with missing version received\n");
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx == 0) 
          {
            
            printf("Empty firmware update request received\n");
            instance->characterIdx = 0;
            
            
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx > 0) 
          {
            
            printf("Firmware update request with missing verification data received\n");
            memset(updateVersion, 0, sizeof(updateVersion));
            instance->characterIdx = 0;
            
            
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
            memset(updateVerificationData, 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
            instance->characterIdx = 0;
            
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
              
              updateVerificationData[instance->characterIdx >> 1] = convertHexDigitToBinValue(((char)((*((uint8_t *)((arguments[0]))))))) << 4;
            }
            else
            {
              
              (updateVerificationData[instance->characterIdx >> 1] |= (convertHexDigitToBinValue(((char)((*((uint8_t *)((arguments[0])))))))));
            }
            instance->characterIdx++;
            
            
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx > 0) 
          {
            
            instance->__currentState = FirmwareUpdateInfoParser_yielding__state;
            break;
          }
          if (isxdigit((*((uint8_t *)((arguments[0]))))) != 0 && instance->characterIdx >= getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM) << 1) 
          {
            
            printf("Received firmware update verification data too long (max. length = %d)\n", getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM) << 1);
            
            
            instance->__currentState = FirmwareUpdateInfoParser_receiving_receivingBadCharacters__state;
            break;
          }
          if ((*((uint8_t *)((arguments[0])))) == LF && instance->characterIdx == 0) 
          {
            
            printf("Firmware update request with missing verification data received\n");
            memset(updateVersion, 0, sizeof(updateVersion));
            memset(updateVerificationData, 0, getVerificationDataSize(DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM));
            instance->characterIdx = 0;
            
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

void fotahub_onProvideFirmwareUpdateVerificationInfo(FirmwareUpdateInfo_t const *pUpdateInfo, FOTAUpdateVerificationAlgorithm_t *pVerificationAlgorithm, uint8_t const  **ppVerificationData)
{
  *pVerificationAlgorithm = DEMO_PRODUCT_FIRMWARE_UPDATE_VERIFICATION_ALGORITHM;
  *ppVerificationData = updateVerificationData;
}
