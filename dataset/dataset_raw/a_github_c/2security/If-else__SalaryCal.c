#include<stdio.h>
int main()
    {
    float basicsal,HRA,DA;
    printf("Enter the basic salary");
    scanf("%f",&basicsal);
    
    if(basicsal>20000)
        {
        HRA=basicsal*30/100;
        DA=basicsal*95/100;
        }
    else if(basicsal<=20000)
        {
        HRA=basicsal*25/100;
        DA=basicsal*90/100;
        }
    else if(basicsal<=10000)
        {
        HRA=basicsal*20/100;
        DA=basicsal*80/100;
        }
    printf("\n Gross salary=%f\n",basicsal+HRA+DA);

    printf("\n");   
    return 0;
    }   
        
    
    

    
        
