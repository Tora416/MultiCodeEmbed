

#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "charlcd.h"


#define TIMEBASE              1000

#if LCD_MODE != 1
#error LCD MODE is wrong setting !
#endif


#ifdef  osCMSIS
#define Delay(t)              osDelay(t)
#define GetTime()             osKernelSysTick()
#else
#define Delay(t)              HAL_Delay(t)
#define GetTime()             HAL_GetTick()
#endif

#if (1UL * LCD_WIDTH * LCD_LINES < 80)
#define  FPSPOZ     0
#define  CPSPOZ     16
#else  
#define  FPSPOZ     82
#define  CPSPOZ     98
#endif 


#ifdef osCMSIS
void StartDefaultTask(void const * argument)
#else
void mainApp(void)
#endif
{
  uint32_t lastmsec = 0, t1, t2, res, cycle = 0;

  LcdInit();                            
  #if (1UL * LCD_WIDTH * LCD_LINES) < 80
  
  #else  
  
  memcpy((char *)LcdText +   0, "****************************************", 40);
  memcpy((char *)LcdText +  40, "*            LCD speed meter           *", 40);
  memcpy((char *)LcdText +  80, "*                                      *", 40);
  memcpy((char *)LcdText + 120, "****************************************", 40);
  #endif 

  while(1)
  {
    LcdRefreshAll();
    cycle++;                            

    t1 = GetTime();
    if(lastmsec + TIMEBASE <= t1)
    {
      t2 = GetTime();
      memcpy((char *)LcdText + FPSPOZ, "FPS:      ", 10);
      memcpy((char *)LcdText + CPSPOZ, "CPS:      ", 10);
      res = cycle * 1000 / (t2 - lastmsec);
      utoa(res, (char *)LcdText +  FPSPOZ + 4, 10);
      utoa(res * (1UL * LCD_LINES * (LCD_WIDTH + 1)), (char *)LcdText +  CPSPOZ + 4, 10);
      lastmsec = GetTime();
      cycle = 0;
    }
  }
}
