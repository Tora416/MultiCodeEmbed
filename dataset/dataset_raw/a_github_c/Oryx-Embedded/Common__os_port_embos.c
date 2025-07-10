


#define TRACE_LEVEL TRACE_LEVEL_OFF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os_port.h"
#include "os_port_embos.h"
#include "debug.h"


void osIdleTaskHook(void);


static OS_TASK *tcbTable[OS_PORT_MAX_TASKS];
static void *stkTable[OS_PORT_MAX_TASKS];




void osInitKernel(void)
{
   
   osMemset(tcbTable, 0, sizeof(tcbTable));
   osMemset(stkTable, 0, sizeof(stkTable));

   
   OS_IncDI();
   
   OS_InitKern();
   
   OS_InitHW();
}




void osStartKernel(void)
{
   
   OS_Start();
}




bool_t osCreateStaticTask(OsTask *task, const char_t *name, OsTaskCode taskCode,
   void *param, void *stack, size_t stackSize, int_t priority)
{
   
   OS_CreateTaskEx(task, name, priority, taskCode,
      stack, stackSize * sizeof(uint_t), 1, param);

   
   return TRUE;
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   uint_t i;
   OS_TASK *task;
   void *stack;

   
   osSuspendAllTasks();

   
   for(i = 0; i < OS_PORT_MAX_TASKS; i++)
   {
      
      if(tcbTable[i] == NULL)
         break;
   }

   
   if(i < OS_PORT_MAX_TASKS)
   {
      
      task = osAllocMem(sizeof(OS_TASK));

      
      if(task != NULL)
      {
         
         stack = osAllocMem(stackSize * sizeof(uint_t));

         
         if(stack != NULL)
         {
            
            OS_CreateTaskEx(task, name, priority, taskCode,
               stack, stackSize * sizeof(uint_t), 1, param);

            
            tcbTable[i] = task;
            
            stkTable[i] = stack;
         }
         else
         {
            osFreeMem(task);
            
            task = NULL;
         }
      }
   }
   else
   {
      
      task = NULL;
   }

   
   osResumeAllTasks();

   
   return task;
}




void osDeleteTask(OsTask *task)
{
   
   OS_TerminateTask(task);
}




void osDelayTask(systime_t delay)
{
   
   OS_Delay(OS_MS_TO_SYSTICKS(delay));
}




void osSwitchTask(void)
{
   
}




void osSuspendAllTasks(void)
{
   
   if(OS_IsRunning())
   {
      
      OS_SuspendAllTasks();
   }
}




void osResumeAllTasks(void)
{
   
   if(OS_IsRunning())
   {
      
      OS_ResumeAllSuspendedTasks();
   }
}




bool_t osCreateEvent(OsEvent *event)
{
   
   OS_EVENT_Create(event);

   
   return TRUE;
}




void osDeleteEvent(OsEvent *event)
{
   
   if(OS_IsRunning())
   {
      
      OS_EVENT_Delete(event);
   }
}




void osSetEvent(OsEvent *event)
{
   
   OS_EVENT_Set(event);
}




void osResetEvent(OsEvent *event)
{
   
   OS_EVENT_Reset(event);
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   bool_t ret;

   
   
   if(timeout == 0)
   {
      
      ret = OS_EVENT_Get(event);
   }
   else if(timeout == INFINITE_DELAY)
   {
      
      OS_EVENT_Wait(event);
      ret = TRUE;
   }
   else
   {
      
      ret = !OS_EVENT_WaitTimed(event, OS_MS_TO_SYSTICKS(timeout));
   }

   
   return ret;
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   
   OS_EVENT_Set(event);

   
   return FALSE;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   
   OS_CreateCSema(semaphore, count);

   
   return TRUE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
   
   if(OS_IsRunning())
   {
      
      OS_DeleteCSema(semaphore);
   }
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   bool_t ret;

   
   if(timeout == 0)
   {
      
      ret = OS_CSemaRequest(semaphore);
   }
   else if(timeout == INFINITE_DELAY)
   {
      
      OS_WaitCSema(semaphore);
      ret = TRUE;
   }
   else
   {
      
      ret = OS_WaitCSemaTimed(semaphore, OS_MS_TO_SYSTICKS(timeout));
   }

   
   return ret;
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   OS_SignalCSema(semaphore);
}




bool_t osCreateMutex(OsMutex *mutex)
{
   
   OS_CreateRSema(mutex);

   
   return TRUE;
}




void osDeleteMutex(OsMutex *mutex)
{
   
   if(OS_IsRunning())
   {
      
      OS_DeleteRSema(mutex);
   }
}




void osAcquireMutex(OsMutex *mutex)
{
   
   OS_Use(mutex);
}




void osReleaseMutex(OsMutex *mutex)
{
   
   OS_Unuse(mutex);
}




systime_t osGetSystemTime(void)
{
   systime_t time;

   
   time = OS_GetTime32();

   
   return OS_SYSTICKS_TO_MS(time);
}




void *osAllocMem(size_t size)
{
   void *p;

   
   p = OS_malloc(size);

   
   TRACE_DEBUG("Allocating %" PRIuSIZE " bytes at 0x%08" PRIXPTR "\r\n", size, (uintptr_t) p);

   
   return p;
}




void osFreeMem(void *p)
{
   
   if(p != NULL)
   {
      
      TRACE_DEBUG("Freeing memory at 0x%08" PRIXPTR "\r\n", (uintptr_t) p);

      
      OS_free(p);
   }
}
