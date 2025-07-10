#include  <stdio.h>
#include  <stdlib.h>
#include  <sys/ipc.h>
#include  <sys/shm.h>
#include  <stdlib.h>
#include  <sys/types.h>
#include <fcntl.h>
#include<sys/wait.h>
#include<unistd.h>
#include<errno.h>

int  ClientProcess(float SharedMem[]);
int main()
{
     int    ShmID,p[2];
     pipe(p);
     float    *ShmPTR; 
     pid_t  pid; 
     int    status;
     int a[10],i;
     
     printf("enter the 10 array elements\n");
     for(i=0;i<10;i++)
     {
         scanf("%d",&a[i]);
     }
     ShmID = shmget(IPC_PRIVATE, 10*sizeof(int), IPC_CREAT | 0666); 
     if (ShmID < 0) {
          printf("*** shmget error (server) ***\n");
          exit(1);
     }

     printf("Server has received a shared memory of 10 integers...\n");
     ShmPTR = (float *) shmat(ShmID, NULL, 0);

    

     printf("Server has attached the shared memory...\n");
     
     for(i=0;i<10;i++)
     {
         ShmPTR[i]=a[i];
     }
     pid=fork();
     if (pid == 0) {
        float sum;
        sum=ClientProcess(ShmPTR);
        close(p[0]);
        write(p[1],&sum,sizeof(sum));
        close(p[1]);
          exit(0);
     }
     
     else{
         wait(&status);
         float sum,avg;
         close(p[1]);
         read(p[0],&sum,sizeof(sum));
         avg=sum/10;
        printf("the average is %f\n",avg);
        shmdt((void *) ShmPTR); 
        shmctl(ShmID, IPC_RMID, NULL);
     }
     return 0;
}
     
     
     
     int  ClientProcess(float  SharedMem[])
     {
     float sum=0,product=1;
     int i;
     
     for(i=0;i<10;i++)
     {
         sum+=(SharedMem[i]);
     }
     printf("the sum is %f\n",sum);
     
     for(i=0;i<10;i++)
     {
         product*=(SharedMem[i]);
     }
     printf("the product are %f\n",product);
     return (sum);
     }