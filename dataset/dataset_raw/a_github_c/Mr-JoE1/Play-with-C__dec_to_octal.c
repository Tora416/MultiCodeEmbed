 


 
#include <stdio.h>
 
int main()
{
    int     number,cnt,i;
    int     oct[32];
 
    printf("Enter decimal number: ");
    scanf("%d",&number);
 
     
    cnt=0;              
    while(number>0)
    {
        oct[cnt]=number%8;
        number=number/8;
        cnt++;
    }
 
    
    printf("Octal value is: ");
    for(i=(cnt-1); i>=0;i--)
        printf("%d",oct[i]);
 
    return 0;
}