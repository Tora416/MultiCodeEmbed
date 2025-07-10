#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct Node{
    int data;
    struct Node* next;
};

typedef struct Node* node;

node createNode()
{
    node t=(node)malloc(sizeof(struct Node));
    if(t==NULL)
        {
            printf("Memory not allocated for node");
            exit(0);
        }
    t->next=NULL;
    return t;
}


void enqueue(struct Node** head_ref, int new_data) 
{ 
    struct Node* new_node = createNode();
    struct Node *last = *head_ref;
    new_node->data  = new_data; 

    if (*head_ref == NULL) 
    { 
       *head_ref = new_node; 
       return; 
    }   
    while (last->next != NULL) 
        last = last->next; 
    last->next = new_node; 
    return;     
}

int find_size(node head)
{
    node p;
    int n=0;
    p=head;
    while(p!=NULL)
    {
        n++;
        p=p->next;
    }
    return n;
}

void print(node head,int n,FILE *fp2)
{

  node temp=head;
  int count=0;
  node p=head;
  if(head==NULL)
    {
      fprintf(fp2,"-1\n");
      return;
    }
  int size=find_size(head);

  if(n==0 || n>size)
  {
    while(temp!=NULL)
   {
    fprintf(fp2,"%d",temp->data);
    temp=temp->next;
    if(temp==NULL)
    {
      if(n>size)
        fprintf(fp2," END");
      fprintf(fp2,"\n");
    }
    else
      fprintf(fp2," ");
   }
   return;
  }
  if(n>0 && n<=size)
   {
    while(count<n)
    {
      fprintf(fp2,"%d",p->data);
      p=p->next;
      count++;
      if(count==n)
        fprintf(fp2,"\n");
      else 
        fprintf(fp2," ");
    }   
   }
}


int dequeue(node* head)
{
  node p;
  int dequeued;
  if(*head==NULL)
      return -1;
  dequeued=(*head)->data;
  p=(*head)->next;
  free(*head);
  *head=p;
  return dequeued;
}

int main()
{
    FILE* fp1;
    FILE* fp2;
    fp1=fopen("input.txt","r");
    fp2=fopen("output.txt","w");
    node Q=NULL;
    char sel;
    int elem,num,temp=0;
    while(1)
    {
        fscanf(fp1,"%c",&sel);
        if(sel=='e')
        {
            fscanf(fp1,"%d",&elem);
            enqueue(&Q, elem);
        }
        else if(sel=='p')
        {
            fscanf(fp1,"%d",&num);
            print(Q,num,fp2);
        }
        else if(sel=='d')
        {
            temp=dequeue(&Q);
            fprintf(fp2,"%d\n",temp);
        }
        else if(sel=='s')
        {
            break;
        }
    }
    fclose(fp1);
    fclose(fp2);
}