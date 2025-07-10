






#include "P_msgq_snd.h"

char str[]="Data from POSIX msg queue send\n";









int main()
{
    int mq_op_ret,mq_send_ret;
    struct mq_attr my_mq_attr;

    my_mq_attr.mq_flags   = 0;   
    my_mq_attr.mq_maxmsg  = 10;
    my_mq_attr.mq_msgsize = 8192;

    
    
    mq_op_ret = mq_open("/P_msgq", O_CREAT | O_RDWR, 0644, &my_mq_attr);
    perror("mq_open");

    printf("ret value of mq_open = %d\n",mq_op_ret);

    
    mq_send_ret = mq_send(mq_op_ret, str, strlen(str)+1,10);
    perror("mq_send");

    printf("ret value of mq_send = %d\n",mq_send_ret);
}
