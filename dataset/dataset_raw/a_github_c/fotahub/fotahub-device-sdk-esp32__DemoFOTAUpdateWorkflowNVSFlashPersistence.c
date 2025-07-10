
#include "DemoFOTAUpdateWorkflowNVSFlashPersistence.h"

#include "Configuration.h"
#include "DemoFOTAUpdateWorkflowPersistence.h"
#include "nvs_flash.h"
#include <stdlib.h>

void saveState(int16_t state)
{
  nvs_handle *nvsHandle = ((nvs_handle *)(malloc(sizeof(nvs_handle))));
  if (nvsHandle == NULL) 
  {
    return;
  }
  if (nvs_open(DEMO_PRODUCT_STORAGE_NAMESPACE, NVS_READWRITE, nvsHandle) == ESP_OK) 
  {
    nvs_set_u8(*nvsHandle, DEMO_PRODUCT_FLASH_STORE_KEY, ((uint8_t) state));
    nvs_commit(*nvsHandle);
    nvs_close(*nvsHandle);
    free(nvsHandle);
    return;
  }
  free(nvsHandle);
  printf("Failed write statemachine state to NVS\n");
}

int16_t loadState(void)
{
  int16_t state = 0;
  nvs_handle *nvsHandle = ((nvs_handle *)(malloc(sizeof(nvs_handle))));
  if (nvsHandle == NULL) 
  {
    return 0;
  }
  if (nvs_open(DEMO_PRODUCT_STORAGE_NAMESPACE, NVS_READONLY, nvsHandle) == ESP_OK) 
  {
    nvs_get_u8(*nvsHandle, DEMO_PRODUCT_FLASH_STORE_KEY, ((uint8_t *)(&state)));
  }
  nvs_close(*nvsHandle);
  free(nvsHandle);
  
  if (state == -1) 
  {
    return 0;
  }
  return state;
}
