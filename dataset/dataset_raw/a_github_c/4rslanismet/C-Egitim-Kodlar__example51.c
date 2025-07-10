#include <stdio.h>

int asalKontrol (int x,int y);

int main()
{
    int asal,num1;

    printf("pozitif bir tam sayı giriniz:\n");
    scanf("%d",&num1);

    if(num1==1)
    {
        printf("1 asal değildir\n");
        
        return 0;    
    }

    asal=asalKontrol(num1,(num1/2));  

    if(asal==1)
        printf("%d asaldır\n",num1);

    else
         printf("%d asal değildir\n",num1);

   return 0;     
}

int asalKontrol (int x,int y)  
{                                           
    if(y==1)
        return 1;
    else
    {
        if(x%y==0)  
            return 0;

        else
            asalKontrol(x,y-1);    
    }    

}