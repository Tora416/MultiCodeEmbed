#include <stdio.h>
#include <stdlib.h>
#include <math.h>
struct Queue
{
    int rear,front;
    int size;
    int *arr;
};

typedef struct Queue queue;

int isFull(queue Q)
{
    if( (Q.front == Q.rear + 1) || (Q.front == 0 && Q.rear == Q.size-1))
        return 1;
    return 0;
}
int isEmpty(queue Q)
{
    if(Q.front == -1)
        return 1;
    return 0;
}
int enqueue(queue *Qref,int element)
{
    if(isFull(*Qref))
        return -999;
    else
    {
        if((*Qref).front == -1)
            (*Qref).front = 0;
        (*Qref).rear = ((*Qref).rear + 1) % (*Qref).size;
        (*Qref).arr[(*Qref).rear] = element;
    }
    return 0;
}
int dequeue(queue *Qref)
{
    int element;
    if(isEmpty(*Qref))
        return(-1);
    else
      {
        element = (*Qref).arr[(*Qref).front];
        if ((*Qref).front == (*Qref).rear)
        {
            (*Qref).front = -1;
            (*Qref).rear = -1;
        } 
        else
            (*Qref).front = ((*Qref).front + 1) % (*Qref).size;
        return(element);
      }
}

int length(queue Q)
{
    int l;
    if (Q.front == -1)
       return 0;
    if (Q.rear >= Q.front)
        l=Q.rear-Q.front+1;
    else
        l=Q.size-Q.front+2+Q.rear;
    return l;
}

void print(queue Q,int n,FILE *fp2)
{
    int i,l,c=0;
    l=length(Q);
    if (Q.front == -1)
    {
        fprintf(fp2,"-1\n");
        return;
    }
    if(n>0 || n==0)
     {
        if(n==0)
          n=l;
        if (Q.rear >= Q.front)
         {
          for (i = Q.front; i <= Q.rear; i++)
            {
                if(c<n)
                 fprintf(fp2,"%d",Q.arr[i]);
                if(i!=Q.rear)
                 fprintf(fp2," ");
                 c++;  
              }
             if(c<n)
              fprintf(fp2," END\n");
             else
              fprintf(fp2,"\n");
          }
     
       
        else
        {
          for (i = Q.front; i < Q.size; i++)
            {
                if(c<n)
                 fprintf(fp2,"%d ", Q.arr[i]);
                c++;
            }      
          for (i = 0; i <= Q.rear; i++)
            {  
                if(c<=n)
                 fprintf(fp2,"%d", Q.arr[i]);
                c++;
                if(i!=Q.rear)
                 fprintf(fp2," ");
            }
            if(c<n)
              fprintf(fp2," END\n");
            else
              fprintf(fp2,"\n");
         }
 
    }
}

int main()
{
    char sel;
    int p,q,n,element;
    FILE *fp1;
    FILE *fp2;
    fp1=fopen("input.txt","r");
    fp2=fopen("output.txt","w");
    queue Q;
    Q.rear=-1;
    Q.front=-1;

    fscanf(fp1,"%d",&(Q.size));
    Q.arr=(int*)malloc(sizeof(int)*(Q.size));
    while(1)
         {
            fscanf(fp1,"%c",&sel);
              if(sel=='e')
                {
                    fscanf(fp1,"%d",&element);
                    p=enqueue(&Q,element);

                    if(p==-999)
                      fprintf(fp2,"%d\n",p);
                }  
            else if(sel=='p')
                 {
                    fscanf(fp1,"%d",&n);
                    print(Q,n,fp2);
                 }
            else if(sel=='d')
                {
                    q=dequeue(&Q);
                    fprintf(fp2,"%d\n",q);
                }
            else if(sel=='s')
                break;
         }

  fclose(fp1);
  fclose(fp2);
  return 0;
}
