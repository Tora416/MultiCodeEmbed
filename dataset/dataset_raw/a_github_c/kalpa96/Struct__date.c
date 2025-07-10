#include<stdio.h>

struct Date{
    int day;
    int month;
    int year;
    int no;
}d[2];

int main(){
    int i, j, key=0;

    for(i=0; i<2; i++){
        d[i].no = i+1;
        printf("\nEnter 0%d\n",d[i].no);
        printf("Year : ");
        scanf("%d",&d[i].year);
        printf("Month : ");
        scanf("%d",&d[i].month);
        printf("Day : ");
        scanf("%d",&d[i].day);

        if(d[i].month >12 || d[i].month<=0 ){
            printf("Invalide Month...\n");

            if(d[i].day >30 || d[i].day<=0 ){
            printf("Invalide Date...\n");
            }

            i--;
        }else{
            if(d[i].day >30 || d[i].day<=0 ){
            printf("Invalide Date...\n");
            i--;
            }
        }


    }


    for(j=0; j<1; j++){
        if(d[j].day==d[j+1].day){
            if(d[j].month==d[j+1].month){
                if(d[j].year==d[j+1].year){
                    printf("Dates are equal..\n");
                }
                else{
                    key = 1;
                }
            }
            else{
                key = 1;
            }
        }
        else{
            key = 1;
        }
    }

    if(key==1){
        printf("Dates are not equal.\n");
    }
    return 0;
}