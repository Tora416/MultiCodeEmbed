


#include "stm32f1xx_hal.h"





#ifdef HAL_GPIO_MODULE_ENABLED




#define GPIO_MODE             0x00000003U
#define EXTI_MODE             0x10000000U
#define GPIO_MODE_IT          0x00010000U
#define GPIO_MODE_EVT         0x00020000U
#define RISING_EDGE           0x00100000U
#define FALLING_EDGE          0x00200000U
#define GPIO_OUTPUT_TYPE      0x00000010U

#define GPIO_NUMBER           16U


#define  GPIO_CR_MODE_INPUT         0x00000000U 
#define  GPIO_CR_CNF_ANALOG         0x00000000U 
#define  GPIO_CR_CNF_INPUT_FLOATING 0x00000004U 
#define  GPIO_CR_CNF_INPUT_PU_PD    0x00000008U 
#define  GPIO_CR_CNF_GP_OUTPUT_PP   0x00000000U 
#define  GPIO_CR_CNF_GP_OUTPUT_OD   0x00000004U 
#define  GPIO_CR_CNF_AF_OUTPUT_PP   0x00000008U 
#define  GPIO_CR_CNF_AF_OUTPUT_OD   0x0000000CU 













void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
{
  uint32_t position;
  uint32_t ioposition = 0x00U;
  uint32_t iocurrent = 0x00U;
  uint32_t temp = 0x00U;
  uint32_t config = 0x00U;
  __IO uint32_t *configregister; 
  uint32_t registeroffset = 0U; 

  
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Init->Pin));
  assert_param(IS_GPIO_MODE(GPIO_Init->Mode));

  
  for (position = 0U; position < GPIO_NUMBER; position++)
  {
    
    ioposition = (0x01U << position);

    
    iocurrent = (uint32_t)(GPIO_Init->Pin) & ioposition;

    if (iocurrent == ioposition)
    {
      
      assert_param(IS_GPIO_AF_INSTANCE(GPIOx));

      
      switch (GPIO_Init->Mode)
      {
        
        case GPIO_MODE_OUTPUT_PP:
          
          assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
          config = GPIO_Init->Speed + GPIO_CR_CNF_GP_OUTPUT_PP;
          break;

        
        case GPIO_MODE_OUTPUT_OD:
          
          assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
          config = GPIO_Init->Speed + GPIO_CR_CNF_GP_OUTPUT_OD;
          break;

        
        case GPIO_MODE_AF_PP:
          
          assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
          config = GPIO_Init->Speed + GPIO_CR_CNF_AF_OUTPUT_PP;
          break;

        
        case GPIO_MODE_AF_OD:
          
          assert_param(IS_GPIO_SPEED(GPIO_Init->Speed));
          config = GPIO_Init->Speed + GPIO_CR_CNF_AF_OUTPUT_OD;
          break;

        
        case GPIO_MODE_INPUT:
        case GPIO_MODE_IT_RISING:
        case GPIO_MODE_IT_FALLING:
        case GPIO_MODE_IT_RISING_FALLING:
        case GPIO_MODE_EVT_RISING:
        case GPIO_MODE_EVT_FALLING:
        case GPIO_MODE_EVT_RISING_FALLING:
          
          assert_param(IS_GPIO_PULL(GPIO_Init->Pull));
          if (GPIO_Init->Pull == GPIO_NOPULL)
          {
            config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_FLOATING;
          }
          else if (GPIO_Init->Pull == GPIO_PULLUP)
          {
            config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_PU_PD;

            
            GPIOx->BSRR = ioposition;
          }
          else 
          {
            config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_INPUT_PU_PD;

            
            GPIOx->BRR = ioposition;
          }
          break;

        
        case GPIO_MODE_ANALOG:
          config = GPIO_CR_MODE_INPUT + GPIO_CR_CNF_ANALOG;
          break;

        
        default:
          break;
      }

      
      configregister = (iocurrent < GPIO_PIN_8) ? &GPIOx->CRL     : &GPIOx->CRH;
      registeroffset = (iocurrent < GPIO_PIN_8) ? (position << 2U) : ((position - 8U) << 2U);

      
      MODIFY_REG((*configregister), ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset), (config << registeroffset));

      
      
      if ((GPIO_Init->Mode & EXTI_MODE) == EXTI_MODE)
      {
        
        __HAL_RCC_AFIO_CLK_ENABLE();
        temp = AFIO->EXTICR[position >> 2U];
        CLEAR_BIT(temp, (0x0FU) << (4U * (position & 0x03U)));
        SET_BIT(temp, (GPIO_GET_INDEX(GPIOx)) << (4U * (position & 0x03U)));
        AFIO->EXTICR[position >> 2U] = temp;


        
        if ((GPIO_Init->Mode & GPIO_MODE_IT) == GPIO_MODE_IT)
        {
          SET_BIT(EXTI->IMR, iocurrent);
        }
        else
        {
          CLEAR_BIT(EXTI->IMR, iocurrent);
        }

        
        if ((GPIO_Init->Mode & GPIO_MODE_EVT) == GPIO_MODE_EVT)
        {
          SET_BIT(EXTI->EMR, iocurrent);
        }
        else
        {
          CLEAR_BIT(EXTI->EMR, iocurrent);
        }

        
        if ((GPIO_Init->Mode & RISING_EDGE) == RISING_EDGE)
        {
          SET_BIT(EXTI->RTSR, iocurrent);
        }
        else
        {
          CLEAR_BIT(EXTI->RTSR, iocurrent);
        }

        
        if ((GPIO_Init->Mode & FALLING_EDGE) == FALLING_EDGE)
        {
          SET_BIT(EXTI->FTSR, iocurrent);
        }
        else
        {
          CLEAR_BIT(EXTI->FTSR, iocurrent);
        }
      }
    }
  }
}


void HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
{
  uint32_t position = 0x00U;
  uint32_t iocurrent = 0x00U;
  uint32_t tmp = 0x00U;
  __IO uint32_t *configregister; 
  uint32_t registeroffset = 0U;

  
  assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  
  while ((GPIO_Pin >> position) != 0U)
  {
    
    iocurrent = (GPIO_Pin) & (1U << position);

    if (iocurrent)
    {
      
      
      configregister = (iocurrent < GPIO_PIN_8) ? &GPIOx->CRL     : &GPIOx->CRH;
      registeroffset = (iocurrent < GPIO_PIN_8) ? (position << 2U) : ((position - 8U) << 2U);

      
      MODIFY_REG(*configregister, ((GPIO_CRL_MODE0 | GPIO_CRL_CNF0) << registeroffset), GPIO_CRL_CNF0_0 << registeroffset);

      
      CLEAR_BIT(GPIOx->ODR, iocurrent);

      
      

      tmp = AFIO->EXTICR[position >> 2U];
      tmp &= 0x0FU << (4U * (position & 0x03U));
      if (tmp == (GPIO_GET_INDEX(GPIOx) << (4U * (position & 0x03U))))
      {
        tmp = 0x0FU << (4U * (position & 0x03U));
        CLEAR_BIT(AFIO->EXTICR[position >> 2U], tmp);

        
        CLEAR_BIT(EXTI->IMR, (uint32_t)iocurrent);
        CLEAR_BIT(EXTI->EMR, (uint32_t)iocurrent);

        
        CLEAR_BIT(EXTI->RTSR, (uint32_t)iocurrent);
        CLEAR_BIT(EXTI->FTSR, (uint32_t)iocurrent);
      }
    }

    position++;
  }
}






GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  GPIO_PinState bitstatus;

  
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  if ((GPIOx->IDR & GPIO_Pin) != (uint32_t)GPIO_PIN_RESET)
  {
    bitstatus = GPIO_PIN_SET;
  }
  else
  {
    bitstatus = GPIO_PIN_RESET;
  }
  return bitstatus;
}


void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
{
  
  assert_param(IS_GPIO_PIN(GPIO_Pin));
  assert_param(IS_GPIO_PIN_ACTION(PinState));

  if (PinState != GPIO_PIN_RESET)
  {
    GPIOx->BSRR = GPIO_Pin;
  }
  else
  {
    GPIOx->BSRR = (uint32_t)GPIO_Pin << 16U;
  }
}


void HAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  GPIOx->ODR ^= GPIO_Pin;
}


HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{
  __IO uint32_t tmp = GPIO_LCKR_LCKK;

  
  assert_param(IS_GPIO_LOCK_INSTANCE(GPIOx));
  assert_param(IS_GPIO_PIN(GPIO_Pin));

  
  SET_BIT(tmp, GPIO_Pin);
  
  GPIOx->LCKR = tmp;
  
  GPIOx->LCKR = GPIO_Pin;
  
  GPIOx->LCKR = tmp;
  
  tmp = GPIOx->LCKR;

  if ((uint32_t)(GPIOx->LCKR & GPIO_LCKR_LCKK))
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
  
  if (__HAL_GPIO_EXTI_GET_IT(GPIO_Pin) != RESET)
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





