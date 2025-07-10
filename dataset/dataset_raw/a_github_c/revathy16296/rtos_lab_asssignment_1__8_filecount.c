#include<stdio.h>
#include<string.h>
#define FILE_SIZE 100
#define LINE 20
int read_lines(char s[FILE_SIZE]);
int main()
{
    FILE *f;
    char s[FILE_SIZE];
    printf("enter the source file path\n");
    scanf("%s",s);
    read_lines(s);
    return 0;
}

int read_lines(char s[FILE_SIZE])
{
    FILE *f;
    int words,lines;
    char ch;
    f=fopen(s,"r");
    if (f == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    }
    words = lines = 0;
    while ((ch = fgetc(f)) != EOF)
    {

        
        if (ch == '\n' || ch == '\0')
            lines++;

        
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0')
            words++;
    }
    printf("\tthe number of lines are :%d\n",lines);
    printf("\tthe number of words are :%d\n",words);    
    fclose(f);
    return 1;
}
    
    

    
    

