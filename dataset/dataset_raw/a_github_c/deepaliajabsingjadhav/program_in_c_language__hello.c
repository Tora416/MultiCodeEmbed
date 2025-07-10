

#include<stdio.h>

void DisplayS()     
{
    printf("Hello\n");
    printf("Hello\n");
    printf("Hello\n");
    printf("Hello\n");
}

void DisplayI()                
{
    int i = 0;
    
    for(i = 1; i<=4;i++)
    {
        printf("Hello\n");      
    }
}

void DisplayR()
{
    static int i = 1;
    
    if(i<=4)
    {
        printf("Hello\n");
        i++;
        DisplayR();
    }
}

int main()
{
    int value = 10;
    
    DisplayR();
    
    printf("End of main");
    return 0;
}
