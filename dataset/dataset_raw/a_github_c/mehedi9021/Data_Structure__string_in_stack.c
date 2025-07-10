#include <stdio.h>
#include <string.h>

#define MAXSIZE 100
struct Stack {
    int top;
    int array[MAXSIZE];
} string;

int isFull() {
    if(string.top >= MAXSIZE)
        return 1;
    else
        return 0;
}
int isEmpty() {
 if(string.top == -1)
     return 1;
 else
     return 0;
}
void push(int num) {
    if (isFull())
        printf("Stack is Full...\n");
    else {
        string.array[string.top + 1] = num;
        string.top++;
    }
}


int main() {
    char inputString[100], c;
    int i, length;
    
    printf("Enter a string\n");
    gets(inputString);
    printf("\n\n");
    puts(inputString);
    length = strlen(inputString);
    
            return 0;


    printf("");
    return 0;
}

