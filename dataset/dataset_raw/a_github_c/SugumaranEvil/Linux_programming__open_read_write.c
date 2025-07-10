





  

#include "open_read_write.h"

int main()
{
    int file_des,i;
    char arr[13]="hi i am arr1\n";
    char arr1[13]="hi i am arr1\n";
    char arr2[13]="hi i am arr2\n";
    char rd_fd[100];
    char sarr[100];

    file_des = open("/home/sugu/Linux_Programming/file.txt",O_CREAT | O_RDWR,0655);
    perror("open");

    ssize_t wt,rd;

    
    i=lseek(file_des,0,SEEK_SET); 
    perror("lseek");              
    printf("lseek%d\n",i);        

    
    wt = write(file_des,arr,13);  
    perror("write");              
    printf("write%d\n",wt);       

    
    rd = read(file_des,rd_fd,13); 
    perror("read");               
    printf("Read%d\n",rd);        
    snprintf(sarr,13,"%s\n",rd_fd);
    printf("%s\n",sarr);           
    i=lseek(file_des,0,SEEK_CUR);  
    perror("lseek");               
    printf("lseek%d\n",i);         

    
    wt = write(file_des,arr1,13);  
    perror("write");               
    printf("write%d\n",wt);        

    
    rd = read(file_des,rd_fd,13);  
    perror("read");                
    printf("read%d\n",rd);         
    snprintf(sarr,13,"%s\n",rd_fd);
    printf("%s\n",sarr);           

    i=lseek(file_des,-15,SEEK_END);
    perror("lseek");               
    printf("lseek%d\n",i);         

    
    wt = write(file_des,arr2,13);  
    perror("write");               
    printf("write%d\n",wt);        

    
    rd = read(file_des,rd_fd,13);  
    perror("read");                
    printf("Read%d\n",rd);         
    snprintf(sarr,13,"%s\n",rd_fd);
    printf("%s\n",sarr);           

    close(file_des);               
    perror("close");
}
