




#include<stdio.h>
#include<stdlib.h>

int FormIp(int no1,int no2,int no3,int no4)
{

    int ret=0;

    no1=no1 & 0x000000ff;

    no2=no2 & 0x000000ff;

    no3=no3 & 0x000000ff;

    no4=no4 & 0x000000ff;


    no1=no1<<24;

    no2=no2<<16;

    no3=no3<<8;

    ret= no1 | no2 | no3 |no4;


    return ret;
}

void split(int no)
{
    int a,b,c,d;

    a=no & 0xff000000;

    b=no & 0x00ff0000;

    c=no & 0x0000ff00;

    d=no & 0x000000ff;

    a = a>>24;

    b=b>>16;

    c=c>>8;

    
    
    printf("\nfirt number is : %d\n",a);
    
    printf("second number is :%d\n",b);

    printf("third number is :%d\n",c);

    printf("fourt number is :%d\n",d);



}
int main()
{
    int iRet=0;
    int a=0,b=0,c=0,d=0;
    printf("enter ip addres\n");
    printf("first value :");
    scanf("%d",&a);
    
    printf("second value :");
        scanf("%d",&b);

    printf("third value :");
        scanf("%d",&c);

    printf("fourth value :");
        scanf("%d",&d);


    iRet=FormIp(a,b,c,d);

    printf("IP address  in one integer  is : %d",iRet);

    split(iRet);

    return 0;
}
