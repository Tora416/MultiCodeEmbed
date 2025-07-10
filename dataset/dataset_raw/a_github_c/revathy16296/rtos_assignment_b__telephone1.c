#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include<unistd.h>
#include<string.h>


void *display_dir(void *para);
void *add_element(void *para);

struct tele
{
    char name[15],sir_name[15],number[15];
};

int choice,limit,beg,i,j,c,count=0;
struct tele cust[10];

int main()
{
    pthread_t thread2,thread1;
    beg=0;
    while(1)
    {
        printf("\ntelephone directory\n");
        printf("1.add\n");
        printf("2.display\n");
        printf("3.exit\n");
        printf("enter your choice\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
            pthread_create(&thread1,NULL,add_element,NULL);
            pthread_join(thread1,NULL);
                break;
            case 2:
            
            pthread_create(&thread2,NULL,display_dir,NULL);
            pthread_join(thread2,NULL);
            break;
            case 3:
                exit(0);
        }
    }
    return 0;
}

void *display_dir(void *para)
{
    
    printf("entered in to the thread2  process!\n");
    FILE *fp;
    printf("\ncustomer details\n");
    fp=fopen("details.txt","r");
    if(fp==NULL)
    {
        printf("error!");
        exit(1);
    }
                
    for (i=0;i<beg;i++)
    {
        fread(&cust,sizeof(struct tele),1,fp);
        printf("(%d) %s %s\t :%s\n",i+1,cust[i].name,cust[i].sir_name,cust[i].number);
    }
        fclose(fp);
}
void *add_element(void *para)
{
    FILE *fp;
    struct tele temp;
    fp=fopen("details.txt","w+");
                printf("enter the number of customers\n");
                scanf("%d",&limit);
                for(i=beg;i<limit+beg;i++)
                {
                    printf("enter the name of customer no %d:\t",i+1);
                    scanf("%s",cust[i].name);
                    printf("enter the sir name:\t");
                    scanf("%s",cust[i].sir_name);
                    printf("enter the phone number\t");
                    scanf("%s",cust[i].number);
                }
                beg=limit+beg;
                for(i=0;i<beg;i++)
                {
                    for(j=0;j<beg-1;j++)
                    {
                        c=strcmp(cust[j].name,cust[j+1].name);
                        if(c>0)
                        {
                            temp=cust[j];
                            cust[j]=cust[j+1];
                            cust[j+1]=temp;
                    }}
                }
                fclose(fp);
}