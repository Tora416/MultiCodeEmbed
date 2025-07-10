
#include<stdio.h>
#include<stdlib.h>
int pos;
struct graph
{
    char name;
    int id;
    char parent;
    struct graph* next;
}*G[10],*temp,*q;
void add_dir(char dir)
{
    int i,flag=-1;
    char root[10];
    struct graph* p=(struct graph*)malloc(sizeof(struct graph));
    p->name=dir;
    p->id=1;
    printf("\nEnter root directory : ");
    scanf("%s",root);
    p->parent=root[0];
    p->next=NULL;
    if(root[0]=='!')
    {
        G[pos]=p;
        pos=pos+1;
    }
    else
    {
        for(i=0;i<pos;i++)
        {
            temp=G[i];
            q=temp->next;
            while(temp!=NULL)
            {
                if(temp->name==root[0])
                {
                    p->next=temp->next;
                    temp->next=p;
                    flag=1;
                    break;
                }
                else
                {
                    temp=temp->next;
                    q=temp->next;
                }
            }
            if(flag==1)
                break;
        }
    }
}
void add_file(char dir,char file)
{
    int i,flag=-1;
    struct graph* p=(struct graph*)malloc(sizeof(struct graph));
    p->name=file;
    p->id=2;
    p->parent=dir;
    p->next=NULL;
    for(i=0;i<pos;i++)
    {
        temp=G[i];
        q=temp->next;
        while(temp!=NULL)
        {
            if(temp->name==dir && temp->id==1)
            {
                p->next=temp->next;
                temp->next=p;
                flag=1;
                break;
            }
            else
            {
                q=temp;
                temp=temp->next;
            }
        }
        if(flag==1)
            break;
    }
}
void del_dir(char dir)
{
    int i;
    for(i=0;i<pos;i++)
    {
        temp=G[i];
        if(temp->name==dir)
        {
            temp->next=NULL;
            free(temp);
            break;
        }
        else
        {
            q=temp;
            while(temp!=NULL)
            {
                if(temp->name==dir && temp->id==1)
                {
                    q->next=temp->next;
                    
                    temp=q->next;
                    continue;
                }
                else if(temp->parent==dir && temp->id==2)
                {
                    q->next=temp->next;
                    
                    temp=q->next;
                    continue;   
                }
                q=temp;
                temp=temp->next;
            }
            
        }
    }
}
void del_file(char dir,char file)
{
    int i,flag=-1;
    for(i=0;i<pos;i++)
    {
        temp=G[i];
        q=temp;
        while(temp!=NULL)
        {
            if(temp->name==file && temp->id==2 && temp->parent==dir)
            {
                q->next=temp->next;
                temp=q->next;
                flag=1;
                break;
            }
            q=temp;
            temp=temp->next;
        }
        if(flag==1)
            break;
    }
}
void display()
{
    int i;
    for(i=0;i<pos;i++)
    {
        temp=G[i];
        printf("\nDirectory (%c) : ",temp->name);
        while(temp!=NULL)
        {
            printf("(%c,%d,%c)",temp->name,temp->id,temp->parent);
            temp=temp->next;
        }
    }
}
int check(char dir)
{
    int flag=-1;
    int i;
    for(i=0;i<pos;i++)
    {
        temp=G[i];
        while(temp!=NULL)
        {
            if(temp->name==dir && temp->id==1)
            {
                flag=1;
                break;
            }
            else
            {
                temp=temp->next;
            }
        }
        if(flag==1)
            break;
    }
    return(flag);
}
void main()
{
    int status=-1,ch;
    char dir[10],file[10];
    while(1)
    {
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1:
            {
                printf("\nEnter the name of directory : ");
                scanf("%s",dir);
                add_dir(dir[0]);
                break;
            }
            case 2:
            {
                printf("\nEnter the name of file to add : ");
                scanf("%s",file);
                printf("\nEnter the directory : ");
                scanf("%s",dir);
                status=check(dir[0]);
                if(status==1)
                    add_file(dir[0],file[0]);
                else
                {
                    add_dir(dir[0]);
                    add_file(dir[0],file[0]);
                }
                break;
            }
            case 3:
            {
                printf("\nEnter the directory to delete : ");
                scanf("%s",dir);
                del_dir(dir[0]);
                break;
            }
            case 4:
            {
                printf("\nEnter the file to delete : ");
                scanf("%s",file);
                printf("\nEnter the directory to which it belongs : ");
                scanf("%s",dir);
                del_file(dir[0],file[0]);
                break;
            }
            case 5:
            {
                display();
                break;
            }
            default:
            {
                exit(0);
                break;
            }
        }
    }
}