#include <stdio.h>
#include <string.h>
#define MAX 20

struct NAME {
    char fname[MAX];
    char mname[MAX];
    char lname[MAX];
};

struct DOB {
    int DD;
    int MM;
    int YYYY;
};

struct student {
    struct NAME name;
    int roll;
    struct DOB dob;
};

int main(void) {
    struct student stud[3];
   
    for (int i = 0; i < 3; i++) {
        printf("\nEnter First name - middle name - last name: ");
        scanf("%s %s %s", stud[i].name.fname, 
                stud[i].name.mname,
                stud[i].name.lname);

        printf("\nEnter Roll no.: ");
        scanf("%d", &stud[i].roll);

        printf("\nEnter DOB in form DD - MM - YY: ");
        scanf("%d %d %d", &stud[i].dob.DD, &stud[i].dob.MM, &stud[i].dob.YYYY);        
    }

    for (int i = 0; i < 3; i++) {
        printf("NAME = %s %s %s\n", 
                (stud+i)->name.fname, 
                (stud+i)->name.mname, 
                (stud+i)->name.lname);
        printf("ROLL = %d\n",(stud+i)->roll);
        printf("DOB  = %2d/%2d/%4d\n",
                ((stud+i)->dob).DD, 
                ((stud+i)->dob).MM, 
                ((stud+i)->dob).YYYY);
        printf("\n");
    }
    
    return 0;
}
