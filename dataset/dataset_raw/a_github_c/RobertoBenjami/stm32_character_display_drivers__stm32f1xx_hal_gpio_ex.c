


#include "stm32f1xx_hal.h"





#ifdef HAL_GPIO_MODULE_ENABLED






void HAL_GPIOEx_ConfigEventout(uint32_t GPIO_PortSource, uint32_t GPIO_PinSource)
{
  
  assert_param(IS_AFIO_EVENTOUT_PORT(GPIO_PortSource));
  assert_param(IS_AFIO_EVENTOUT_PIN(GPIO_PinSource));

  
  MODIFY_REG(AFIO->EVCR, (AFIO_EVCR_PORT) | (AFIO_EVCR_PIN), (GPIO_PortSource) | (GPIO_PinSource));
}


void HAL_GPIOEx_EnableEventout(void)
{
  SET_BIT(AFIO->EVCR, AFIO_EVCR_EVOE);
}


void HAL_GPIOEx_DisableEventout(void)
{
  CLEAR_BIT(AFIO->EVCR, AFIO_EVCR_EVOE);
}





#endif 






