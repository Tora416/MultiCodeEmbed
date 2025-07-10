


#define TRACE_LEVEL TRACE_LEVEL_OFF


#if (defined(_WIN32) && defined(_DEBUG))
   #define _CRTDBG_MAP_ALLOC
   #include <stdlib.h>
   #include <crtdbg.h>
#endif


#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "os_port.h"
#include "os_port_windows.h"
#include "debug.h"




void osInitKernel(void)
{
   
}




void osStartKernel(void)
{
   
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   void *handle;

   
   handle = CreateThread(NULL, 0,
      (LPTHREAD_START_ROUTINE) taskCode, param, 0, NULL);

   
   return handle;
}




void osDeleteTask(OsTask *task)
{
   
   if(task == NULL)
   {
      
      ExitThread(0);
   }
   else
   {
      
      TerminateThread(task, 0);
   }
}




void osDelayTask(systime_t delay)
{
   
   Sleep(delay);
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
   
   event->handle = CreateEvent(NULL, FALSE, FALSE, NULL);

   
   if(event->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteEvent(OsEvent *event)
{
   
   if(event->handle != NULL)
   {
      
      CloseHandle(event->handle);
   }
}




void osSetEvent(OsEvent *event)
{
   
   SetEvent(event->handle);
}




void osResetEvent(OsEvent *event)
{
   
   ResetEvent(event->handle);
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   
   if(WaitForSingleObject(event->handle, timeout) == WAIT_OBJECT_0)
      return TRUE;
   else
      return FALSE;
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   
   return FALSE;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   
   semaphore->handle = CreateSemaphore(NULL, count, count, NULL);

   
   if(semaphore->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
   
   if(semaphore->handle != NULL)
   {
      
      CloseHandle(semaphore->handle);
   }
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   
   if(WaitForSingleObject(semaphore->handle, timeout) == WAIT_OBJECT_0)
      return TRUE;
   else
      return FALSE;
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   ReleaseSemaphore(semaphore->handle, 1, NULL);
}




bool_t osCreateMutex(OsMutex *mutex)
{
   
   mutex->handle = CreateMutex(NULL, FALSE, NULL);

   
   if(mutex->handle != NULL)
      return TRUE;
   else
      return FALSE;
}




void osDeleteMutex(OsMutex *mutex)
{
   
   if(mutex->handle != NULL)
   {
      
      CloseHandle(mutex->handle);
   }
}




void osAcquireMutex(OsMutex *mutex)
{
   
   WaitForSingleObject(mutex->handle, INFINITE);
}




void osReleaseMutex(OsMutex *mutex)
{
   
   ReleaseMutex(mutex->handle);
}




systime_t osGetSystemTime(void)
{
   
   return GetTickCount();
}




void *osAllocMem(size_t size)
{
   
   return malloc(size);
}




void osFreeMem(void *p)
{
   
   free(p);
}
