

         




#include "posix_shm.h"

int main()
{
   int open_fd, munmap_ret, msync_ret;
   ssize_t write_fd;
   char *mmap_ret;
   char buff[50]="Data stored in posix shared memory\n";

   
   open_fd = shm_open("/posix" , O_CREAT | O_RDWR | O_TRUNC , 0644);
   if(open_fd == -1){
       perror("shm_open");
       printf("Return value of shm_open %d\n",open_fd);
   }else {
       perror("shm_open");
       printf("Return value of shm_open %d\n",open_fd);
   }


   
   write_fd = write(open_fd,buff,strlen(buff)+1);
   if(write_fd == -1){
    perror("write");
   }else {
    perror("write");
   }

   
   
   mmap_ret = mmap(NULL , 4096 , PROT_READ | PROT_WRITE, MAP_SHARED ,open_fd ,0);
   perror("mmap");

   
   
   msync_ret = msync(mmap_ret, 4096, MS_SYNC);
   if(msync_ret == -1){
       perror("msync");
   }else {
       perror("msync");
   }

   
   munmap_ret = munmap(mmap_ret, 4096);
   if(munmap_ret == -1) {
       perror("munmap");
   }else {
       perror("munmap");
   }       
   
}
