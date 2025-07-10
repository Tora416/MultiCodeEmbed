


#define TRACE_LEVEL TRACE_LEVEL_OFF


#include <stdio.h>
#include <stdlib.h>
#include "os_port.h"
#include "os_port_cmsis_rtos2.h"
#include "debug.h"




void osInitKernel(void)
{
   
   osKernelInitialize();
}




void osStartKernel(void)
{
   
   osKernelStart();
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   osThreadId_t threadId;
   osThreadAttr_t threadAttr;

   
   threadAttr.name = name;
   threadAttr.attr_bits = 0;
   threadAttr.cb_mem = NULL;
   threadAttr.cb_size = 0;
   threadAttr.stack_mem = NULL;
   threadAttr.stack_size = stackSize * sizeof(uint_t);
   threadAttr.priority = (osPriority_t) priority;
   threadAttr.tz_module = 0;
   threadAttr.reserved = 0;

   
   threadId = osThreadNew(taskCode, param, &threadAttr);
   
   return (OsTask *) threadId;
}




void osDeleteTask(OsTask *task)
{
   
   if(task == NULL)
      osThreadExit();
   else
      osThreadTerminate((osThreadId_t) task);
}




void osDelayTask(systime_t delay)
{
   
   osDelay(OS_MS_TO_SYSTICKS(delay));
}




void osSwitchTask(void)
{
   
   osThreadYield();
}




void osSuspendAllTasks(void)
{
   
   if(osKernelGetState() != osKernelInactive)
   {
      
      osKernelLock();
   }
}




void osResumeAllTasks(void)
{
   
   if(osKernelGetState() != osKernelInactive)
   {
      
      osKernelUnlock();
   }
}




bool_t osCreateEvent(OsEvent *event)
{
   osEventFlagsAttr_t eventFlagsAttr;

   
   eventFlagsAttr.name = NULL;
   eventFlagsAttr.attr_bits = 0;

#if defined(os_CMSIS_RTX)
   eventFlagsAttr.cb_mem = &event->cb;
   eventFlagsAttr.cb_size = sizeof(os_event_flags_t);
#elif defined(osRtxVersionKernel)
   eventFlagsAttr.cb_mem = &event->cb;
   eventFlagsAttr.cb_size = sizeof(osRtxEventFlags_t);
#else
   eventFlagsAttr.cb_mem = NULL;
   eventFlagsAttr.cb_size = 0;
#endif

   
   event->id = osEventFlagsNew(&eventFlagsAttr);

   
   if(event->id != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteEvent(OsEvent *event)
{
   
   if(event->id != NULL)
   {
      
      osEventFlagsDelete(event->id);
   }
}




void osSetEvent(OsEvent *event)
{
   
   osEventFlagsSet(event->id, 1);
}




void osResetEvent(OsEvent *event)
{
   
   osEventFlagsClear(event->id, 1);
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   uint32_t flags;

   
   
   if(timeout == INFINITE_DELAY)
   {
      
      flags = osEventFlagsWait(event->id, 1, osFlagsWaitAny, osWaitForever);
   }
   else
   {
      
      flags = osEventFlagsWait(event->id, 1, osFlagsWaitAny,
         OS_MS_TO_SYSTICKS(timeout));
   }

   
   if(flags == 1)
      return TRUE;
   else
      return FALSE;
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   
   osEventFlagsSet(event->id, 1);

   
   return FALSE;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   osSemaphoreAttr_t semaphoreAttr;

   
   semaphoreAttr.name = NULL;
   semaphoreAttr.attr_bits = 0;

#if defined(os_CMSIS_RTX)
   semaphoreAttr.cb_mem = &semaphore->cb;
   semaphoreAttr.cb_size = sizeof(os_semaphore_t);
#elif defined(osRtxVersionKernel)
   semaphoreAttr.cb_mem = &semaphore->cb;
   semaphoreAttr.cb_size = sizeof(osRtxSemaphore_t);
#else
   semaphoreAttr.cb_mem = NULL;
   semaphoreAttr.cb_size = 0;
#endif

   
   semaphore->id = osSemaphoreNew(count, count, &semaphoreAttr);

   
   if(semaphore->id != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
   
   if(semaphore->id != NULL)
   {
      
      osSemaphoreDelete(semaphore->id);
   }
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   osStatus_t status;

   
   if(timeout == INFINITE_DELAY)
   {
      
      status = osSemaphoreAcquire(semaphore->id, osWaitForever);
   }
   else
   {
      
      status = osSemaphoreAcquire(semaphore->id, OS_MS_TO_SYSTICKS(timeout));
   }

   
   if(status == osOK)
      return TRUE;
   else
      return FALSE;
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   osSemaphoreRelease(semaphore->id);
}




bool_t osCreateMutex(OsMutex *mutex)
{
   osMutexAttr_t mutexAttr;

   
   mutexAttr.name = NULL;
   mutexAttr.attr_bits = 0;

#if defined(os_CMSIS_RTX)
   mutexAttr.cb_mem = &mutex->cb;
   mutexAttr.cb_size = sizeof(os_mutex_t);
#elif defined(osRtxVersionKernel)
   mutexAttr.cb_mem = &mutex->cb;
   mutexAttr.cb_size = sizeof(osRtxMutex_t);
#else
   mutexAttr.cb_mem = NULL;
   mutexAttr.cb_size = 0;
#endif

   
   mutex->id = osMutexNew(&mutexAttr);

   
   if(mutex->id != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteMutex(OsMutex *mutex)
{
   
   if(mutex->id != NULL)
   {
      
      osMutexDelete(mutex->id);
   }
}




void osAcquireMutex(OsMutex *mutex)
{
   
   osMutexAcquire(mutex->id, osWaitForever);
}




void osReleaseMutex(OsMutex *mutex)
{
   
   osMutexRelease(mutex->id);
}




systime_t osGetSystemTime(void)
{
   systime_t time;

   
   time = osKernelGetTickCount();

   
   return OS_SYSTICKS_TO_MS(time);
}




void *osAllocMem(size_t size)
{
   void *p;

   
   osSuspendAllTasks();
   
   p = malloc(size);
   
   osResumeAllTasks();

   
   TRACE_DEBUG("Allocating %u bytes at 0x%08X\r\n", size, (uint_t) p);

   
   return p;
}




void osFreeMem(void *p)
{
   
   if(p != NULL)
   {
      
      TRACE_DEBUG("Freeing memory at 0x%08X\r\n", (uint_t) p);

      
      osSuspendAllTasks();
      
      free(p);
      
      osResumeAllTasks();
   }
}
