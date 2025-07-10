
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct q{
    int coeff;
    int pow;
    struct q* next;
}node;
void createNode(int c, int p, node** exp)
{
    if(c==0)
        return;
    node* x=*exp;
    while(x)
    {
        if(x->pow == p)
        {
            if(x->coeff < 0 && c < 0)
                x->coeff=-(x->coeff+c);
            else
                x->coeff=x->coeff+c;
            return;
        }
        x=x->next;
    }
    node* ret=(node*) malloc(sizeof(node));
    ret->coeff=c;
    ret->pow=p;
    if(*exp==NULL)
    {
        ret->next=*exp;
        *exp=ret;
    }
    else
    {
            if(p > (*exp)->pow)
            {
                ret->next=*exp;
                *exp=ret;
            }
            else
            {
                x=*exp;
                while(x->next!=NULL && x->next->pow > p)
                    x=x->next;
                ret->next=x->next;
                x->next=ret;
            }
    }
}
node* poly_add_sub(char task, node* exp1, node* exp2)
{
    node* res=NULL;
    while(exp1 || exp2)
    {
        if(!exp2)
        {
            createNode(exp1->coeff,exp1->pow,&res);
            exp1=exp1->next;
        }
        else if(!exp1)
        {
            if(task=='+')
                createNode(exp2->coeff,exp2->pow,&res);
            else
            createNode(-(exp2->coeff),exp2->pow,&res);
            exp2=exp2->next;
        }
        else if(exp1->pow > exp2->pow)
        {
            createNode(exp1->coeff,exp1->pow,&res);
            exp1=exp1->next;
        }
        else if(exp1->pow < exp2->pow)
        {
            if(task=='+')
                createNode(exp2->coeff,exp2->pow,&res);
            else
                createNode(-(exp2->coeff),exp2->pow,&res);
            exp2=exp2->next;
        }
        else if(exp1->pow == exp2->pow )
        {
            if(task=='+' && (exp1->coeff + exp2->coeff)!=0)
                createNode(exp1->coeff+exp2->coeff,exp1->pow,&res);
            else if(task=='-' && (exp1->coeff - exp2->coeff)!=0)
                createNode(exp1->coeff-exp2->coeff,exp1->pow,&res);
            exp1=exp1->next;
            exp2=exp2->next;
        }
    }
    return res;
}
node* poly_mul(node* exp1, node* exp2)
{
    node* res=NULL;
    node* t=exp2;
    while(exp1)
    {
        while(t)
        {
            createNode(exp1->coeff * t->coeff,exp1->pow + t->pow,&res);
            t=t->next;
        }
        t=exp2;
        exp1=exp1->next;
    }
    return res;
}
void display(node* res)
{
    int f=0;
    while(res)
    {
        if(res->coeff>0)
        {
            if(f==0)
                printf(" %dx^%d ",res->coeff,res->pow);
            else
                printf("+ %dx^%d ",res->coeff,res->pow);
        }
        else if(res->coeff<0)
            printf("- %dx^%d ",-res->coeff,res->pow);
        f=1;
        res=res->next;
    }
}
int main()
{
    {
        node* exp1=NULL; node* exp2=NULL;
        char fexp[51],sexp[51];
        printf("Input in this format \" +/- ax^y +/- ... +/- ... \"\n");
        printf("Enter 1st Exp. = ");
        gets(fexp);
        printf("Enter 2nd Exp. = ");
        gets(sexp);
        if(strlen(fexp)==0 && strlen(sexp)==0)
        {
            printf("No expression found.\n");
            exit(1);
        }
        else if(strlen(fexp)>=51 || strlen(sexp)>=51)
        {
            printf("Expressions too lengthy.\n");
            exit(1);
        }
        else if(strlen(fexp)!=0 && strlen(sexp)==0)
            printf(" %s\n",fexp);
        else if(strlen(fexp)==0 && strlen(sexp)!=0)
            printf(" %s\n",sexp);
        else
        {
            {
                if(fexp[0]!='-'){
                    for(int i=50; i>0; i--) fexp[i]=fexp[i-1];
                    fexp[0]='+';
                }
                int t=0,c1=0,c2=0;
                char a[10],b[10];
                for(int i=0; i<=strlen(fexp); i++)
                {
                    if(fexp[i]==' ')
                        continue;
                    else if(t==0)
                    {
                        if(fexp[i]=='x'){
                            t=1;
                            i++;
                            if(fexp[i+1]=='-' && fexp[i+2]!=' ')
                            {
                                i++;
                                b[c2++]=fexp[i];
                            }
                        }
                        else
                            a[c1++]=fexp[i];
                    }
                    else if(fexp[i]=='+' || fexp[i]=='-' || fexp[i]=='\0')
                        {
                            t=0;
                            if(atoi(a)!=0)
                                createNode(atoi(a),atoi(b),&exp1);
                            if(fexp[i]!='\0')
                            {
                                for (int j = 0; j < 10; j++)
                                    a[j]=b[j]='\0';
                                c1=c2=0;
                                a[c1++]=fexp[i];
                            }
                        }
                    else if(t==1)
                            b[c2++]=fexp[i];
                }
            }
            {
                if(sexp[0]!='-'){
                    for(int i=50; i>0; i--) sexp[i]=sexp[i-1];
                    sexp[0]='+';
                }
                int t=0,c1=0,c2=0;
                char a[10],b[10];
                for(int i=0; i<=strlen(sexp); i++)
                {
                    if(sexp[i]==' ')
                        continue;
                    else if(t==0)
                    {
                        if(sexp[i]=='x'){
                            t=1;
                            i++;
                            if(sexp[i+1]=='-')
                            {
                                i++;
                                b[c2++]=sexp[i];
                            }
                        }
                        else
                            a[c1++]=sexp[i];
                    }
                    else if(t==1)
                    {
                        if(sexp[i]=='+' || sexp[i]=='-' || sexp[i]=='\0')
                        {
                            t=0;
                            if(atoi(a)!=0)
                                createNode(atoi(a),atoi(b),&exp2);
                            if(sexp[i]!='\0')
                            {
                                for (int j = 0; j < 10; j++)
                                    a[j]=b[j]='\0';
                                c1=c2=0;
                                a[c1++]=sexp[i];
                            }
                        }
                        else
                            b[c2++]=sexp[i];
                    }
                }
            }
            while(1)
            {
                int ch;
                printf("\n\n1. ADDITION\n");
                printf("2. SUBTRACTION\n");
                printf("3. MULTIPLICATION\n");
                printf("4. PRINT EXPRESSIONS\n");
                printf("5. EXIT PROGRAM\n");
                printf("What operation do you want to perform: ");
                scanf("%d",&ch);
                if(ch==5)
                {
                    printf("Exitting Program, Thank You.\n");
                    break;
                }
                switch (ch)
                {
                case 1:
                    printf("\n");
                    display(poly_add_sub('+',exp1,exp2));
                    break;
                case 2:
                    printf("\n");
                    display(poly_add_sub('-',exp1,exp2));
                    break;
                case 3:
                    printf("\n");
                    display(poly_mul(exp1,exp2));
                    break;
                case 4:
                    printf("\nExpression 1: ");
                    display(exp1);
                    printf("\nExpression 2: ");
                    display(exp2);
                    break;
                default:
                    printf("Invalid choice!\n");
                    break;
                }
            }
        }
    }
    return 0;
}