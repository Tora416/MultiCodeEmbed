#include <stdio.h>
#include <stdlib.h>

typedef struct Node* nptr;
typedef struct Node
{
    nptr llink;
    nptr rlink;
    int ele;
}node;

nptr createNode(int x)
{
    nptr temp=(nptr)malloc(sizeof(node));
    temp->ele=x;
    temp->llink=NULL;
    temp->rlink=NULL;
    return temp;
}

void insertst(nptr* start,nptr* end,int x)
{
    nptr temp=createNode(x);

    if(!*start)
    {
        *start=temp;
        *end=temp;
    }
    else
    {
        temp->rlink=*start;
        (*start)->llink=temp;
        *start=temp;
    }
}

void inserten(nptr* start,nptr* end,int x)
{
    nptr temp=createNode(x);
    
    if(!*end)
    {
        *start=temp; *end=temp; 
        return;
    }
    else
    {
        (*end)->rlink=temp;
        temp->llink=*end;
        *end=temp;
    }
}

int delst(nptr* start,nptr* end)
{
    if(!*start)
    {
        printf("Underflow!!\n"); 
        return -99;
    }
    
    nptr temp; int x;
    temp=*start;
    x=temp->ele;
    
    if(!((*start)->rlink))
    {
        *end=*start=NULL;
        free(temp);
        return x;
    }
    
    *start=(*start)->rlink;
    (*start)->llink=NULL;

    free(temp);
    return x;
}

int delen(nptr* start,nptr* end)
{
    if(!*end)
    {
        printf("Underflow!!\n"); 
        return -99;
    }
    
    nptr temp; int x;
    temp=*end;
    x=temp->ele;
    
    if(!((*end)->llink))
    {
        *end=*start=NULL;
        free(temp);
        return x;
    }
    
    *end=(*end)->llink;
    (*end)->rlink=NULL;
    
    free(temp);
    return x;
}

void disp(nptr front)
{
    printf("NULL <--->");
    for(nptr i=front;i;i=i->rlink)
        printf(" %d <---> ",i->ele);
    
    printf("NULL \n");
}

int main()
{
    printf("1:Insert@start 2:Insert@end 3:Delete@start\n4:Delete@end 5:Display 6:Exit\n");
    int i=1,ch,ele;
    
    nptr start=NULL,end=NULL;
    
    while(i)
    {
        printf("Command: "); 
        scanf("%d",&ch);
        
        switch(ch)
        {
            case 1:
                    printf("Enter element to insert: ");
                    scanf("%d",&ele);
                    insertst(&start,&end,ele);
                    break;
            
            case 2:
                    printf("Enter element to insert: ");
                    scanf("%d",&ele);
                    inserten(&start,&end,ele);
                    break;
            
            case 3:
                    ele=delst(&start,&end);
                    if(ele!=-99) 
                        printf("Deleted %d\n",ele);
                    break;
            
            case 4:
                    ele=delen(&start,&end);
                    if(ele!=-99) 
                        printf("Deleted %d\n",ele);
                    break;
            
            case 5:
                    disp(start);
                    break;
            
            case 6:
                    i=0; break;
        }

    }
}