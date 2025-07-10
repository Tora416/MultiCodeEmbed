#include <stdio.h>
#include <stdlib.h>
FILE *F1;
FILE *F2;

void read(int A[],int n)
{
    int i;
    for(i=0;i<n;i++)
    fscanf(F1,"%d",&A[i]);
}

void checkSubset(int X[],int m,int Y[],int n)
{
    int i,j,flag=0;
    for(i=0;i<n;i++)
     {
         for(j=0;j<m;j++)
         {
             if(Y[i]==X[j])
              {
                  flag++;
                  break;
              }
         }  
     }
     if(flag==n)
       fprintf(F2,"true");
     else
       fprintf(F2,"false");
}
int main(int argc,char *argv[])
{
    char s;
    int m,n,x,p,k;
    int *X,*Y;
    int count=0;
    F1=fopen(argv[1],"r");
    F2=fopen(argv[2],"w");
    if(F1==NULL)
        printf("cant open file");
    else
        {
        while(1)
         {
            fscanf(F1,"%c",&s);
            if(s=='r')
                {
                    count++;
                    if(count%2!=0)
                     { 
                         fscanf(F1," %d",&m);
                         X = (int*) malloc(m* sizeof(int));
                         read(X,m);
                     }
                    else
                     {
                         fscanf(F1," %d",&n);
                         Y = (int*) malloc(n* sizeof(int));
                         read(Y,n);
                     }
                 }    
            else if(s=='c')
                 {        
                      checkSubset(X,m,Y,n);
                 }
            else if(s=='t')
                break;
            }

         }
    fclose(F1);
    fclose(F2);

}
