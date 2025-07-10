#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
struct stack{
        int stk[50];
        int top;
        };

int evaluatepostfix(int a,int b, char c,FILE* F2)
{
int res=1;
if(c=='+')
    return a+b;
if(c=='-')
        return b-a;
if(c=='*')
        return a*b;
if(c=='/')
        return b/a;
if(c=='^')
{
for(int i=1;i<=a;i++)
{
res*=b;
}
return res;
}
printf("invalid operator");
fprintf(F2,"-999");
exit(0);
}
int pop(struct stack* A)
{
int q;
q=A->stk[A->top];
return q;
}

struct stack* push(struct stack* A,int elt)
{

                A->top=A->top+1;
                A->stk[A->top]=elt;
        return A;
}

int main()
{       FILE* F1;
        FILE *F2;
        F1 = fopen("input.txt","r");
        F2 = fopen("output.txt","w");
        if(F1 == NULL)
        {
                printf("input file not found");
                exit(0);
        }


          int flag=-1;;
      char a,check;
      char c;
          int p,size,elt,q,t1,t2,res;
          struct stack AA;
          struct stack *A=&AA;
          A->top=-1;
      
        while(1)
        {
                fscanf(F1,"%c",&a);
               if(a=='e' || a=='s');
                else
               {
                        printf("invalid char input ");
                        fprintf(F2,"-999");
                        exit(0);
                }
                if(a=='e')
                {  
                fscanf(F1," ");
        while(1)
        {
        fscanf(F1,"%c",&check);
        if(check=='e' || check =='s' || check=='\n')
        {    fseek(F1,-1,1);
            break;}
        else
            fseek(F1,-1,1);
        

        t2=ftell(F1);
        if(fscanf(F1,"%d",&elt));
        else
        {
        flag=1;  
        
        t1=ftell(F1);
        if(t1!=t2)
        {
        fseek(F1,-1,1);
        }
        fscanf(F1,"%c",&c);
        }
    
    
        if(flag==-1)
        {
        A=push(A,elt);
        }

        if(flag==1)
        {   int e1=pop(A);
            A->top=A->top-1;
            int e2=pop(A);
             A->top=A->top-1;
            res=evaluatepostfix(e1,e2,c,F2);
            A=push(A,res);
        }
        flag=-1;
        fscanf(F1," ");
        }
        fprintf(F2,"%d\n",A->stk[A->top]);
        A->top=-1;
        } 
                if(a=='s')
                        exit(0);
                fscanf(F1,"\n");
        }
        return 0;
}





