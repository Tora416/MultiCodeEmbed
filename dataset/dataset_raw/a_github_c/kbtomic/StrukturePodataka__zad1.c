#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>

typedef struct {
    char ime[10];
    char prezime[10];
    double bodovi;
}student;
int upis(FILE* fp, student* s, int n);
int main()
{
    int n = 0;
    FILE* fp = NULL;
    fp = fopen("studenti.txt", "r");
    if (fp == NULL)
    {   
        printf("Datoteka nije pronadena!\n");
        return 1;
    }
    while (!feof(fp))
    {
        if (fgetc(fp) == '\n')
            n++;
    }
    
    student* stud = NULL;
    stud = (student*)malloc(n * sizeof(student));
    if (stud == NULL)
    {
        printf("Neuspjesna alokacija memorije!\n");
    }
    rewind(fp);
    upis(fp, stud, n);
    fclose(fp);
    return 0;
}
int upis(FILE* fp, student* s, int n)
{
    int i, max = 100;
    double r;
    for (i = 0; i < n; i++)
    {
        fscanf(fp, "%s %s %lf\n", (*(s + i)).ime, (*(s + i)).prezime, &(*(s + i)).bodovi);
        r = s[i].bodovi / max * 100;
        printf("Ime i prezime: %s \t%s\t Bodovi: %.2lf\t  Relativni bodovi: %.2lf\n", (*(s + i)).ime, (*(s + i)).prezime, (*(s + i)).bodovi, r);
    }
    return 0;
}