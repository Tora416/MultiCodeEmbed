#include <stdio.h>
#include <stdlib.h>
FILE *F1;
FILE *F2;
int* read(int n)
{
      int *arr;
      arr = (int*) malloc(n* sizeof(int));
      int i;
      for(i=0;i<n;i++)
       fscanf(F1,"%d",&arr[i]);
      return arr;
}
void display(int a[],int n)
{
  int i;
  for(i=0;i<n;i++)
  {fprintf(F2,"%d ",a[i]);
   if(i==(n-1))
    fprintf(F2,"\n");}
}
int search(int A[],int n,int k)
{
 int i;

 for(i=0;i<n;i++)
   if(A[i]==k)
     return i;
   return -1;
}
int main(int argc,char *argv[])
  {     char sel;
        int n,x,k;
        int *arr;
        F1=fopen(argv[1],"r");
        F2=fopen(argv[2],"w");
        if(F1==NULL)
         printf("Cant open file");
        else
          {
           while(1)
           {
             fscanf(F1,"%ch",&sel);
             if(sel=='r')
             {
               fscanf(F1," %d",&n);
               arr= read(n);
             }
            else if(sel=='d')
             {
               display(arr,n);
             }
             else if(sel=='s')
             {
              fscanf(F1,"%d",&k);
              x=search(arr,n,k);
              fprintf(F2,"%d\n",x);
             }
             else if(sel=='t')
               break;
           }

         }
   fclose(F1);
   fclose(F2);

  }
   






