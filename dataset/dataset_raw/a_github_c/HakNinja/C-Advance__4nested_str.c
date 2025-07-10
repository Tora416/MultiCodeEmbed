#include<stdio.h>
struct NAME
{
    char fn[30],mn[30],ln[30];
};
struct date
{
    int d,m,y;
};
struct student
{
    int rno;
    float per;
    struct  NAME name;
    struct date dob;
};
int main()
{
    int u;
    struct student x;
    printf("Enter Details:\n");
    printf("Enter roll number:");
    scanf("%d",&x.rno);
    printf("Enter name of student");
    printf("\nFirst name:");
    scanf("%s",&x.name.fn);
    printf("Middle name:");
    scanf("%s",&x.name.mn);
    printf("Last name:");
    scanf("%s",&x.name.ln);
    printf("Enter Date Of Birth");
    printf("\nDate:");
    scanf("%d",&x.dob.d);
    printf("Month:");
    scanf("%d",&x.dob.m);
    printf("Year:");
    scanf("%d",&x.dob.y);
    printf("Percentage:");
    scanf("%f",&x.per);
    printf("\n--------------------------------------------------------------------------");
    printf("\nRoll number:%d\n",x.rno);
    printf("\nName:%s %s %s\n",x.name.fn,x.name.mn,x.name.ln);
    printf("DoB:%d/%d/%d\n",x.dob.d,x.dob.m,x.dob.y);
    printf("Percentage:%f\n",x.per);
    
    return(0);
}
