
#include <stdio.h>


int main()
{
    
    int max,min,s1,s2,s3;
    
    
    printf("lütfen üç tane sayı giriniz:");
    scanf("%d %d %d",&s1,&s2,&s3);
    
    
    min=s1;
    max=s1;
    
    if(max<s2)
        max=s2;
        
    if(max<s3)
        max=s3;
        
    
    
    if(min>s2)
        min=s2;
    
    if(min>s3)
        min=s3;
        
        
    printf("en büyük : %d\nen küçük: %d",max,min);
    
    return 0;
    }
