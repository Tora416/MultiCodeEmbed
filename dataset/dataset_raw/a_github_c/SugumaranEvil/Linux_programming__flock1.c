







#include "flock1.h"
#include <stdio.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main()
{
    int file_des;
    ssize_t wt;
    char arr[]="mara_mani";  
    file_des = open("./text",O_RDWR);
    perror("open");             

    wt = write(file_des,arr,9); 
    perror("write");  

    flock(file_des,LOCK_UN);    
    perror("flock");

    close(file_des);            
}

