
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <c_types.h>
#include <osapi.h>
#include "SPIFlashHelper.h"
#include "user_config.h"
#include "DemoFOTAUpdateWorkflowPersistence.h"
#include <mem.h>

void ICACHE_FLASH_ATTR saveState(int16_t state)
{
  uint16_t sector = getFlashSector(DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS);
  if (spi_flash_erase_sector(sector) != SPI_FLASH_RESULT_OK) 
  {
    os_printf("Failed to erase NVS sector %d\n", DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS);
  }
  if (spi_flash_write(DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS, ((uint32_t *)(&state)), ((uint32_t)(sizeof(state)))) != SPI_FLASH_RESULT_OK) 
  {
    os_printf("Failed write statemachine state to NVS sector %d\n", DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS);
  }
}

int16_t ICACHE_FLASH_ATTR loadState(void)
{
  int16_t state = 0;
  if (spi_flash_read(DEMO_FOTA_UPDATE_STATE_FLASH_SECTOR_ADDRESS, ((uint32_t *)(&state)), ((uint32_t)(sizeof(state)))) != SPI_FLASH_RESULT_OK) 
  {
    return 0;
  }
  
  if (state == -1) 
  {
    return 0;
  }
  return state;
}
