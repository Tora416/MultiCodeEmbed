


#define TRACE_LEVEL TRACE_LEVEL_OFF


#include <stdio.h>
#include <stdlib.h>
#include "os_port.h"
#include "os_port_freertos.h"
#include "debug.h"




void osInitKernel(void)
{
}




void osStartKernel(void)
{
   
   vTaskStartScheduler();
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   portBASE_TYPE status;
   TaskHandle_t task = NULL;

   
   status = xTaskCreate((TaskFunction_t) taskCode, name, stackSize, param,
      priority, &task);

   
   if(status == pdPASS)
      return task;
   else
      return NULL;
}




void osDeleteTask(OsTask *task)
{
   
   vTaskDelete((TaskHandle_t) task);
}




void osDelayTask(systime_t delay)
{
   
   vTaskDelay(OS_MS_TO_SYSTICKS(delay));
}




void osSwitchTask(void)
{
   
   taskYIELD();
}




void osSuspendAllTasks(void)
{
   
   if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
   {
      
      vTaskSuspendAll();
   }
}




void osResumeAllTasks(void)
{
   
   if(xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
   {
      
      xTaskResumeAll();
   }
}




bool_t osCreateEvent(OsEvent *event)
{
#if (configSUPPORT_STATIC_ALLOCATION == 1)
   
   event->handle = xSemaphoreCreateBinaryStatic(&event->buffer);
#else
   
   event->handle = xSemaphoreCreateBinary();
#endif

   
   if(event->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteEvent(OsEvent *event)
{
   
   if(event->handle != NULL)
   {
      
      vSemaphoreDelete(event->handle);
   }
}




void osSetEvent(OsEvent *event)
{
   
   xSemaphoreGive(event->handle);
}




void osResetEvent(OsEvent *event)
{
   
   xSemaphoreTake(event->handle, 0);
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   portBASE_TYPE ret;

   
   if(timeout == INFINITE_DELAY)
   {
      
      ret = xSemaphoreTake(event->handle, portMAX_DELAY);
   }
   else
   {
      
      ret = xSemaphoreTake(event->handle, OS_MS_TO_SYSTICKS(timeout));
   }

   
   return ret;
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   portBASE_TYPE flag = FALSE;

   
   xSemaphoreGiveFromISR(event->handle, &flag);

   
   return flag;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
#if (configSUPPORT_STATIC_ALLOCATION == 1)
   
   semaphore->handle = xSemaphoreCreateCountingStatic(count, count,
      &semaphore->buffer);
#else
   
   semaphore->handle = xSemaphoreCreateCounting(count, count);
#endif

   
   if(semaphore->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
   
   if(semaphore->handle != NULL)
   {
      
      vSemaphoreDelete(semaphore->handle);
   }
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   portBASE_TYPE ret;

   
   if(timeout == INFINITE_DELAY)
   {
      
      ret = xSemaphoreTake(semaphore->handle, portMAX_DELAY);
   }
   else
   {
      
      ret = xSemaphoreTake(semaphore->handle, OS_MS_TO_SYSTICKS(timeout));
   }

   
   return ret;
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   xSemaphoreGive(semaphore->handle);
}




bool_t osCreateMutex(OsMutex *mutex)
{
#if (configSUPPORT_STATIC_ALLOCATION == 1)
   
   mutex->handle = xSemaphoreCreateMutexStatic(&mutex->buffer);
#else
   
   mutex->handle = xSemaphoreCreateMutex();
#endif

   
   if(mutex->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteMutex(OsMutex *mutex)
{
   
   if(mutex->handle != NULL)
   {
      
      vSemaphoreDelete(mutex->handle);
   }
}




void osAcquireMutex(OsMutex *mutex)
{
   
   xSemaphoreTake(mutex->handle, portMAX_DELAY);
}




void osReleaseMutex(OsMutex *mutex)
{
   
   xSemaphoreGive(mutex->handle);
}




systime_t osGetSystemTime(void)
{
   systime_t time;

   
   time = xTaskGetTickCount();

   
   return OS_SYSTICKS_TO_MS(time);
}




void *osAllocMem(size_t size)
{
   void *p;

   
   p = pvPortMalloc(size);

   
   TRACE_DEBUG("Allocating %" PRIuSIZE " bytes at 0x%08" PRIXPTR "\r\n", size, (uintptr_t) p);

   
   return p;
}




void osFreeMem(void *p)
{
   
   if(p != NULL)
   {
      
      TRACE_DEBUG("Freeing memory at 0x%08" PRIXPTR "\r\n", (uintptr_t) p);

      
      vPortFree(p);
   }
}


#if 0



void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
   (void) pcTaskName;
   (void) pxTask;

   taskDISABLE_INTERRUPTS();
   while(1);
}




void vAssertCalled(const char *pcFile, unsigned long ulLine)
{
   volatile unsigned long ul = 0;

   (void) pcFile;
   (void) ulLine;

   taskENTER_CRITICAL();

   
   while(ul == 0)
   {
      portNOP();
   }

   taskEXIT_CRITICAL();
}

#endif
