

         




#include "posix_shm.h"

int main()
{
   int open_fd, munmap_ret, msync_ret;
   ssize_t read_fd;
   char *mmap_ret;
   char buff[50];

   
   open_fd = shm_open("/posix" , O_RDWR , 0644);
   if(open_fd == -1){
       perror("shm_open");
       printf("Return value of shm_open %d\n",open_fd);
   }else {
       perror("shm_open");
       printf("Return value of shm_open %d\n",open_fd);
   }


   
   read_fd = read(open_fd,buff,4096);
   if(read_fd == -1){
    perror("read");
   }else {
    perror("read");
   }

   
   
   mmap_ret = mmap(NULL , 4096 , PROT_READ | PROT_WRITE, MAP_SHARED ,open_fd ,0);
   perror("mmap");

   
   msync_ret = msync(mmap_ret, 4096, MS_SYNC);
   if(msync_ret == -1){
       perror("msync");
   }else {
       perror("msync");
   }

   
   printf("%s\n",buff);

   
   munmap_ret = munmap(mmap_ret, 4096);
   if(munmap_ret == -1) {
       perror("munmap");
   }else {
       perror("munmap");
   }
}
