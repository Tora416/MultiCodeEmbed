


#include <stdio.h>

int main ()
{
    int a,b,c;
    
    printf("bir sayı giriniz:");
    scanf("%d",&a);
    
    
    printf("bir sayı giriniz:");
    scanf("%d",&b);


    printf("bir sayı giriniz:");
    scanf("%d",&c); 
    
    
    if(a<=b && a<=c) 
    {
            printf("a b ve c ye eşit veya küçüktür");
        }
    
    
    if(a>=b && a>=c)
        {
            printf("a b ve c ye eşit veya büyüktür");
        }
    
    return 0;
    
    
    }
