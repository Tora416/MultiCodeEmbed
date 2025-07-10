


#define TRACE_LEVEL TRACE_LEVEL_OFF


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "os_port.h"
#include "os_port_posix.h"
#include "debug.h"


typedef void *(*PthreadTaskCode) (void *param);




void osInitKernel(void)
{
   
}




void osStartKernel(void)
{
   
}




OsTask *osCreateTask(const char_t *name, OsTaskCode taskCode,
   void *param, size_t stackSize, int_t priority)
{
   int_t ret;
   pthread_t thread;

   
   ret = pthread_create(&thread, NULL, (PthreadTaskCode) taskCode, param);

   
   if(ret == 0)
      return (OsTask *) thread;
   else
      return NULL;
}




void osDeleteTask(OsTask *task)
{
   
   if(task == NULL)
   {
      
      pthread_exit(NULL);
   }
}




void osDelayTask(systime_t delay)
{
   
   usleep(delay * 1000);
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
   int_t ret;

   
   ret = sem_init(event, 0, 0);

   
   if(ret == 0)
      return TRUE;
   else
      return FALSE;
}




void osDeleteEvent(OsEvent *event)
{
   
   sem_destroy(event);
}




void osSetEvent(OsEvent *event)
{
   int_t ret;
   int_t value;

   
   ret = sem_getvalue(event, &value);

   
   if(ret == 0 && value == 0)
   {
      
      sem_post(event);
   }
}




void osResetEvent(OsEvent *event)
{
   int_t ret;

   
   do
   {
      
      ret = sem_trywait(event);

      
   } while(ret == 0);
}




bool_t osWaitForEvent(OsEvent *event, systime_t timeout)
{
   int_t ret;
   struct timespec ts;

   
   
   if(timeout == 0)
   {
      
      ret = sem_trywait(event);
   }
   else if(timeout == INFINITE_DELAY)
   {
      
      ret = sem_wait(event);
   }
   else
   {
      
      clock_gettime(CLOCK_REALTIME, &ts);

      
      ts.tv_sec += timeout / 1000;
      ts.tv_nsec += (timeout % 1000) * 1000000;

      
      if(ts.tv_nsec >= 1000000000)
      {
         ts.tv_sec += 1;
         ts.tv_nsec -= 1000000000;
      }

      
      ret = sem_timedwait(event, &ts);
   }

   
   if(ret == 0)
   {
      
      do
      {
         
         ret = sem_trywait(event);

         
      } while(ret == 0);

      
      return TRUE;
   }
   else
   {
      
      return FALSE;
   }
}




bool_t osSetEventFromIsr(OsEvent *event)
{
   
   return FALSE;
}




bool_t osCreateSemaphore(OsSemaphore *semaphore, uint_t count)
{
   int_t ret;

   
   ret = sem_init(semaphore, 0, count);

   
   if(ret == 0)
      return TRUE;
   else
      return FALSE;
}




void osDeleteSemaphore(OsSemaphore *semaphore)
{
   
   sem_destroy(semaphore);
}




bool_t osWaitForSemaphore(OsSemaphore *semaphore, systime_t timeout)
{
   int_t ret;
   struct timespec ts;

   
   if(timeout == 0)
   {
      
      ret = sem_trywait(semaphore);
   }
   else if(timeout == INFINITE_DELAY)
   {
      
      ret = sem_wait(semaphore);
   }
   else
   {
      
      clock_gettime(CLOCK_REALTIME, &ts);

      
      ts.tv_sec += timeout / 1000;
      ts.tv_nsec += (timeout % 1000) * 1000000;

      
      if(ts.tv_nsec >= 1000000000)
      {
         ts.tv_sec += 1;
         ts.tv_nsec -= 1000000000;
      }

      
      ret = sem_timedwait(semaphore, &ts);
   }

   
   if(ret == 0)
      return TRUE;
   else
      return FALSE;
}




void osReleaseSemaphore(OsSemaphore *semaphore)
{
   
   sem_post(semaphore);
}




bool_t osCreateMutex(OsMutex *mutex)
{
   int_t ret;

   
   ret = pthread_mutex_init(mutex, NULL);

   
   if(ret == 0)
      return TRUE;
   else
      return FALSE;
}




void osDeleteMutex(OsMutex *mutex)
{
   
   pthread_mutex_destroy(mutex);
}




void osAcquireMutex(OsMutex *mutex)
{
   
   pthread_mutex_lock(mutex);
}




void osReleaseMutex(OsMutex *mutex)
{
   
   pthread_mutex_unlock(mutex);
}




systime_t osGetSystemTime(void)
{
   struct timeval tv;

   
   gettimeofday(&tv, NULL);

   
   return (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
}




void *osAllocMem(size_t size)
{
   
   return malloc(size);
}




void osFreeMem(void *p)
{
   
   free(p);
}
