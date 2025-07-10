
#include<stdio.h>
#include<stdlib.h>
struct Dir
{
    char file;
    struct Dir* next;
}*dir[5],*temp,*q;
int isthere(int d,char name)
{
    int flag=-1;
    temp=dir[d];
    while(temp!=NULL)
    {
        if(temp->file==name)
        {
            flag=1;
            break;
        }
        temp=temp->next;
    }
    return(flag);
}
void add_file(int d,char name)
{
    struct Dir* p=(struct Dir*)malloc(sizeof(struct Dir));
    p->file=name;
    p->next=NULL;
    if(isthere(d,name)==-1)
    {
        if(dir[d]==NULL)
            dir[d]=p;
        else
        {
            temp=dir[d];
            while(temp->next!=NULL)
                temp=temp->next;
            temp->next=p;
        }
    }   
    else
        printf("file already exists in that directory");
}
void rem_file(int d,char name)
{
    if(isthere(d,name)==-1)
        printf("file doesnot exist in the directory");
    else
    {
        temp=dir[d];
        q=temp;
        while(temp->next!=NULL)
        {
            if(temp->file==name)
            {
                if(temp==dir[d])
                {
                    dir[d]=dir[d]->next;
                    free(temp);
                    temp=dir[d];
                }
                else
                {
                    q->next=temp->next;
                    free(temp);
                    temp=q->next;
                }
            }
            q=temp;
            temp=temp->next;
        }
        if(temp->file==name)
        {
            q->next=NULL;
            free(temp);
        }
    }
}
void display()
{
    int i;
    for(i=0;i<5;i++)
    {
        temp=dir[i];
        printf("\nDirectory %d - ",i);
        while(temp!=NULL)
        {
            printf("%c\t",temp->file);
            temp=temp->next;
        }
    }
}
void main()
{
    int ch,dir;
    char name[5];
    while(1)
    {
        printf("\nEnter choice : ");
        scanf("%d",&ch);
        switch(ch)
        {
            case 1: 
            {
                printf("\nEnter directory : ");
                scanf("%d",&dir);
                printf("\nEnter file name : ");
                scanf("%s",name);
                add_file(dir,name[0]);
                break;
            }
            case 2: 
            {
                printf("\nEnter directory : ");
                scanf("%d",&dir);
                printf("\nEnter file name : ");
                scanf("%s",name);
                rem_file(dir,name[0]);
                break;
            }
            case 3:
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