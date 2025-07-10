#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include<string.h>

#define FILE_SIZE 100

void *read_lines(void *para);
void *read_char(void *para);
char s[FILE_SIZE];
int main()
{
    pthread_t thread1,thread2;
    printf("enter the source file path\n");
    scanf("%s",s);
    pthread_create(&thread1,NULL,read_char,NULL);
    pthread_join(thread1,NULL);
    pthread_create(&thread1,NULL,read_lines,NULL);
    pthread_join(thread1,NULL);
    
    return 0;
}

void *read_char(void *para)
{
    FILE *f;
    int character=0;
    char ch;
    f=fopen(s,"r");
    if (f == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    }
    while ((ch = fgetc(f)) != EOF)
    {
        if (ch != ' ' || ch != '\t' || ch != '\n' || ch != '\0'|| ch!='.')
        character++;
    }
    printf("the character count is %d\n",character);
    fclose(f);
    pthread_exit(NULL);
}



void *read_lines(void *para)
{
    FILE *f;
    int words;
    char ch;
    f=fopen(s,"r");
    if (f == NULL) 
    { 
        printf("Could not open file"); 
        return 0; 
    }
    words = 0;
    while ((ch = fgetc(f)) != EOF)
    {
        
        if (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\0'|| ch=='.')
            words++;
    }
    printf("the number of words are :%d\n",words);  
    fclose(f);
}
    