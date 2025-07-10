
#include<stdio.h>

char arr[256];


char* LastLetters(char *str){

    while(*str != '\0'){
        str++;
    }

    arr[0] = *(--str);

    arr[1] = ' ';

    arr[2] = *(--str);

    arr[3] = '\0';

    return arr;
}

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);
    setvbuf(stderr , NULL , _IONBF , 0);

    char str[256];

    printf("Enter a string: ");
    gets(str);

    printf("Reversed string: %s",LastLetters(str));

    return 0;
}
