


#include <stdio.h> 
#include <math.h>

#define SIZE 5

int binaryToDecimal(int arr[]);

int main()
{
    int i,binaryNum[SIZE],decimal;
      
    printf("%s\n","en fazla 5 basamak olmak üzere binary sayıyı giriniz:");
    
    for(i=SIZE;i>0;i--)
        scanf("%d",&binaryNum[i]);

    decimal=binaryToDecimal(binaryNum);

    printf("%s","girilen binary değer:");

    for(i=SIZE;i>0;i--)
        printf("%d",binaryNum[i]);

    printf("\ndecimal sayı:%d",decimal);

    return 0;
}

int binaryToDecimal(int arr[])
{
    int i,j=4,decimalNum=0;

    for(i=SIZE;i>0;i--)
    {
        decimalNum+=pow(2,j)*arr[i];
        j--;
    }
     

    
   return decimalNum;
}