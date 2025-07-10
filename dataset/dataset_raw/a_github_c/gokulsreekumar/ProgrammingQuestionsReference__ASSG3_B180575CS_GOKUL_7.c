#include<stdio.h>
#include<stdlib.h>
struct stack{
    int top;
    int cap;
    int* A;
};

int StackOverflow(struct stack* stk)
{
    if(stk->top==stk->cap-1)
        return 1;
    else 
        return 0;
}
int StackEmpty(struct stack* stk)
{
    if(stk->top==-1)
        return 1;
    else
        return 0;
}
void push(struct stack* stk, int elem,FILE* fp2){
    if(StackOverflow(stk))
    {
        fprintf(fp2, "%d\n", 999);
        return;
    }
    stk->top++;
    stk->A[stk->top]=elem;
        
};
void pop(struct stack* stk,FILE* fp2){
    if(StackEmpty(stk))
    {
        fprintf(fp2, "%d\n", -1);
        return;
    }
    stk->top--;
    fprintf(fp2,"%d\n",stk->A[stk->top+1]);
};
void print(struct stack* stk,int n,FILE* fp2)
{
    int i;
    int top1=stk->top;
    if(StackEmpty(stk))
    {
        fprintf(fp2, "%d\n",-1);
        return;
    }
    if(n==0)
    {
        for(i=top1;i>=0;i--)
        {
            fprintf(fp2, "%d ",stk->A[i]);
        }
        fprintf(fp2, "\n");
    }
    else if(n>0)
    {
        if(n<=top1+1)
        {
            for(i=0;i<n;i++)
                {
                    fprintf(fp2, "%d ", stk->A[top1-i]);
                }
                        fprintf(fp2, "\n");
        }
        else if(n>top1+1)
        {
            for(i=top1;i>=0;i--)
            {
                fprintf(fp2, "%d ",stk->A[i]);
            }
            fprintf(fp2, "END\n");
        }   
    }
}
int main()
{
    int num;
    char sel;
    int n1; int capacity;

    FILE* fp1;
    FILE* fp2;
    fp1=fopen("input.txt","r");
    fp2=fopen("output.txt","w");

    fscanf(fp1,"%d",&capacity);
    
    struct stack* stk=(struct stack*)malloc(sizeof(struct stack));
    stk->cap=capacity;
    stk->top=-1;
    stk->A=(int*)malloc(sizeof(int)*capacity);


    while(1){
    fscanf(fp1,"%c",&sel);
    if(sel=='p')
    {
        fscanf(fp1,"%d",&n1);
        push(stk,n1,fp2);
    }
    else if(sel=='t')
    {
        pop(stk,fp2);
    }
    else if(sel=='d')
    {
        fscanf(fp1,"%d",&num);
        print(stk,num,fp2);
    }
    else if(sel=='s')
    {
        break;
    }
}
}
