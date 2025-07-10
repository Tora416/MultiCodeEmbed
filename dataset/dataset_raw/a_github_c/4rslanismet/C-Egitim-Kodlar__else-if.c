



#include <stdio.h>

int main ()
{
    
    int a,b;
    
    printf("lütfen bir sayı giriniz:");
    scanf("%d",&a);
    
    
    printf("lütfen bir sayı giriniz:");
    scanf("%d",&b);
    
    if(a<b)
        printf("a b'den küçüktür");
        
    
    else if(a>b)
        printf("a b'den büyüktür");
    
    else 
        printf("a b ye eşittir");
            
    
    return 0;
    }
