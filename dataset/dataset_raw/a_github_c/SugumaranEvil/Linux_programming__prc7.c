           




           


#include "write_to_new_file.h"

int main()
{
    int shmid1;
   int fd;
   ssize_t ret_write;
    char data[136];
    char *data_ptr;

   
    shmid1 = shmget(111, 8192, 0);
    perror("shmget: ");
    
    
    
    data_ptr = shmat(shmid1, NULL,0);
    perror("shmat: ");

    
    strcpy(data, data_ptr);

   
    printf("%s\n",data);

   
   
   fd = open("./file", O_CREAT | O_WRONLY ,0644 );

   
   ret_write = write(fd, data , 136);

   
    shmdt(data_ptr);
    perror("shmdt: ");

    return 0;
}
