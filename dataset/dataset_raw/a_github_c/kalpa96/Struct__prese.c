#include<stdio.h>

struct Marks {
    int ID_no;
    char name[30];
    float chem_marks, maths_marks, phy_marks;
};

int main() {
    
    struct Marks marks[5];
    int i;

    for(i=0;i<1;i++){
        printf("Student %d\n",i+1);
        printf("Enter ID no. : ");
        scanf("%d",&marks[i].ID_no);
        printf("Enter name : ");
        scanf("%s",&marks[i].name);
        printf("Enter Chemistry marks : ");
        scanf("%f",&marks[i].chem_marks);
        printf("Enter Maths marks : ");
        scanf("%f",&marks[i].maths_marks);
        printf("Enter Physics marks : ");
        scanf("%f",&marks[i].phy_marks);
        
        printf("\n");
    }
    
    for(i=0;i<5;i++) {
        printf("Student %d\n",i+1);
        float percentage = (marks[i].chem_marks + marks[i].maths_marks + marks[i].phy_marks)/3.0;
        printf("Percentage : %f\n", percentage);
    }
  return 0;
}