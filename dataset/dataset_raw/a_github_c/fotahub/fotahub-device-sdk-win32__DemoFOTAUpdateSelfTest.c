
#include "DemoFOTAUpdateSelfTest.h"

#include "FotaHub.h"
#include <stdlib.h>
#include <time.h>

static bool runRandomSelfTest(uint8_t successRate);

void fotaUpdateSelfTest_init(void)
{
  srand(((uint32_t)(time(NULL))));
}

static bool runRandomSelfTest(uint8_t successRate)
{
  if (((uint8_t)((rand() % 100))) >= (successRate)) 
  {
    printf("Firmware self test failed (reason: simulated pseudo-random failure)\n");
    return false;
  }
  return true;
}

void validateFirmwareUpdateActivation(void)
{
  printf("Validating firmware update\n");
  
  if (runRandomSelfTest(SIMULATED_ACTIVATION_SUCCESS_RATE)) 
  {
    printf("Firmware update successfully activated\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_ACTIVATION_SUCCEEDED);
  }
  else
  {
    printf("Firmware update activation failed\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_ACTIVATION_FAILED);
  }
}

void validateFirmwareUpdateReversion(void)
{
  printf("Validating previous firmware\n");
  
  if (runRandomSelfTest(SIMULATED_REVERSION_SUCCESS_RATE)) 
  {
    printf("Firmware update successfully reverted\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_REVERSION_SUCCEEDED);
  }
  else
  {
    printf("Firmware update reversion failed\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_REVERSION_FAILED);
  }
}
