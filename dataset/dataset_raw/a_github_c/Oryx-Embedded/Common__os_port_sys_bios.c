


#define TRACE_LEVEL TRACE_LEVEL_OFF


#include <stdio.h>
#include <stdlib.h>
#include "os_port.h"
#include "os_port_sys_bios.h"
#include "debug.h"


static bool_t running = FALSE;




void osInitKernel(void)
{
   
   running = FALSE;
}




void osStartKernel(void)
{
   
   running = TRUE;
   
   BIOS_start();
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   Error_Block eb;
   Task_Params taskParams;
   Task_Handle task;

   
   Error_init(&eb);

   
   Task_Params_init(&taskParams);
   taskParams.arg0 = (UArg) param;
   taskParams.stackSize = stackSize * sizeof(uint_t);
   taskParams.priority = priority;

   
   task = Task_create((Task_FuncPtr) taskCode, &taskParams, &eb);

   
   return task;
}




void osDeleteTask(OsTask *task)
{
   
   Task_delete(&task);
}




void osDelayTask(systime_t delay)
{
   
   Task_sleep(OS_MS_TO_SYSTICKS(delay));
}




void osSwitchTask(void)
{
   
   Task_yield();
}




void osSuspendAllTasks(void)
{
   
   if(running)
   {
      
      Task_disable();
   }
}




void osResumeAllTasks(void)
{
   
   if(running)
   {
      
      Task_enable();
   }
}




bool_t osCreateEvent(OsEvent *event)
{
   
   event->handle = Event_create(NULL, NULL);

   
   if(event->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteEvent(OsEvent *event)
{
   
   if(event->handle != NULL)
   {
      
      Event_delete(&event->handle);
   }
}




void osSetEvent(OsEvent *event)
{
   
   Event_post(event->handle, Event_Id_00);
}




void osResetEvent(OsEvent *event)
{
   
   Event_pend(event->handle, Event_Id_00, Event_Id_NONE, BIOS_NO_WAIT);
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   Bool ret;

   
   if(timeout == 0)
   {
      
      ret = Event_pend(event->handle, Event_Id_00,
         Event_Id_NONE, BIOS_NO_WAIT);
   }
   else if(timeout == INFINITE_DELAY)
   {
      
      ret = Event_pend(event->handle, Event_Id_00,
         Event_Id_NONE, BIOS_WAIT_FOREVER);
   }
   else
   {
      
      ret = Event_pend(event->handle, Event_Id_00,
         Event_Id_NONE, OS_MS_TO_SYSTICKS(timeout));
   }

   
   return ret;
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   
   Event_post(event->handle, Event_Id_00);

   
   return FALSE;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   Semaphore_Params semaphoreParams;

   
   Semaphore_Params_init(&semaphoreParams);
   semaphoreParams.mode = Semaphore_Mode_COUNTING;

   
   semaphore->handle = Semaphore_create(count, &semaphoreParams, NULL);

   
   if(semaphore->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
   
   if(semaphore->handle != NULL)
   {
      
      Semaphore_delete(&semaphore->handle);
   }
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   Bool ret;

   
   if(timeout == 0)
   {
      
      ret = Semaphore_pend(semaphore->handle, BIOS_NO_WAIT);
   }
   else if(timeout == INFINITE_DELAY)
   {
      
      ret = Semaphore_pend(semaphore->handle, BIOS_WAIT_FOREVER);
   }
   else
   {
      
      ret = Semaphore_pend(semaphore->handle, OS_MS_TO_SYSTICKS(timeout));
   }

   
   return ret;
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   Semaphore_post(semaphore->handle);
}




bool_t osCreateMutex(OsMutex *mutex)
{
   Semaphore_Params semaphoreParams;

   
   Semaphore_Params_init(&semaphoreParams);
   semaphoreParams.mode = Semaphore_Mode_BINARY_PRIORITY;

   
   mutex->handle = Semaphore_create(1, &semaphoreParams, NULL);

   
   if(mutex->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteMutex(OsMutex *mutex)
{
   
   if(mutex->handle != NULL)
   {
      
      Semaphore_delete(&mutex->handle);
   }
}




void osAcquireMutex(OsMutex *mutex)
{
   
   Semaphore_pend(mutex->handle, BIOS_WAIT_FOREVER);
}




void osReleaseMutex(OsMutex *mutex)
{
   
   Semaphore_post(mutex->handle);
}




systime_t osGetSystemTime(void)
{
   systime_t time;

   
   time = Clock_getTicks();

   
   return OS_SYSTICKS_TO_MS(time);
}




void *osAllocMem(size_t size)
{
   void *p;

   
   osSuspendAllTasks();
   
   p = malloc(size);
   
   osResumeAllTasks();

   
   TRACE_DEBUG("Allocating %" PRIuSIZE " bytes at 0x%08" PRIXPTR "\r\n", size, (uintptr_t) p);

   
   return p;
}




void osFreeMem(void *p)
{
   
   if(p != NULL)
   {
      
      TRACE_DEBUG("Freeing memory at 0x%08" PRIXPTR "\r\n", (uintptr_t) p);

      
      osSuspendAllTasks();
      
      free(p);
      
      osResumeAllTasks();
   }
}
