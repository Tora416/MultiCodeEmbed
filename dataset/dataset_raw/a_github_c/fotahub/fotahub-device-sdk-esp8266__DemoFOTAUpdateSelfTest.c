
#include "DemoFOTAUpdateSelfTest.h"

#include "FotaHub.h"
#include <stdlib.h>
#include <time.h>

static bool ICACHE_FLASH_ATTR runRandomSelfTest(uint8_t successRate);

void ICACHE_FLASH_ATTR fotaUpdateSelfTest_init(void)
{
  srand(((uint32_t)(time(NULL))));
}

static bool ICACHE_FLASH_ATTR runRandomSelfTest(uint8_t successRate)
{
  if (((uint8_t)((os_random() % 100))) >= (successRate)) 
  {
    os_printf("Firmware self test failed (reason: simulated pseudo-random failure)\n");
    return false;
  }
  return true;
}

void ICACHE_FLASH_ATTR validateFirmwareUpdateActivation(void)
{
  os_printf("Validating firmware update\n");
  
  if (runRandomSelfTest(SIMULATED_ACTIVATION_SUCCESS_RATE)) 
  {
    os_printf("Firmware update successfully activated\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_ACTIVATION_SUCCEEDED);
  }
  else
  {
    os_printf("Firmware update activation failed\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_ACTIVATION_FAILED);
  }
}

void ICACHE_FLASH_ATTR validateFirmwareUpdateReversion(void)
{
  os_printf("Validating previous firmware\n");
  
  if (runRandomSelfTest(SIMULATED_REVERSION_SUCCESS_RATE)) 
  {
    os_printf("Firmware update successfully reverted\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_REVERSION_SUCCEEDED);
  }
  else
  {
    os_printf("Firmware update reversion failed\n");
    fotahub_onFirmwareUpdateStatusChanged(FOTA_UPDATE_STATUS_REVERSION_FAILED);
  }
}
