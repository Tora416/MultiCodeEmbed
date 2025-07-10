#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50

typedef struct Node* nptr;
typedef struct Node
{
    nptr llink;
    nptr rlink;
    char* ele;
}node;

nptr createNode()
{
    nptr temp=(nptr)malloc(sizeof(node));
    temp->ele=(char*)malloc(SIZE*sizeof(char));

    temp->llink=NULL;
    temp->rlink=NULL;

    return temp;
}

void insertf(nptr list,char* x)
{
    nptr temp=createNode();
    strcpy(temp->ele,x);

    if(!list->rlink)
    {
        list->rlink=temp;
        temp->llink=list;
        temp->rlink=NULL;

        return;
    }

    (list->rlink)->llink=temp;
    temp->llink=list;
    temp->rlink=list->rlink;
    list->rlink=temp;
}

char* delf(nptr list)
{
    if(!(list->rlink))
    {
        printf("Underflow!!\n"); 
        return NULL;
    }

    nptr temp=list->rlink;
    list->rlink=temp->rlink;

    if(temp->rlink)
        (temp->rlink)->llink=list;
    
    char* str=(char*)malloc(SIZE*sizeof(char));
    strcpy(str,temp->ele);
    free(temp);

    return str;
}

void rev(nptr list)
{
    nptr trv=list;

    while(trv->rlink)
        trv=trv->rlink;

    nptr last=trv;
    
    while(trv!=list)
    {
        nptr temp=trv->llink;
        trv->llink=trv->rlink;
        trv->rlink=temp;
        trv=temp;
    }
    
    (list->rlink)->rlink=NULL;
    list->rlink=last;
    last->llink=list;
}

void disp(nptr list)
{
    nptr i=list->rlink;
    
    while(i)
    {
        printf("%s  ",i->ele);
        i=i->rlink;
    }
    
    printf("\n");
}

int main()
{
    int n;
    printf("Enter no. of elemnts: ");
    scanf("%d", &n);
    
    char str[SIZE];
    nptr list=createNode();

    for(int i = 0 ; i < n ; i++)
    {
        printf("Enter word to insert: "); 
        scanf("%s", str);
        insertf(list, str);
    }

    disp(list);
    rev(list);
    disp(list);
}