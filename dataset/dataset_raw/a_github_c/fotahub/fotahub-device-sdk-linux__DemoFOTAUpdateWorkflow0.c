
#include "DemoFOTAUpdateWorkflow.h"

#include "DemoProductInfo.h"
#include <string.h>

enum DemoFOTAUpdateWorkflowEngine__inevents {
  DemoFOTAUpdateWorkflowEngine_connectionStatusChanged__event,
  DemoFOTAUpdateWorkflowEngine_updateVersionChanged__event,
  DemoFOTAUpdateWorkflowEngine_updateStatusChanged__event
};
typedef enum DemoFOTAUpdateWorkflowEngine__inevents DemoFOTAUpdateWorkflowEngine__inevents_t;

enum DemoFOTAUpdateWorkflowEngine__states {
  DemoFOTAUpdateWorkflowEngine_idle__state = 0,
  DemoFOTAUpdateWorkflowEngine_connected__state,
  DemoFOTAUpdateWorkflowEngine_downloading__state,
  DemoFOTAUpdateWorkflowEngine_restarting__state
};
typedef enum DemoFOTAUpdateWorkflowEngine__states DemoFOTAUpdateWorkflowEngine__states_t;

struct DemoFOTAUpdateWorkflowEngine__data {
  DemoFOTAUpdateWorkflowEngine__states_t __currentState;
  FirmwareUpdateInfo_t updateInfo;
};
typedef struct DemoFOTAUpdateWorkflowEngine__data DemoFOTAUpdateWorkflowEngine__data_t;

static void DemoFOTAUpdateWorkflowEngine__init(DemoFOTAUpdateWorkflowEngine__data_t *instance);

static bool DemoFOTAUpdateWorkflowEngine__execute(DemoFOTAUpdateWorkflowEngine__data_t *instance, DemoFOTAUpdateWorkflowEngine__inevents_t event, void **arguments);

static inline void DemoFOTAUpdateWorkflowEngine_connected_EntryAction(DemoFOTAUpdateWorkflowEngine__data_t *instance);

static inline void DemoFOTAUpdateWorkflowEngine_restarting_EntryAction(DemoFOTAUpdateWorkflowEngine__data_t *instance);

static DemoFOTAUpdateWorkflowEngine__data_t updateWorkflowEngine;

void fotaUpdateWorkflow_init(void)
{
  DemoFOTAUpdateWorkflowEngine__init(&updateWorkflowEngine);
}

void fotahub_onConnectionStatusChanged(ConnectionStatus_t status)
{
  ConnectionStatus_t ___DemoFOTAUpdateWorkflowEngine_connectionStatusChanged_status__arg = status;
  void *___DemoFOTAUpdateWorkflowEngine_connectionStatusChanged__args[1] = { &___DemoFOTAUpdateWorkflowEngine_connectionStatusChanged_status__arg };
  DemoFOTAUpdateWorkflowEngine__execute(&updateWorkflowEngine, DemoFOTAUpdateWorkflowEngine_connectionStatusChanged__event, ___DemoFOTAUpdateWorkflowEngine_connectionStatusChanged__args);
}

void fotahub_onFirmwareUpdateStatusChanged(FOTAUpdateStatus_t status)
{
  FOTAUpdateStatus_t ___DemoFOTAUpdateWorkflowEngine_updateStatusChanged_status__arg = status;
  void *___DemoFOTAUpdateWorkflowEngine_updateStatusChanged__args[1] = { &___DemoFOTAUpdateWorkflowEngine_updateStatusChanged_status__arg };
  DemoFOTAUpdateWorkflowEngine__execute(&updateWorkflowEngine, DemoFOTAUpdateWorkflowEngine_updateStatusChanged__event, ___DemoFOTAUpdateWorkflowEngine_updateStatusChanged__args);
}

void fotaUpdateWorkflow_onFirmwareUpdateVersionChanged(char *updateVersion)
{
  char *___DemoFOTAUpdateWorkflowEngine_updateVersionChanged_updateVersion__arg = updateVersion;
  void *___DemoFOTAUpdateWorkflowEngine_updateVersionChanged__args[1] = { &___DemoFOTAUpdateWorkflowEngine_updateVersionChanged_updateVersion__arg };
  DemoFOTAUpdateWorkflowEngine__execute(&updateWorkflowEngine, DemoFOTAUpdateWorkflowEngine_updateVersionChanged__event, ___DemoFOTAUpdateWorkflowEngine_updateVersionChanged__args);
}

static void DemoFOTAUpdateWorkflowEngine__init(DemoFOTAUpdateWorkflowEngine__data_t *instance)
{
  instance->updateInfo.binaryKind = BINARY_KIND_DEFAULT;
  instance->updateInfo.binaryName = BINARY_NAME_DEFAULT;
  instance->updateInfo.version = NULL;
  instance->updateInfo.partitionIdx = PARTITION_IDX_NONE;
  instance->__currentState = DemoFOTAUpdateWorkflowEngine_idle__state;
}

static bool DemoFOTAUpdateWorkflowEngine__execute(DemoFOTAUpdateWorkflowEngine__data_t *instance, DemoFOTAUpdateWorkflowEngine__inevents_t event, void **arguments)
{
  switch (instance->__currentState)
  {
    case DemoFOTAUpdateWorkflowEngine_idle__state:
    {
      switch (event)
      {
        case DemoFOTAUpdateWorkflowEngine_connectionStatusChanged__event:
        {
          if ((*((ConnectionStatus_t *)((arguments[0])))) >= CONNECTION_STATUS_CONNECTIVITY_AVAILABLE) 
          {
            
            instance->__currentState = DemoFOTAUpdateWorkflowEngine_connected__state;
            DemoFOTAUpdateWorkflowEngine_connected_EntryAction(instance);
          }
          break;
        }
        case DemoFOTAUpdateWorkflowEngine_updateVersionChanged__event:
        {
          
          printf("Cannot handle firmware over-the-air update request (missing network connection)\n");
          
          
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    case DemoFOTAUpdateWorkflowEngine_connected__state:
    {
      switch (event)
      {
        case DemoFOTAUpdateWorkflowEngine_connectionStatusChanged__event:
        {
          if ((*((ConnectionStatus_t *)((arguments[0])))) < CONNECTION_STATUS_CONNECTIVITY_AVAILABLE) 
          {
            
            instance->__currentState = DemoFOTAUpdateWorkflowEngine_idle__state;
          }
          break;
        }
        case DemoFOTAUpdateWorkflowEngine_updateVersionChanged__event:
        {
          if (strcmp((*((char **)((arguments[0])))), DEMO_PRODUCT_FIRMWARE_VERSION) != 0) 
          {
            
            bool __transitionResult = true;
            DemoFOTAUpdateWorkflowEngine__states_t __targetState = DemoFOTAUpdateWorkflowEngine_downloading__state;
            
            
            instance->updateInfo.version = (*((char **)((arguments[0]))));
            
            
            if (!fotahub_downloadFirmwareUpdate(&instance->updateInfo)) 
            {
              __targetState = DemoFOTAUpdateWorkflowEngine_connected__state;
              __transitionResult = false;
            }
            
            if (instance->__currentState == DemoFOTAUpdateWorkflowEngine_connected__state) 
            {
              
              instance->__currentState = __targetState;
              switch (__targetState)
              {
                case DemoFOTAUpdateWorkflowEngine_connected__state:
                {
                  DemoFOTAUpdateWorkflowEngine_connected_EntryAction(instance);
                  break;
                }
                default: {
                  break;
                }
              }
            }
            
            if (!__transitionResult) 
            {
              return false;
            }
            break;
          }
          if (strcmp((*((char **)((arguments[0])))), DEMO_PRODUCT_FIRMWARE_VERSION) == 0) 
          {
            
            printf("Ignoring firmware over-the-air update request to version %s as this version is already running\n", (*((char **)((arguments[0])))));
            
            
            DemoFOTAUpdateWorkflowEngine_connected_EntryAction(instance);
          }
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    case DemoFOTAUpdateWorkflowEngine_downloading__state:
    {
      switch (event)
      {
        case DemoFOTAUpdateWorkflowEngine_updateStatusChanged__event:
        {
          if ((*((FOTAUpdateStatus_t *)((arguments[0])))) == FOTA_UPDATE_STATUS_DOWNLOAD_SUCCEEDED) 
          {
            
            bool __transitionResult = true;
            DemoFOTAUpdateWorkflowEngine__states_t __targetState = DemoFOTAUpdateWorkflowEngine_restarting__state;
            
            
            if (!fotahub_activateFirmwareUpdate(&instance->updateInfo)) 
            {
              __targetState = DemoFOTAUpdateWorkflowEngine_connected__state;
              __transitionResult = false;
            }
            
            if (instance->__currentState == DemoFOTAUpdateWorkflowEngine_downloading__state) 
            {
              
              instance->__currentState = __targetState;
              switch (__targetState)
              {
                case DemoFOTAUpdateWorkflowEngine_restarting__state:
                {
                  DemoFOTAUpdateWorkflowEngine_restarting_EntryAction(instance);
                  break;
                }
                case DemoFOTAUpdateWorkflowEngine_connected__state:
                {
                  DemoFOTAUpdateWorkflowEngine_connected_EntryAction(instance);
                  break;
                }
                default: {
                  break;
                }
              }
            }
            
            if (!__transitionResult) 
            {
              return false;
            }
            break;
          }
          if ((*((FOTAUpdateStatus_t *)((arguments[0])))) == FOTA_UPDATE_STATUS_CONNECTIVITY_UNAVAILABLE) 
          {
            
            instance->__currentState = DemoFOTAUpdateWorkflowEngine_idle__state;
            break;
          }
          if ((*((FOTAUpdateStatus_t *)((arguments[0])))) != FOTA_UPDATE_STATUS_DOWNLOAD_SUCCEEDED || (*((FOTAUpdateStatus_t *)((arguments[0])))) != FOTA_UPDATE_STATUS_CONNECTIVITY_UNAVAILABLE) 
          {
            
            instance->__currentState = DemoFOTAUpdateWorkflowEngine_connected__state;
            DemoFOTAUpdateWorkflowEngine_connected_EntryAction(instance);
          }
          break;
        }
        default: {
          break;
        }
      }
      break;
    }
    case DemoFOTAUpdateWorkflowEngine_restarting__state:
    {
      switch (event)
      {
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

static inline void DemoFOTAUpdateWorkflowEngine_connected_EntryAction(DemoFOTAUpdateWorkflowEngine__data_t *instance)
{
  printf("Ready for firmware over-the-air update\n");
}

static inline void DemoFOTAUpdateWorkflowEngine_restarting_EntryAction(DemoFOTAUpdateWorkflowEngine__data_t *instance)
{
  printf("Waiting for restart\n");
}
