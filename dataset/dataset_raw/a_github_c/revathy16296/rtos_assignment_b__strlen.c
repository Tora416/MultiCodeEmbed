#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

#define SIZE 30

void *count_vowels(void *string);

int main()
{
    
    char str[SIZE];
    printf("enter the string\n");
    int i,n=0;
    fgets(str,sizeof(str),stdin);
    for(i=1;str[i]!='\0';i++)
        {
        n++;
        }
    printf("the number of character in the string is %d\n",n);
    pthread_t thread;
    pthread_create(&thread,NULL,count_vowels,&str);
    pthread_join(thread,NULL);
    
    return 0;
}

void *count_vowels(void *string)

{
    char *b=(char *)string;
    int n,i,vowel=0;
    char ch;
    n=strlen(b);
    while(i<=n)
        {
            ch=b[i];
            if(ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u'||ch=='A'||ch=='E'||ch=='I'||ch=='O'||ch=='U')
            {vowel++;}
            i++;
        }
        printf("the number of vowels in the strings is  %d\n",vowel);
        return 0;
}