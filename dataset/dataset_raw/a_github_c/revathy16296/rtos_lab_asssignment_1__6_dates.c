#include<stdio.h>
#include<stdlib.h>

typedef struct dates{
    int day,month,year;
}date;

void comp_dat(date d1,date d2);

int main()
{
    date d1,d2;
    printf("enter the date 1 in format DD-MM-YYYY:\t");
    scanf("%d-%d-%d",&d1.day,&d1.month,&d1.year);
    printf("enter the date 2 in format DD-MM-YYYY:\t");
    scanf("%d-%d-%d",&d2.day,&d2.month,&d2.year);
    comp_dat(d1,d2);
    return 0;
}


void comp_dat(date d1,date d2)
{
    if((d1.year==d2.year)&&(d1.month==d2.month)&&(d1.day==d2.day))
    {printf("\nBoth the dates are same");}
    else if(d1.year>d2.year||(d1.year==d2.year&&d1.month>d2.month)||(d1.year==d2.year&&d1.month==d2.month&&d1.day>d2.day))
    {printf("\nThe latest date is %d-%d-%d",d1.day,d1.month,d1.year);}
    else
        {printf("\nThe latest date is %d-%d-%d",d2.day,d2.month,d2.year);}
}
    