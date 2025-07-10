





 

#include "truncate.h"


int main()
{
    int tr,file_des,sn;
    char buf[10],snp[30],snp1[30];
    char buf1[8]="sugukavi";
    ssize_t rd,wt;

    file_des = open("./text",O_CREAT | O_RDWR,0644);
    perror("open");                   
    printf("fd %d\n",file_des);       

    wt = write(file_des,buf1,8);      
    perror("write");
    printf("write %d\n",wt);

    rd = read(file_des,buf,8);        
    perror("read");
    printf("read %d\n",rd);

    sn = snprintf(snp1,20,"%s",buf);   
    printf("%s\n",snp1);              
    printf("snprintf %d\n",sn);

    tr = truncate("./text",20);       
    perror("truncate");
    printf("truncate %d\n",tr);

    lseek(file_des,0,SEEK_SET);       
    rd = read(file_des,buf,20);      
    perror("read");

    snprintf(snp1,20,"%s",buf);
    printf("%s\n",snp1);

    close(file_des);                  
}
