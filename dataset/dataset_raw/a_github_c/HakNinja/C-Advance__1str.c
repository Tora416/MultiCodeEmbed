#include<stdio.h>
struct student
{
    int rno;
    float per;
    char name[30];
};
int main()
{
    struct student x;
    printf("Enter Details:\n");
    printf("Enter roll number:");
    scanf("%d",&x.rno);
    printf("Enter name of student:");
    scanf("%s",x.name);
    printf("Percentage:");
    scanf("%f",&x.per);
    printf("\n--------------------------------------------------------------------------");
    printf("\nRoll number:%d\n",x.rno);
    printf("\nName:%s\n",x.name);
    printf("Percentage:%f\n",x.per);
    return(0);
}









