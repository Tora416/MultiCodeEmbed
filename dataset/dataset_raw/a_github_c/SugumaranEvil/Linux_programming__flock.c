







#include "flock.h"

int main()
{
    int file_des;
    ssize_t wt,rd;
    char arr[]="sugukavi";
    char buf[10];
    file_des = open("./text",O_CREAT | O_RDWR,0644);
    perror("open");              

    wt = write(file_des,arr,8);  
    perror("write");

    
    
    flock(file_des,LOCK_EX | LOCK_NB);
    perror("flock");
    sleep(10);                   

    rd = read(file_des,buf,8);   
    perror("read");

    close(file_des);             
}
