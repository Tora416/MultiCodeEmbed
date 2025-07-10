           




            


#include "header.h"

struct my_message
{
   long mtype; 
   char buffer[30]; 
};

char string1[]="string 14 through msgqueue\n";

int main()
{
   int msgid;
   int size;
   int ret_msgsnd;
   struct my_message msg_buffer;

   
   
   
   msgid = msgget(1004,IPC_CREAT | 0644);
   perror("msgget");

   
   strcpy(msg_buffer.buffer,string1);

   
   msg_buffer.mtype = 14; 
   size = strlen(string1)+1;

   
   
   ret_msgsnd = msgsnd(msgid,&msg_buffer,size,0);
   perror("msgget");
}
