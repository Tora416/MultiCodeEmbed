#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 125
#define NAME_SIZE 50
typedef struct student {
    int rollNo;
    char name[NAME_SIZE];
} studentType;
void dispStudents ( studentType students[], int n ) {
    int i;
    for (i=0; i<n; i++)
        printf("#%d Roll: %d | Name:%s\n",i+1, students[i].rollNo, students[i].name );
}
int enterStudents( studentType students[MAX] )
{
    int i;
    for (i = 0; i < MAX; i++)
    {
        scanf("%d",&students[i].rollNo);
        if(students[i].rollNo==0)
            break;
        scanf("%[^\n]s",students[i].name);
    }
    return i;
}

int main() {
    int n;
    studentType students[MAX]; 
    
    n = enterStudents( students );
    
    dispStudents( students, n );
    return 0;
}