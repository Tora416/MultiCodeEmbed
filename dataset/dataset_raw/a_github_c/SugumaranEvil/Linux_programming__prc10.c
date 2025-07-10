







#include "store_txt_header.h"

int main()
{
   int fd,shmid;
   ssize_t rd,op;
   char buffer[30],*data_ptr;

   
   fd = open("./txt",O_RDONLY);

   
   rd = read(fd,buffer,20);

   
   shmid = shmget(100,8192,IPC_CREAT | IPC_EXCL | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH); 
   perror("shmget ");

   
   data_ptr = shmat(shmid,NULL,0);
   perror("shmat  ");

   
   strcpy(data_ptr,buffer);

   
   shmdt(data_ptr);
   perror("shmdt  ");
   return 0;
}
