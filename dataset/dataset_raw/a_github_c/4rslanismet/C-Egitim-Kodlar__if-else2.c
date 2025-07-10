#include <stdio.h>

int main ()
{
    
    
    
    int s1,s2,s3;
    
    printf("lütfen üç tane sayı giriniz:");
    scanf("%d %d %d",&s1,&s2,&s3);
    
    if(s1<s2 && s1<s3)
        printf("en küçük sayı %d\n",s1);
        
    if(s2<s1 && s2<s3)
        printf("en küçük sayı %d\n",s2);
    
    if(s3<s1 && s3<s2)
        printf("en küçük sayı %d\n",s3);
    
    
    
    if(s1>s2 && s1>s3)
        printf("en büyük sayı %d",s1);
        
    
    if(s2>s1 && s2>s3)
        printf("en büyük sayı %d",s2);   
    
    
    if(s3>s1 && s3>s2)
        printf("en büyük sayı %d",s3);
    
    return 0;
    
    }
