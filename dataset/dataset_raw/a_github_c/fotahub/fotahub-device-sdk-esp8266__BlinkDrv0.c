
#include "BlinkDrv.h"

#include <eagle_soc.h>
#include <gpio.h>

static uint16_t currentTick;

static uint16_t expirationTick;

void ICACHE_FLASH_ATTR blink_init(uint16_t runPeriod, uint16_t blinkPeriod)
{
  PIN_FUNC_SELECT(BLINK_PIN_NAME,BLINK_FUNC_GPIO);
  
  currentTick = 0;
  expirationTick = (blinkPeriod >> 1) / runPeriod;
}

void ICACHE_FLASH_ATTR blink_run(void)
{
  if (currentTick == expirationTick) 
  {
    uint32_t state = GPIO_INPUT_GET(BLINK_PIN);
    (state ^= (0x01u));
    GPIO_OUTPUT_SET(BLINK_PIN,state);
    
    currentTick = 0;
  }
  else
  {
    currentTick++;
  }
}
