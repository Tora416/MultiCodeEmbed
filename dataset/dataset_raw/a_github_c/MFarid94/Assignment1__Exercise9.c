

#include<stdio.h>

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);            
    setvbuf(stderr , NULL , _IONBF , 0);
    int grade;                                      
    printf("Enter student's grade in percentage: ");
    scanf("%d",&grade);                             
    if(grade >= 85 && grade <=100){
        printf("Student's grade is Excellent");
    }
    else if(grade < 85 && grade >= 75){
        printf("Student's grade is Very good");
    }
    else if(grade < 75 && grade >= 65){
        printf("Student's grade is Good");
    }
    else if(grade < 65 && grade >= 50){
        printf("Student's grade is Passed");
    }
    else if(grade < 50 && grade >= 0){
        printf("Student's grade is Failed");
    }
    else{
        printf("Invalid input");
    }
    return 0;
}
