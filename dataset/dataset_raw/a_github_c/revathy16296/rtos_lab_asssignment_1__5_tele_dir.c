#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct tele
{
    char name[15],sir_name[15],number[15];
};
int main()
{
    FILE *fp;
    struct tele cust[50];
    struct tele temp;
    int choice,limit,beg=0,i,j,c,count=0;
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
                
                break;
            case 2:
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
                break;
            case 3:
                exit(0);
        }
    }
    return 0;
}
    

