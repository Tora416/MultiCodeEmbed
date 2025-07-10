


#define TRACE_LEVEL TRACE_LEVEL_OFF


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "os_port.h"
#include "os_port_rtx.h"
#include "debug.h"


static bool_t running = FALSE;
static OsTask taskTable[OS_PORT_MAX_TASKS];




void osInitKernel(void)
{
   
   running = FALSE;
   
   osMemset(taskTable, 0, sizeof(taskTable));
}




void osStartKernel(OsInitTaskCode task)
{
   
   running = TRUE;
   
   os_sys_init(task);
}




bool_t osCreateStaticTask(OsTask *task, const char_t *name, OsTaskCode taskCode,
   void *param, void *stack, size_t stackSize, int_t priority)
{
   
   task->tid = os_tsk_create_user_ex(taskCode, priority, stack,
      stackSize * sizeof(uint_t), param);

   
   if(task->tid != 0)
      return TRUE;
   else
      return FALSE;
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   uint_t i;
   OsTask *task = NULL;

   
   osSuspendAllTasks();

   
   for(i = 0; i < OS_PORT_MAX_TASKS; i++)
   {
      
      if(!taskTable[i].tid)
         break;
   }

   
   if(i < OS_PORT_MAX_TASKS)
   {
      
      taskTable[i].tid = os_tsk_create_ex(taskCode, priority, param);

      
      if(taskTable[i].tid != 0)
         task = &taskTable[i];
   }

   
   osResumeAllTasks();

   
   return task;
}




void osDeleteTask(OsTask *task)
{
   uint_t i;
   OS_TID tid;

   
   if(task == NULL)
      tid = os_tsk_self();
   else
      tid = task->tid;

   
   osSuspendAllTasks();

   
   for(i = 0; i < OS_PORT_MAX_TASKS; i++)
   {
      
      if(taskTable[i].tid == tid)
      {
         
         taskTable[i].tid = 0;
      }
   }

   
   osResumeAllTasks();

   
   if(task == NULL)
   {
      
      os_tsk_delete_self();
   }
   else
   {
      
      os_tsk_delete(tid);
   }
}




void osDelayTask(systime_t delay)
{
   uint16_t n;

   
   delay = OS_MS_TO_SYSTICKS(delay);

   
   while(delay > 0)
   {
      
      n = MIN(delay, 0xFFFE);
      
      os_dly_wait(n);
      
      delay -= n;
   }
}




void osSwitchTask(void)
{
   
   os_tsk_pass();
}




void osSuspendAllTasks(void)
{
   
   if(running)
   {
      
      tsk_lock();
   }
}




void osResumeAllTasks(void)
{
   
   if(running)
   {
      
      tsk_unlock();
   }
}




bool_t osCreateEvent(OsEvent *event)
{
   
   os_sem_init(event, 0);

   
   return TRUE;
}




void osDeleteEvent(OsEvent *event)
{
   
}




void osSetEvent(OsEvent *event)
{
   
   os_sem_send(event);
}




void osResetEvent(OsEvent *event)
{
   OS_RESULT res;

   
   do
   {
      
      res = os_sem_wait(event, 0);

      
   } while(res == OS_R_OK);
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   uint16_t n;
   OS_RESULT res;

   
   
   if(timeout == INFINITE_DELAY)
   {
      
      res = os_sem_wait(event, 0xFFFF);
   }
   else
   {
      
      timeout = OS_MS_TO_SYSTICKS(timeout);

      
      do
      {
         
         n = MIN(timeout, 0xFFFE);
         
         res = os_sem_wait(event, n);
         
         timeout -= n;

         
      } while(res == OS_R_TMO && timeout > 0);
   }

   
   if(res == OS_R_OK || res == OS_R_SEM)
   {
      
      do
      {
         
         res = os_sem_wait(event, 0);

         
      } while(res == OS_R_OK);

      
      return TRUE;
   }
   else
   {
      
      return FALSE;
   }
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   
   isr_sem_send(event);

   
   return FALSE;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   
   os_sem_init(semaphore, count);

   
   return TRUE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
   
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   uint16_t n;
   OS_RESULT res;

   
   if(timeout == INFINITE_DELAY)
   {
      
      res = os_sem_wait(semaphore, 0xFFFF);
   }
   else
   {
      
      timeout = OS_MS_TO_SYSTICKS(timeout);

      
      do
      {
         
         n = MIN(timeout, 0xFFFE);
         
         res = os_sem_wait(semaphore, n);
         
         timeout -= n;

         
      } while(res == OS_R_TMO && timeout > 0);
   }

   
   if(res == OS_R_OK || res == OS_R_SEM)
      return TRUE;
   else
      return FALSE;
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   os_sem_send(semaphore);
}




bool_t osCreateMutex(OsMutex *mutex)
{
   
   os_mut_init(mutex);

   
   return TRUE;
}




void osDeleteMutex(OsMutex *mutex)
{
   
}




void osAcquireMutex(OsMutex *mutex)
{
   
   os_mut_wait(mutex, 0xFFFF);
}




void osReleaseMutex(OsMutex *mutex)
{
   
   os_mut_release(mutex);
}




systime_t osGetSystemTime(void)
{
   systime_t time;

   
   time = os_time_get();

   
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
