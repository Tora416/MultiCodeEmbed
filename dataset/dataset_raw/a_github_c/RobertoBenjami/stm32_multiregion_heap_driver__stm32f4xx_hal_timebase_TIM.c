


#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_tim.h"


 





TIM_HandleTypeDef        htim6; 
uint32_t                 uwIncrementState = 0;




HAL_StatusTypeDef HAL_InitTick(uint32_t TickPriority)
{
  RCC_ClkInitTypeDef    clkconfig;
  uint32_t              uwTimclock = 0;
  uint32_t              uwPrescalerValue = 0;
  uint32_t              pFLatency;
  
  
  HAL_NVIC_SetPriority(TIM6_DAC_IRQn, TickPriority ,0); 
  
  
  HAL_NVIC_EnableIRQ(TIM6_DAC_IRQn); 
  
  
  __HAL_RCC_TIM6_CLK_ENABLE();
  
  
  HAL_RCC_GetClockConfig(&clkconfig, &pFLatency);
  
  
  uwTimclock = 2*HAL_RCC_GetPCLK1Freq();
   
  
  uwPrescalerValue = (uint32_t) ((uwTimclock / 1000000) - 1);
  
  
  htim6.Instance = TIM6;
  
  
  htim6.Init.Period = (1000000 / 1000) - 1;
  htim6.Init.Prescaler = uwPrescalerValue;
  htim6.Init.ClockDivision = 0;
  htim6.Init.CounterMode = TIM_COUNTERMODE_UP;
  if(HAL_TIM_Base_Init(&htim6) == HAL_OK)
  {
    
    return HAL_TIM_Base_Start_IT(&htim6);
  }
  
  
  return HAL_ERROR;
}


void HAL_SuspendTick(void)
{
  
  __HAL_TIM_DISABLE_IT(&htim6, TIM_IT_UPDATE);                                                  
}


void HAL_ResumeTick(void)
{
  
  __HAL_TIM_ENABLE_IT(&htim6, TIM_IT_UPDATE);
}

 

 


