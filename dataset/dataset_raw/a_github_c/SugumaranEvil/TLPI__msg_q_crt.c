

         




#include "msg_q_crt.h"


struct mymsg {
    long mtype;
    char mtext[200];
};


char str1[]="Message from str1\n";
char str2[]="Message from str2\n";
char str3[]="Message from str3\n";

int main(){
    printf("\033[1;31mSystem V Message queue Creating a message\033[0m\n");
    int mesg_id,msgsnd_return;

    struct mymsg my_data1,my_data2,my_data3;

    
    my_data1.mtype  = 1; 
    my_data2.mtype  = 2;
    my_data3.mtype  = 3;

    
    strncpy(my_data1.mtext,str1,strlen(str1)+1);
    strncpy(my_data2.mtext,str2,strlen(str2)+1);
    strncpy(my_data3.mtext,str3,strlen(str3)+1);

    
    mesg_id = msgget(103,IPC_CREAT|0644);
    perror("msgget");

    
    
    msgsnd_return = msgsnd(mesg_id, &my_data1, strlen(str1)+1, 1);
    perror("msgsnd");
    msgsnd_return = msgsnd(mesg_id, &my_data2, strlen(str2)+1, 2);
    perror("msgsnd");
    msgsnd_return = msgsnd(mesg_id, &my_data3, strlen(str3)+1, 3);
    perror("msgsnd");
}
