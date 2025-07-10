


#define TRACE_LEVEL TRACE_LEVEL_OFF


#include <stdio.h>
#include <stdlib.h>
#include "os_port.h"
#include "os_port_none.h"
#include "debug.h"


#if defined(__linux__) || defined(__FreeBSD__)
   #include <sys/time.h>
#elif defined(_WIN32)
   #include <windows.h>
#endif


systime_t systemTicks = 0;




void osInitKernel(void)
{
   
   systemTicks = 0;
}




void osStartKernel(void)
{
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   
   return (OsTask *) (-1);
}




void osDeleteTask(OsTask *task)
{
}




void osDelayTask(systime_t delay)
{
}




void osSwitchTask(void)
{
}




void osSuspendAllTasks(void)
{
}




void osResumeAllTasks(void)
{
}




bool_t osCreateEvent(OsEvent *event)
{
   
   *event = FALSE;
   
   return TRUE;
}




void osDeleteEvent(OsEvent *event)
{
}




void osSetEvent(OsEvent *event)
{
   
   *event = TRUE;
}




void osResetEvent(OsEvent *event)
{
   
   *event = FALSE;
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   
   if(*event)
   {
      
      *event = FALSE;
      
      return TRUE;
   }
   else
   {
      
      return FALSE;
   }
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   
   *event = TRUE;
   
   return FALSE;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   
   *semaphore = count;
   
   return TRUE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   
   if(*semaphore > 0)
   {
      
      *semaphore -= 1;
      
      return TRUE;
   }
   else
   {
      
      return FALSE;
   }
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   *semaphore += 1;
}




bool_t osCreateMutex(OsMutex *mutex)
{
   
   return TRUE;
}




void osDeleteMutex(OsMutex *mutex)
{
}




void osAcquireMutex(OsMutex *mutex)
{
}




void osReleaseMutex(OsMutex *mutex)
{
}




systime_t osGetSystemTime(void)
{
   systime_t time;

#if defined(__linux__) || defined(__FreeBSD__)
   struct timeval tv;
   
   gettimeofday(&tv, NULL);
   
   time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
#elif defined(_WIN32)
   
   time = GetTickCount();
#else
   
   time = systemTicks;
#endif

   
   return OS_SYSTICKS_TO_MS(time);
}




void *osAllocMem(size_t size)
{
   void *p;

   
   p = malloc(size);

   
   TRACE_DEBUG("Allocating %" PRIuSIZE " bytes at 0x%08" PRIXPTR "\r\n", size, (uintptr_t) p);

   
   return p;
}




void osFreeMem(void *p)
{
   
   if(p != NULL)
   {
      
      TRACE_DEBUG("Freeing memory at 0x%08" PRIXPTR "\r\n", (uintptr_t) p);

      
      free(p);
   }
}
