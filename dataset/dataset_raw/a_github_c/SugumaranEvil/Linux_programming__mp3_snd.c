                             

                  
                  
                  
                  

                             


#include "sender.h"

int main()
{
   int create_pipe;
   int fd,fd_1;
   ssize_t ret_read,ret_write;

   
   char buffer[9000000];

   
   create_pipe = mknod("fifo" , S_IFIFO | 0764,0);

   
   fd = open("/home/sugu/Downloads/baby.mp3",O_RDONLY);

   
   ret_read = read(fd,buffer,9000000);
 
   
   fd_1 = open("fifo",O_WRONLY);

   
   ret_write = write(fd_1,buffer,9000000);

   
   close(fd);
   close(fd_1);
}
