
#include <stdio.h>
#include<stdlib.h>

struct stack{
    int size;
    int top;
    int *arr;
};

int isEmpty(struct stack*ptr){
    if(ptr->top== -1){
        printf("Stack is empty..\n");
        return 1;
    }
    else{
        return 0;
    }
    
}
int isFull(struct stack*ptr){
    if(ptr->top == ptr->size-1){
        printf("Stack is Full(overflow)..\n");
        return 1;
    }
    else{
        
        return 0;
    }
    
}

void push(struct stack*ptr, int val){
    if(isFull(ptr)){
        printf("Stack Overflow! Cannot push %d to the stack\n", val);
    }
    else{
        ptr->top++;
        ptr->arr[ptr->top]=val;
        
    }
}

int pop(struct stack*ptr){
    if(isEmpty(ptr)){
        printf("Stack Underflow! Cannot pop from the stack\n");
        return -1;
    }
    else{
        int val = ptr->arr[ptr->top];
        ptr->top--;
        return val;
        
        
    }
}

int peek(struct stack* sp, int i){
    int arrayInd = sp->top-i+1;
    if(arrayInd<0){
        printf("Not a valid position for stack\n");
        return -1;
        
    }
    else{
        return sp->arr[arrayInd];
    }
}

int main()
{
    struct stack *sp=(struct stack*)malloc(sizeof(struct stack));
    sp->size=10;
    sp->top= -1;
    sp->arr= (int *)malloc(sp->size* sizeof(int));
    
    
    printf("Before pushing, Full: %d\n", isFull(sp));
    printf("Before pushing, Empty: %d\n", isEmpty(sp));
    
    push(sp, 56);
    push(sp, 55);
    push(sp, 54);
    push(sp, 53);
    push(sp, 52);
    push(sp, 51);
    push(sp, 50);
    push(sp, 49);
    push(sp, 48);
    push(sp, 47); 
    push(sp, 46); 
    
    printf("After pushing, Full: %d\n", isFull(sp));
    printf("After pushing, Empty: %d\n", isEmpty(sp));
    
    
    printf("Popped %d from the stack\n", pop(sp));
     
    
    for(int j=1; j <= sp->top + 1; j++){
        printf("The value at position %d is %d\n",j,peek(sp, j));
    }

    return 0;
}