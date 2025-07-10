#include<stdio.h>

struct student{
    char name[50],address[60];
    int no,id,age;
    float marks;
} s[10];

int main() {
    int i;
    printf("Enter information of students:\n");

    
    for (i=0;i<11;++i) {
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
    printf("\nDisplaying Information:\n");

    
    for (i=0;i<11;i++){
        if(s[i].age==14){
            printf("Name : ");
            puts(s[i].name);
        }
    }
    return 0;
}