


#include "stm32f4xx_hal.h"





#ifdef HAL_DMA_MODULE_ENABLED







static void DMA_MultiBufferSetConfig(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength);











HAL_StatusTypeDef HAL_DMAEx_MultiBufferStart(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t SecondMemAddress, uint32_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  
  assert_param(IS_DMA_BUFFER_SIZE(DataLength));
  
  
  if (hdma->Init.Direction == DMA_MEMORY_TO_MEMORY)
  {
    hdma->ErrorCode = HAL_DMA_ERROR_NOT_SUPPORTED;
    status = HAL_ERROR;
  }
  else
  {
    
    __HAL_LOCK(hdma);
    
    if(HAL_DMA_STATE_READY == hdma->State)
    {
      
      hdma->State = HAL_DMA_STATE_BUSY; 
      
      
      hdma->Instance->CR |= (uint32_t)DMA_SxCR_DBM;
      
      
      hdma->Instance->M1AR = SecondMemAddress;
      
      
      DMA_MultiBufferSetConfig(hdma, SrcAddress, DstAddress, DataLength);
      
      
      __HAL_DMA_ENABLE(hdma);
    }
    else
    {
      
      status = HAL_BUSY;
    }
  }
  return status;
}


HAL_StatusTypeDef HAL_DMAEx_MultiBufferStart_IT(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t SecondMemAddress, uint32_t DataLength)
{
  HAL_StatusTypeDef status = HAL_OK;
  
  
  assert_param(IS_DMA_BUFFER_SIZE(DataLength));
  
  
  if (hdma->Init.Direction == DMA_MEMORY_TO_MEMORY)
  {
    hdma->ErrorCode = HAL_DMA_ERROR_NOT_SUPPORTED;
    return HAL_ERROR;
  }
  
  
  if ((NULL == hdma->XferCpltCallback) || (NULL == hdma->XferM1CpltCallback) || (NULL == hdma->XferErrorCallback))
  {
    hdma->ErrorCode = HAL_DMA_ERROR_PARAM;
    return HAL_ERROR;
  }
  
  
  __HAL_LOCK(hdma);
  
  if(HAL_DMA_STATE_READY == hdma->State)
  {
    
    hdma->State = HAL_DMA_STATE_BUSY;
    
    
    hdma->ErrorCode = HAL_DMA_ERROR_NONE;
    
    
    hdma->Instance->CR |= (uint32_t)DMA_SxCR_DBM;
    
    
    hdma->Instance->M1AR = SecondMemAddress;
    
    
    DMA_MultiBufferSetConfig(hdma, SrcAddress, DstAddress, DataLength); 
    
    
    __HAL_DMA_CLEAR_FLAG (hdma, __HAL_DMA_GET_TC_FLAG_INDEX(hdma));
    __HAL_DMA_CLEAR_FLAG (hdma, __HAL_DMA_GET_HT_FLAG_INDEX(hdma));
    __HAL_DMA_CLEAR_FLAG (hdma, __HAL_DMA_GET_TE_FLAG_INDEX(hdma));
    __HAL_DMA_CLEAR_FLAG (hdma, __HAL_DMA_GET_DME_FLAG_INDEX(hdma));
    __HAL_DMA_CLEAR_FLAG (hdma, __HAL_DMA_GET_FE_FLAG_INDEX(hdma));

    
    hdma->Instance->CR  |= DMA_IT_TC | DMA_IT_TE | DMA_IT_DME;
    hdma->Instance->FCR |= DMA_IT_FE;
    
    if((hdma->XferHalfCpltCallback != NULL) || (hdma->XferM1HalfCpltCallback != NULL))
    {
      hdma->Instance->CR  |= DMA_IT_HT;
    }
    
    
    __HAL_DMA_ENABLE(hdma); 
  }
  else
  {     
    
    __HAL_UNLOCK(hdma);   
    
    
    status = HAL_BUSY;
  }  
  return status; 
}


HAL_StatusTypeDef HAL_DMAEx_ChangeMemory(DMA_HandleTypeDef *hdma, uint32_t Address, HAL_DMA_MemoryTypeDef memory)
{
  if(memory == MEMORY0)
  {
    
    hdma->Instance->M0AR = Address;
  }
  else
  {
    
    hdma->Instance->M1AR = Address;
  }

  return HAL_OK;
}








static void DMA_MultiBufferSetConfig(DMA_HandleTypeDef *hdma, uint32_t SrcAddress, uint32_t DstAddress, uint32_t DataLength)
{  
  
  hdma->Instance->NDTR = DataLength;
  
  
  if((hdma->Init.Direction) == DMA_MEMORY_TO_PERIPH)
  {   
    
    hdma->Instance->PAR = DstAddress;
    
    
    hdma->Instance->M0AR = SrcAddress;
  }
  
  else
  {
    
    hdma->Instance->PAR = SrcAddress;
    
    
    hdma->Instance->M0AR = DstAddress;
  }
}



#endif 





