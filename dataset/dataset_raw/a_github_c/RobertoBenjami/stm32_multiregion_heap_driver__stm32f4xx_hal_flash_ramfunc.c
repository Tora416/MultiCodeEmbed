 


#include "stm32f4xx_hal.h"




#ifdef HAL_FLASH_MODULE_ENABLED
#if defined(STM32F410Tx) || defined(STM32F410Cx) || defined(STM32F410Rx) || defined(STM32F411xE) || defined(STM32F446xx) || defined(STM32F412Zx) || defined(STM32F412Vx) || \
    defined(STM32F412Rx) || defined(STM32F412Cx)












__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_StopFlashInterfaceClk(void)
{
  
  __HAL_RCC_PWR_CLK_ENABLE();
    
  SET_BIT(PWR->CR, PWR_CR_FISSR);
   
  return HAL_OK;
}


__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_StartFlashInterfaceClk(void)
{
  
  __HAL_RCC_PWR_CLK_ENABLE();
  
  CLEAR_BIT(PWR->CR, PWR_CR_FISSR);

  return HAL_OK;
}


__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_EnableFlashSleepMode(void)
{
  
  __HAL_RCC_PWR_CLK_ENABLE();
  
  SET_BIT(PWR->CR, PWR_CR_FMSSR);

  return HAL_OK;
}


__RAM_FUNC HAL_StatusTypeDef HAL_FLASHEx_DisableFlashSleepMode(void)
{
  
  __HAL_RCC_PWR_CLK_ENABLE();
  
  CLEAR_BIT(PWR->CR, PWR_CR_FMSSR);
  
  return HAL_OK;
}





#endif 
#endif 





