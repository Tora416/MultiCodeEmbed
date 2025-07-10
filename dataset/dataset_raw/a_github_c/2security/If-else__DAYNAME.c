#include<stdio.h>
int main()
    {
    int weekd;
    printf("Enter week day number");
    scanf("%d",&weekd);

    if(weekd==1)
        printf("MONDAY\n");

    else if(weekd==2)
        printf("TUESDAY\n");
    
    else if(weekd==3)
        printf("WEDNESDAY\n");

    else if(weekd==4)
        printf("THURSDAY\n");
    
    else if(weekd==5)
        printf("FRIDAY\n");
    
    else if(weekd==6)
        printf("SATURDAY\n");

    else if(weekd==7)
        printf("SUNDAY\n");
    
    else 
        printf("OOPS!!Enter valid week day number\n");

    return 0;
    }

