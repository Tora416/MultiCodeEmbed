#include<stdio.h>
int main()
    {
    int amount,tt=0,ot=0,fh=0,h=0,f=0,tw=0,te=0,five=0,to=0,one=0;
    printf("Enter amount");
    scanf("%d",&amount);
    
    if(amount>=2000)
        {
        tt=amount/2000;
        amount=amount-2000*tt;
        }
    if(amount>=1000)
        {
        ot=amount/1000;
        amount=amount-1000*ot;
        }
    if(amount>=500)
        {
        fh=amount/500;
        amount=amount-500*fh;
        }
    if(amount>=100)
        {
        h=amount/100;
        amount=amount-100*h;
        }
    if(amount>=50)
        {
        f=amount/50;
        amount=amount-50*f;
        }
    if(amount>=20)
        {
        tw=amount/20;
        amount=amount-20*tw;
        }
    if(amount>=10)
        {
        te=amount/10;
        amount=amount-10*te;
        }
    if(amount>=5)
        {
        five=amount/5;
        amount=amount-5*five;
        }
    if(amount>=2)
        {
        to=amount/2;
        amount=amount-10*to;
        }
    else
        {
        one=amount;
        }
    printf("\n Total number of notes");
    printf("\n2000: %d",tt);
    printf("\n1000: %d",ot);
    printf("\n500: %d",fh);
    printf("\n100: %d",h);
    printf("\n50: %d",f);
    printf("\n20: %d",tw);
    printf("\n10: %d",te);
    printf("\n5: %d",five);
    printf("\n2: %d",to);
    printf("\n1: %d\n",one);

    return 0;
    }
