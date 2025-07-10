







#include "read_txt_header.h"

int main()
{
    int shmid;
    char data[30];
    char *data_ptr;

    
    shmid = shmget(100, 8192, 0); 
    perror("shmget: ");
    
    
    data_ptr = shmat(shmid, NULL,0);
    perror("shmat: ");
    
   
    strcpy(data, data_ptr);
 
   
    printf("%s\n",data);

   
    shmdt(data_ptr);
    perror("shmdt: ");

    return 0;
}
