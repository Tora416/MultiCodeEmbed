#include <stdio.h>

#define SIZE 5
 
int tabanDonusumu(int arr[SIZE]);
int ustAlma(int ust);

int main (void)
{
    int i,binary[SIZE];

    printf("%s\n","onluk tabana dönüştürmek istediğiniz binary değerini giriniz:");

    for(i=0;i<SIZE;i++)
        scanf("%d",&binary[i]);

    printf("binary sayı:");

    for(i=0;i<SIZE;i++)
        printf("%d",binary[i]);

    printf("\n onluk biçim:%d",tabanDonusumu(binary));

}

int tabanDonusumu(int arr[SIZE])
{
    int i,j=0,ust,decimal;

    for(i=SIZE-1;i>0;i--,j++)
    {
        ust=ustAlma(j);
        decimal+=ust*arr[i];

    }
    
    return decimal;

}

int ustAlma(int ust)
{
    int i,deger=1;

    for(i=1;i<=ust;i++)
        deger*=2;  

    if(ust==0)
    deger=1;
    
    return deger;
}





  
