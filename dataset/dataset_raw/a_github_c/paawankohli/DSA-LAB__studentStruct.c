#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    char name[20];
    int rollNum;
    float gpa;
} STUDENT;

void readData(STUDENT* s)
{
    printf("Enter name: ");
    scanf("%s", (s->name));

    printf("Enter roll number: ");
    scanf("%d", &(s->rollNum));

    printf("Enter GPA: ");
    scanf("%f", &(s->gpa));
}

void printData(STUDENT* s)
{
    printf("Name: %s \n", (s->name)); 
    printf("Roll number: %d \n", s->rollNum);
    printf("GPA: %f \n", s->gpa);
}

int main()
{

    int n;
    printf("Enter no. of students:");
    scanf("%d", &n);

    STUDENT* ptr = calloc(n, sizeof(STUDENT));

    for(int i = 0 ; i < n ; i++)
    {
        printf("\nEnter data of %dth student: \n", i + 1);
        readData(ptr + i);
    }

    
    for(int i = 0 ; i < n - 1 ; i++)
    {
        STUDENT temp;
        
        for(int j = 0 ; j < n - i - 1 ; j++)
            if( ptr[j].rollNum  > ptr[j+1].rollNum )
            {
                temp = ptr[j];
                ptr[j] = ptr[j+1];
                ptr[j+1] = temp;
            }
    }

    for(int i = 0 ; i < n ; i++)
    {
        printf("\nData of %dth student: \n", i + 1);
        printData(ptr + i);
    }

    free(ptr);
}