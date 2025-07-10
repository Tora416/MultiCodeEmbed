
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define NAME_SIZE 50
typedef struct x{
    int rollNo;
    char name[50];
}StudentType;
int enterStudents(StudentType students[]){
    int c=0;
    while(1)
    {
        if(c>NAME_SIZE){
            printf("OVERFLOW");
            break;
        }
        scanf("%d",&students[c].rollNo);
        if(students[c].rollNo==0)
            break;
        scanf("%[^\n]s",students[c].name);
        c++;
    }
    if(c==0){
        printf("Empty list");
        exit(1);
    }
    return c;
}
void sortStudents(StudentType students[], int n ){
    StudentType t;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i;j++)
        {
            if(students[j].rollNo<students[j+1].rollNo)
            {
                t=students[j];
                students[j]=students[j+1];
                students[j+1]=t;
            }
        }
    }
}
void dispStudents ( StudentType students[], int n ) {
    int i;
    for (i=0; i<n; i++)
        printf("#%d Roll: %d | Name:%s\n",i+1, students[i].rollNo, students[i].name );
}

int main() {
    int n;
    StudentType students[MAX]; 
    
    n = enterStudents( students );    
    sortStudents( students, n );
    
    dispStudents( students, n );
    return 0;
}