

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stm32f4xx_it.h"







extern TIM_HandleTypeDef htim6;


 



void NMI_Handler(void)
{
  

  
  

  
}


void HardFault_Handler(void)
{
  

  
  while (1)
  {
    
    
  }
  

  
}


void MemManage_Handler(void)
{
  

  
  while (1)
  {
    
    
  }
  

  
}


void BusFault_Handler(void)
{
  

  
  while (1)
  {
    
    
  }
  

  
}


void UsageFault_Handler(void)
{
  

  
  while (1)
  {
    
    
  }
  

  
}


void SVC_Handler(void)
{
  

  
  

  
}


void DebugMon_Handler(void)
{
  

  
  

  
}


void PendSV_Handler(void)
{
  

  
  

  
}


void SysTick_Handler(void)
{
  

  
  HAL_SYSTICK_IRQHandler();
  

  
}









void TIM6_DAC_IRQHandler(void)
{
  

  
  HAL_TIM_IRQHandler(&htim6);
  

  
}





