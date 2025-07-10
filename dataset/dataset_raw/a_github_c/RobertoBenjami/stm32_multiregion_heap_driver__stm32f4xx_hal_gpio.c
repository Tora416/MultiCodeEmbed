 


#include "stm32f4xx_hal.h"





#ifdef HAL_GPIO_MODULE_ENABLED




#define GPIO_MODE             0x00000003U
#define EXTI_MODE             0x10000000U
#define GPIO_MODE_IT          0x00010000U
#define GPIO_MODE_EVT         0x00020000U
#define RISING_EDGE           0x00100000U
#define FALLING_EDGE          0x00200000U
#define GPIO_OUTPUT_TYPE      0x00000010U

#define GPIO_NUMBER           16U












void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;
  uint32_t temp = 0x00U;

  
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Init->Pin));
  assert_param(IS_GPIO_MODE(GPIO_Init->Mode));
  assert_param(IS_GPIO_PULL(GPIO_Init->Pull));

  
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
    
    ioposition = 0x01U << position;
    
    iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;

    if(iocurrent == ioposition)
    {
      
      
      if((GPIO_Init->Mode == GPIO_MODE_AF_PP) || (GPIO_Init->Mode == GPIO_MODE_AF_OD))
      {
        
        assert_param(IS_GPIO_AF(GPIO_Init->Alternate));
        
        temp = GPIOx->AFR[position >> 3U];
        temp &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U)) ;
        temp |= ((uint32_t)(GPIO_Init->Alternate) << (((uint32_t)position & 0x07U) * 4U));
        GPIOx->AFR[position >> 3U] = temp;
      }

      
      temp = GPIOx->MODER;
      temp &= ~(GPIO_MODER_MODER0 << (position * 2U));
      temp |= ((GPIO_Init->Mode & GPIO_MODE) << (position * 2U));
      GPIOx->MODER = temp;

      
      if((GPIO_Init->Mode == GPIO_MODE_OUTPUT_PP) || (GPIO_Init->Mode == GPIO_MODE_AF_PP) ||
         (GPIO_Init->Mode == GPIO_MODE_OUTPUT_OD) || (GPIO_Init->Mode == GPIO_MODE_AF_OD))
      {
        
        assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
        
        temp = GPIOx->OSPEEDR; 
        temp &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2U));
        temp |= (GPIO_Init->Speed << (position * 2U));
        GPIOx->OSPEEDR = temp;

        
        temp = GPIOx->OTYPER;
        temp &= ~(GPIO_OTYPER_OT_0 << position) ;
        temp |= (((GPIO_Init->Mode & GPIO_OUTPUT_TYPE) >> 4U) << position);
        GPIOx->OTYPER = temp;
      }

      
      temp = GPIOx->PUPDR;
      temp &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));
      temp |= ((GPIO_Init->Pull) << (position * 2U));
      GPIOx->PUPDR = temp;

      
      
      if((GPIO_Init->Mode & EXTI_MODE) == EXTI_MODE)
      {
        
        __HAL_RCC_SYSCFG_CLK_ENABLE();

        temp = SYSCFG->EXTICR[position >> 2U];
        temp &= ~(0x0FU << (4U * (position & 0x03U)));
        temp |= ((uint32_t)(GPIO_GET_INDEX(GPIOx)) << (4U * (position & 0x03U)));
        SYSCFG->EXTICR[position >> 2U] = temp;

        
        temp = EXTI->IMR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Init->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
        {
          temp |= iocurrent;
        }
        EXTI->IMR = temp;

        temp = EXTI->EMR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Init->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
        {
          temp |= iocurrent;
        }
        EXTI->EMR = temp;

        
        temp = EXTI->RTSR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Init->Mode & RISING_EDGE) == RISING_EDGE)
        {
          temp |= iocurrent;
        }
        EXTI->RTSR = temp;

        temp = EXTI->FTSR;
        temp &= ~((uint32_t)iocurrent);
        if((GPIO_Init->Mode & FALLING_EDGE) == FALLING_EDGE)
        {
          temp |= iocurrent;
        }
        EXTI->FTSR = temp;
      }
    }
  }
}


void HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
  uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;
  uint32_t tmp = 0x00U;

  
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  
  
  for(position = 0U; position < GPIO_NUMBER; position++)
  {
    
    ioposition = 0x01U << position;
    
    iocurrent = (GPIO_Pin) & ioposition;

    if(iocurrent == ioposition)
    {
      
      
      GPIOx->MODER &= ~(GPIO_MODER_MODER0 << (position * 2U));

      
      GPIOx->AFR[position >> 3U] &= ~(0xFU << ((uint32_t)(position & 0x07U) * 4U)) ;

      
      GPIOx->OSPEEDR &= ~(GPIO_OSPEEDER_OSPEEDR0 << (position * 2U));

      
      GPIOx->OTYPER  &= ~(GPIO_OTYPER_OT_0 << position) ;

      
      GPIOx->PUPDR &= ~(GPIO_PUPDR_PUPDR0 << (position * 2U));

      
      tmp = SYSCFG->EXTICR[position >> 2U];
      tmp &= (0x0FU << (4U * (position & 0x03U)));
      if(tmp == ((uint32_t)(GPIO_GET_INDEX(GPIOx)) << (4U * (position & 0x03U))))
      {
        
        tmp = 0x0FU << (4U * (position & 0x03U));
        SYSCFG->EXTICR[position >> 2U] &= ~tmp;

        
        EXTI->IMR &= ~((uint32_t)iocurrent);
        EXTI->EMR &= ~((uint32_t)iocurrent);
        
        
        EXTI->RTSR &= ~((uint32_t)iocurrent);
        EXTI->FTSR &= ~((uint32_t)iocurrent);
      }
    }
  }
}






GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;

  
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}


void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ACTION(PinState));

  if(PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
  }
}


void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
}


HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
  __IO uint32_t tmp = GPIO_LCKR_LCKK;

  
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  
  tmp |= GPIO_Pin;
  
  GPIOx->LCKR = tmp;
  
  GPIOx->LCKR = GPIO_Pin;
  
  GPIOx->LCKR = tmp;
  
  tmp = GPIOx->LCKR;

 if((GPIOx->LCKR & GPIO_LCKR_LCKK) != RESET)
  {
    return HAL_OK;
  }
  else
  {
    return HAL_ERROR;
  }
}


void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
{
  
  if(__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != RESET)
  {
    __HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
    HAL_GPIO_EXTI_Callback(GPIO_Pin);
  }
}


__weak void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  
  UNUSED(GPIO_Pin);
  
}






#endif 





