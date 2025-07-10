



#include<stdio.h>

void DisplayI(int no)
{
    while(no > 0)
    {
        printf("%d\n",no);
        no--;
    }
}

void DisplayR(int no)
{
        if(no > 0)
        {
            printf("%d\t",no);
            no--;
            DisplayR(no);
        }
}

int main()
{
    int value = 0;
    printf("Enter number\n");
    scanf("%d",&value);     
    
    DisplayR(value);
    
    printf("End of main");
    return 0;
}

