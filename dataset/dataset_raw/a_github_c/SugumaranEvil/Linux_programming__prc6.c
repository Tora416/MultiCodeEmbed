           




           

#include "collects_msg.h"

struct my_message
{
  long mtype; 
  char Buffer[150]; 
};

int main()
{
  int msgid;
  int shmid1,i=0,j;
  char *data_ptr;
  int ret_msgrcv;
  struct my_message msg_buffer;
  char str[136];

  
  
  msgid = msgget(1001,0644);
  perror("msgget :");

  
  
  ret_msgrcv = msgrcv(msgid, &msg_buffer, 200,11 ,0);
  perror("msgrcv :");

  
  for(j=0 ;msg_buffer.Buffer[j]!='\0'; i++ ,j++)
     str[i]=msg_buffer.Buffer[j];
  
  str[i]='\n';

  
  
  msgid = msgget(1002,0644);
  perror("msgget :");

  
  
  ret_msgrcv = msgrcv(msgid, &msg_buffer, 200,12 ,0);
  perror("msgrcv :");

  
  for(j=0 ;msg_buffer.Buffer[j]!='\0'; i++ ,j++)
     str[i]=msg_buffer.Buffer[j];
  
  str[i]='\n';

  
  
  msgid = msgget(1003,IPC_CREAT|0644);
  perror("msgget :");

  
  
  ret_msgrcv = msgrcv(msgid, &msg_buffer, 200,13 ,0); 
  perror("msgrcv :");

  
  for(j=0 ;msg_buffer.Buffer[j]!='\0'; i++ ,j++)
     str[i]=msg_buffer.Buffer[j];
  
  str[i]='\n';

  
  
  msgid = msgget(1004,IPC_CREAT|0644);
  perror("msgget :");

  
  
  ret_msgrcv = msgrcv(msgid, &msg_buffer, 200,14 ,0); 
  perror("msgrcv :");

  
  for(j=0 ;msg_buffer.Buffer[j]!='\0'; i++ ,j++)
     str[i]=msg_buffer.Buffer[j];
  
  str[i]='\n';

  
  
  msgid = msgget(1005,IPC_CREAT|0644);
  perror("msgget :");

  
  
  ret_msgrcv = msgrcv(msgid, &msg_buffer, 200,15 ,0); 
  perror("msgrcv :");

  
  for(j=0 ;msg_buffer.Buffer[j]!='\0'; i++ ,j++)
     str[i]=msg_buffer.Buffer[j];
  
  str[i]='\n';

  
  printf("i = %d\n",i);

  
  shmid1 = shmget(111,8192,IPC_CREAT | S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
  perror("shmget :");

  
  data_ptr = shmat(shmid1,NULL,0);
  perror("shmat  :");

  
  strcpy(data_ptr,str);

  
  shmdt(data_ptr);
  perror("shmdt  :");
  return 0;
}
