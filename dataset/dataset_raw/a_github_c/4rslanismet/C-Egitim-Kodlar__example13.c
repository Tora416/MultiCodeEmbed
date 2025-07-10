












#include <stdio.h>

int faktoriyel(int num);


int main ()
{
    int num,fact=0;

    printf("faktöriyelini öğrenmek istediğiniz sayıyı giriniz:\n");
    scanf("%d",&num);

    fact=faktoriyel(num);

    if(fact>0)
        printf("\n[%d]! = [%d]\n",num,fact);
   
return 0;

}

int faktoriyel(int num)
{
    int res=0;

    if(num <= 0)
        printf("\nerror !\n");
    

    else if (num==1)
        return num;

    else
    {
        res=num*faktoriyel(num-1);  
        
    }   
   return -1; 
}