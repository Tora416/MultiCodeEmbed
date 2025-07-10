
#include <stdio.h>


int main ()

{
    
    
    
    
    int secim ;
    
    printf("1 giriniz");
    scanf("%d",&secim);
    
    switch(secim)
    {
        
        case(1):
            {
                int k=10;
                
                printf("bölüm:%d ",k/0);
                
            }
            
            break;
            
            
            default:
                printf("sayın kullanıcı neden 1 girmiyorsun ayıp değil mi");
        
    }
    
    
    
    return 0;
        
        
        
    
    
    
    
    
    
    
    
    
    
    
    
    
    }
