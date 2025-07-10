                     
       
       
       
       
                     


#include "receiver.h"

int main()
{
   int ret_val;
   int fd,fd_1;
   char buffer[9000000];
   ssize_t ret_read,ret_write;

   
   fd = open("fifo",O_RDONLY);
   perror("open :");

   
   ret_read = read(fd,buffer,9000000);
   perror("read :");

   
   fd_1 = open("rcv.mp3", O_CREAT | O_WRONLY ,0764);
   perror("read :");

   
   ret_write = write(fd_1,buffer,9000000);
   perror("close :");

   
   close(fd);
   close(fd_1);
}
