#include<stdio.h>
int main()
    {
    int unit;
    float pay,Surpay;
    printf("\nEnter the unit consumed\n");
    scanf("%d",&unit);
        
    if(unit<=50)
        {
        pay=unit * 0.50;
        unit=unit-50;
        }

    if(unit<=150)
        {       
        pay=pay+unit*0.75;
        unit=unit-100;
        }
    if(unit<=250)
        {
        pay=pay+unit*1.20;
        unit=unit-100;
        }
    else
        {
        pay=pay+unit*1.50;
        }

    Surpay=pay*0.2;
    pay=pay+Surpay;

    printf("\nPay of %f\n",pay);    

    printf("\n");   
    return 0;
    }   
        
    
    

    
        
