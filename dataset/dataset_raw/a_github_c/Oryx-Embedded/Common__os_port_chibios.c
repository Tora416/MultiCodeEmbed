


#define TRACE_LEVEL TRACE_LEVEL_OFF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os_port.h"
#include "os_port_chibios.h"
#include "debug.h"


static OsTask taskTable[OS_PORT_MAX_TASKS];
static uint_t *waTable[OS_PORT_MAX_TASKS];




void osInitKernel(void)
{
   
   osMemset(taskTable, 0, sizeof(taskTable));
   osMemset(waTable, 0, sizeof(waTable));

   
   chSysInit();
}




void osStartKernel(void)
{
   
   chThdExit(MSG_OK);
}




bool_t osCreateStaticTask(OsTask *task, const char_t *name, OsTaskCode taskCode,
   void *param, void *stack, size_t stackSize, int_t priority)
{
   
   stackSize *= sizeof(uint_t);

   
   task->tp = chThdCreateStatic(stack, stackSize,
      priority, (tfunc_t) taskCode, param);

   
   if(task->tp != NULL)
      return TRUE;
   else
      return FALSE;
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   uint_t i;
   void *wa;
   OsTask *task = NULL;

   
   stackSize *= sizeof(uint_t);

   
   wa = osAllocMem(THD_WORKING_AREA_SIZE(stackSize));

   
   if(wa != NULL)
   {
      
      chSysLock();

      
      for(i = 0; i < OS_PORT_MAX_TASKS; i++)
      {
         
         if(taskTable[i].tp == NULL)
            break;
      }

      
      if(i < OS_PORT_MAX_TASKS)
      {
         
         taskTable[i].tp = chThdCreateI(wa, THD_WORKING_AREA_SIZE(stackSize),
            priority, (tfunc_t) taskCode, param);

         
         if(taskTable[i].tp != NULL)
         {
            
            chSchWakeupS(taskTable[i].tp, MSG_OK);

            
            task = &taskTable[i];
            
            waTable[i] = wa;

            
            chSysUnlock();
         }
         else
         {
            
            chSysUnlock();
            
            osFreeMem(wa);
         }
      }
      else
      {
         
         chSysUnlock();
         
         osFreeMem(wa);
      }
   }

   
   return task;
}




void osDeleteTask(OsTask *task)
{
   
   if(task == NULL)
      chThdExit(MSG_OK);
   else
      chThdTerminate(task->tp);
}




void osDelayTask(systime_t delay)
{
   
   chThdSleep(OS_MS_TO_SYSTICKS(delay));
}




void osSwitchTask(void)
{
   
   chThdYield();
}




void osSuspendAllTasks(void)
{
   
   chSysLock();
}




void osResumeAllTasks(void)
{
   
   chSysUnlock();
}




bool_t osCreateEvent(OsEvent *event)
{
   
   chBSemObjectInit(event, TRUE);

   
   return TRUE;
}




void osDeleteEvent(OsEvent *event)
{
   
}




void osSetEvent(OsEvent *event)
{
   
   chBSemSignal(event);
}




void osResetEvent(OsEvent *event)
{
   
   chBSemReset(event, TRUE);
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   msg_t msg;

   
   
   if(timeout == 0)
   {
      
      msg = chBSemWaitTimeout(event, TIME_IMMEDIATE);
   }
   else if(timeout == INFINITE_DELAY)
   {
      
      msg = chBSemWaitTimeout(event, TIME_INFINITE);
   }
   else
   {
      
      msg = chBSemWaitTimeout(event, OS_MS_TO_SYSTICKS(timeout));
   }

   
   if(msg == MSG_OK)
      return TRUE;
   else
      return FALSE;
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   
   chBSemSignalI(event);

   
   return FALSE;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   
   chSemObjectInit(semaphore, count);

   
   return TRUE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
   
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   msg_t msg;

   
   if(timeout == 0)
   {
      
      msg = chSemWaitTimeout(semaphore, TIME_IMMEDIATE);
   }
   else if(timeout == INFINITE_DELAY)
   {
      
      msg = chSemWaitTimeout(semaphore, TIME_INFINITE);
   }
   else
   {
      
      msg = chSemWaitTimeout(semaphore, OS_MS_TO_SYSTICKS(timeout));
   }

   
   if(msg == MSG_OK)
      return TRUE;
   else
      return FALSE;
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   chSemSignal(semaphore);
}




bool_t osCreateMutex(OsMutex *mutex)
{
   
   chMtxObjectInit(mutex);

   
   return TRUE;
}




void osDeleteMutex(OsMutex *mutex)
{
   
}




void osAcquireMutex(OsMutex *mutex)
{
   
   chMtxLock(mutex);
}




void osReleaseMutex(OsMutex *mutex)
{
   
#if (CH_KERNEL_MAJOR < 3)
   chMtxUnlock();
#else
   chMtxUnlock(mutex);
#endif
}




systime_t osGetSystemTime(void)
{
   systime_t time;

   
   time = chVTGetSystemTime();

   
   return OS_SYSTICKS_TO_MS(time);
}




void *osAllocMem(size_t size)
{
   void *p;

   
   p = chHeapAlloc(NULL, size);

   
   TRACE_DEBUG("Allocating %" PRIuSIZE " bytes at 0x%08" PRIXPTR "\r\n", size, (uintptr_t) p);

   
   return p;
}




void osFreeMem(void *p)
{
   
   if(p != NULL)
   {
      
      TRACE_DEBUG("Freeing memory at 0x%08" PRIXPTR "\r\n", (uintptr_t) p);

      
      chHeapFree(p);
   }
}




void osIdleLoopHook(void)
{
   uint_t i;

   
   for(i = 0; i < OS_PORT_MAX_TASKS; i++)
   {
      
      if(taskTable[i].tp != NULL)
      {
         
         if(chThdTerminatedX(taskTable[i].tp))
         {
            
            osFreeMem(waTable[i]);

            
            waTable[i] = NULL;
            taskTable[i].tp = NULL;
         }
      }
   }
}
