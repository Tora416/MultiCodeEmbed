

#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "charlcd.h"


#ifdef  osCMSIS
#define Delay(t)              osDelay(t)
#define GetTime()             osKernelSysTick()
#else
#define Delay(t)              HAL_Delay(t)
#define GetTime()             HAL_GetTick()
#endif


#ifdef osCMSIS
void StartDefaultTask(void const * argument)
#else
void mainApp(void)
#endif
{
  LcdInit();                            
  memcpy((char *)LcdText, "   Hello world                  ", 32);
  #if LCD_MODE == 1 || LCD_MODE == 2 || LCD_MODE == 3
  LcdRefreshAll();
  #endif
  while(1)
  {
    #if LCD_MODE == 4
    LcdProcess();
    #endif
  }
}
