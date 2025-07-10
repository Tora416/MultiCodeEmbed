






#include "P_msgq_rcv.h"

char buffer[8192];

int main()
{
    int mq_op_ret,mq_rcv_ret;
    struct mq_attr my_mq_attr;
    unsigned int msg_pri = 10;

    my_mq_attr.mq_flags    = 0;
    my_mq_attr.mq_maxmsg  = 10;
    my_mq_attr.mq_msgsize = 8192;

    
    
    mq_op_ret = mq_open("/P_msgq", O_RDONLY);
    perror("mq_open");

    printf("ret value of mq_open = %d\n",mq_op_ret);

    
    
    mq_rcv_ret = mq_receive(mq_op_ret, buffer, 8192,&msg_pri);
    perror("mq_receive");

    printf("ret value of mq_receive = %d\n",mq_rcv_ret);
    printf("Data from sender ==> %s\n",buffer);

}
