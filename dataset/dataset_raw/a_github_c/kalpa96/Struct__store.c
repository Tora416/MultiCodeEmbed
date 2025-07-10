#include<stdio.h>
struct student{
    char name[50],address[60];
    int no,id,age;
    float marks;
} s[10];

int main() {
    int i;
    printf("Enter information of students:\n");

    
    for (i=0;i<5;++i) {
        s[i].no = i+1;
        printf("\nStudent 0%d\n", s[i].no);
        printf("Enter ID number : ");
        scanf("%d",&s[i].id);
        printf("Enter name : ");
        scanf("%s",&s[i].name);
        printf("Enter age : ");
        scanf("%d",&s[i].age);
        printf("Enter address : ");
        scanf("%s",&s[i].address);
        printf("Enter marks : ");
        scanf("%f",&s[i].marks);
    }
    printf("Displaying Information:\n\n");

    
    for (i=0;i<5;++i){
        printf("\nStudent : %d\n",i+1);
        printf("ID number : %d\n",s[i].id);
        printf("Name : ");
        puts(s[i].name);
        printf("Age : %d\n",s[i].age);
        printf("Address : ");
        puts(s[i].address);
        printf("Marks: %.1f",s[i].marks);
        printf("\n");
    }
    return 0;
}