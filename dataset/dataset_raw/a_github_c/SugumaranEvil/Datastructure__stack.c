

         




#include "stack.h"

#define MAXSIZE 5

int push(void);
int pop(void);
int display(void);

struct stack
{
    int stack[MAXSIZE];
    int data;
}stack;

int main(){

    int input;

    stack.data = -1;

    while(1){
    printf("Enter the choice\n1.Push\n2.Pop\n3.Display\n4.Exit\n");
    scanf("%d",&input);

        switch(input){
            case 1 :
                push();
                break ;
            case 2 :
                pop();
                break ;
            case 3 :
                display();
                break ;
            case 4 :
                exit(EXIT_SUCCESS);
            default :
                printf("Invalid Option\n");
        }
    }
}


int push(void)
{
    int data_input;

    if(stack.data == (MAXSIZE - 1)){
        printf("..........Stack is full...........\n");
        return 0;
    }else{
        printf("Enter the Data to push\n");
        scanf("%d",&data_input);
        stack.data = stack.data + 1;
        stack.stack[stack.data] = data_input;
    }

}

int pop(void)
{
    int data_input;
    if(stack.data == -1){
        printf("...............Stack is empty.............\n");
        return 0;
    }else{
        data_input = stack.stack[stack.data];
        printf("Deleted Data = %d\n",stack.stack[stack.data]);
        stack.data = stack.data - 1;
    }

}
int display(void)
{
    int count;
    if(stack.data == -1){
        printf("Stack is empty\n");
        return 0;
    }else{
        printf("The status of stack\n");
        for(count = stack.data; count>=0; count--)
        {
            printf("%d\n",stack.stack[count]);
        }
    }
}
