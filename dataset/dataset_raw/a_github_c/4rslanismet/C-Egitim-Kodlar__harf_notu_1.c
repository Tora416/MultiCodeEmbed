



#include <stdio.h>

int main ()
{
    
    int n;
    
    printf("ders notunuzu 0-100 arasında giriniz:");
    scanf("%d",&n);
    
            
        if(90<=n && n<=100)
            printf("harf notunuz A");
    
    
        else if(80<=n && n<90)
            printf("harf notunuz B");
    
    
        else if(70<=n && n<80)
            printf("harf notunuz C");   
        
        else 
            {
                if(0<=n && n<=100)
                printf("harf notunuz F");
                
                else 
                  printf("geçersiz not girildi");
            
        }
    
    return 0;
    }

