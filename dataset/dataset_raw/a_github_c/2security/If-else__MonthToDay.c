#include<stdio.h>
int main()
    {
    int mno;
    printf("Enter the month number");
    scanf("%d",&mno);

    if(mno==1)
        printf("\n January months 31 days\n");
    else if(mno==2) 
        printf("\n February month 28 or 29 days\n");
    else if(mno==3) 
        printf("\n March month 31 days\n");     
    else if(mno==4) 
        printf("\n April month 30 days\n");
    else if(mno==5) 
        printf("\n May month 31 days\n");   
    else if(mno==6) 
        printf("\n June month 30 days\n");
    else if(mno==7) 
        printf("\n July month 31 days\n");  
    else if(mno==8) 
        printf("\n August month 31 days\n");
    else if(mno==9) 
        printf("\n September month 30 days\n");     
    else if(mno==10) 
        printf("\n October month 31 days\n");
    else if(mno==11) 
        printf("\n November month 30 days\n");      
    else if(mno==12) 
        printf("\n December month 31 days\n");
    else
        printf("\n OOPS!! Enter corrent month number\n");
    return 0;
    }




