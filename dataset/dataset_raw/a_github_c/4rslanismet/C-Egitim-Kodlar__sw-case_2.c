


#include <stdio.h>


int main ()
{
    
    
    
        int secim ;
        
        printf("\t---MENU---\t\n1-selamla\n2-toplama\n3-teklik kontrolü\n0-çıkış\nsecim:");
        
        scanf("%d",&secim);
        
        switch (secim)
        {
            
            case (0):
                return 0;
                
                break;
                
            case (1):
                printf("helllo world\n");
                
                break;
            
            case (2):
                {
                    int s1,s2;
                    
                    printf("iki sayı giriniz:");
                    scanf("%d %d",&s1,&s2);
                
                    printf("toplam: %d\n",s1+s2);
                    
                }
                
                break;
                
            case(3):
                {
                    int s1;
                                    
                    printf("bir sayı giriniz");
                    scanf("%d",&s1);
                    
                    if(s1%2==1)
                        printf("sayı tektir\n");
                        
                    else 
                        printf("sayı çifttir\n");
                }
                    
                break;
            
            
            
            default:
            {
                printf("girilen işlem geçersiz\n");
                return 1;
                
            }
            
                
            
        }
    
    
    
    
    return 0;
    
    
    
    
    
    }
