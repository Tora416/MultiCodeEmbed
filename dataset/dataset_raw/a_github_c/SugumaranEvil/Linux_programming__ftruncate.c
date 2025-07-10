





 

#include "ftruncate.h"


int main()
{
    int ftr,file_des;
    char buf[10],snp[30],snp1[30];
    char buf1[8]="sugukavi";
    ssize_t rd,wt;

    file_des = open("./ftext",O_CREAT | O_RDWR,0644); 
    perror("open");                  

    wt = write(file_des,buf1,8);     
    perror("write");

    ftr = ftruncate(file_des,4);     
    perror("ftruncate");
    printf("ftruncate %d\n",ftr);    

    lseek(file_des,0,SEEK_SET);      
    rd = read(file_des,buf,5);       
    perror("read");

    snprintf(snp1,5,"%s",buf);       
    printf("%s",snp1);

    close(file_des);                 
}
