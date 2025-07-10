#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int data;
    struct node* next;
}*NODE;
NODE insert(NODE first,int e,int pr)
{
    NODE temp=(NODE)malloc(sizeof(struct node));
    temp->data=e;
    temp->next=NULL;
    if (first==NULL)
        return temp;
    else if(first->next==NULL)
    {
        if (first->data>e)
        {
            temp->next=first;
            return temp;
        }
        else if(first->data<e)
            first->next=temp;
        else
        {
            if (pr==1)
                printf("Input not unique\n");
            free(temp);
        }
    }
    else
    {
        NODE m=first;
        while(m->next!=NULL && m->next->data<=e)
            m=m->next;
        if (m->data!=e)
        {
            temp->next=m->next;
            m->next=temp;
        }
        else
        {
            if (pr==1)
                printf("Input not unique\n");
            free(temp);
        }
        return first;
    }
}
NODE lunion(NODE l1, NODE l2)
{
    NODE uni=NULL;
    while(l1!=NULL)
    {
        uni=insert(uni,l1->data,0);
        l1=l1->next;
    }
    while(l2!=NULL)
    {
        uni=insert(uni,l2->data,0);
        l2=l2->next;
    }
    return uni;
}
NODE lintersection(NODE l1, NODE l2)
{
    NODE in=NULL;
    while (l1!=NULL)
    {
        NODE pl2=l2;
        while(pl2!=NULL)
        {
            if (l1->data==pl2->data)
            {
                in=insert(in,l1->data,0);
                break;
            }
            pl2=pl2->next;
        }
        l1=l1->next;
    }
    return in;
}
void display(NODE first)
{
    if (first==NULL)
        printf("List Empty\n");
    else
    {
        NODE p=first;
        while (p->next!=NULL)
        {
            printf("%d ",p->data);
            p=p->next;
        }
        printf("%d\n",p->data);
    }
}
int main()
{
    NODE first=NULL;
    NODE second=NULL;
    NODE uni=NULL;
    NODE in=NULL;
    int z=0,k;
    while (z==0)
    {
        printf("1. Insert 1\t2. Insert 2\t3. Display 1\t4. Display 2\t5. Union\t6. Intersection\t7. Exit\t");
        scanf("%d",&k);
        switch(k)
        {
            case 1:
            {
                int i;
                printf("Insert:\t");
                scanf("%d",&i);
                first=insert(first,i,1);
                break;
            }
            case 2:
            {
                int i;
                printf("Insert:\t");
                scanf("%d",&i);
                second=insert(second,i,1);
                break;
            }
            case 3:
            {
                display(first);
                break;
            }
            case 4:
            {
                display(second);
                break;
            }
            case 5:
            {
                uni=lunion(first,second);
                display(uni);
                break;
            }
            case 6:
            {
                in=lintersection(first,second);
                display(in);
                break;
            }
            case 7:
                z=1;
        }
    }
    return 0;
}