#include <stdio.h>
#include <stdlib.h>
FILE *F1;
FILE *F2;

struct bucket
{
    int count;
    int* value;
};


void read(int A[],int n)
{
  int i;
  for(i=0;i<n;i++)
   fscanf(F1,"%d",&A[i]);
}
void display(int A[],int n)
{
  int i;
  for(i=0;i<n;i++)
  {
        fprintf(F2,"%d ",A[i]);
        if(i==(n-1))
        fprintf(F2,"\n");}
}
int findMax_digits(int a[],int n)
{
  int i,digits=0,num;
  int max=0;
  int level=1;
  for(i=1;i<n;i++)
   {
     if(a[i]>a[max])
       max=i;
   }
  num=a[max];
  if(num==0)
   return 0;
  while(num>=level)
   {
     digits++;
     level*=2;
   }
  return digits;
}
void form_binary(int a[],int n,int q,int bin[n][q])
{

  int i,j,num;
  for(i=0;i<n;i++)
   {
    num=a[i];
    j=q-1;
    while(num>0)
      {
           bin[i][j]=num%2;
           num/=2;
           j--;
      }
   }
}
void count_ones(int n,int q,int a[n][q],int one[])
{
int i,j;
  for(i=0;i<n;i++)
    for(j=0;j<q;j++)
        {if(a[i][j]==1)
         one[i]++;
        }
}

void insertionSort(int arr[], int n)
{
    int i, key, j;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
 }
void bucketSort(int A[],int n)
 {  int i,j,k,flag=0;
    int dig=0;
    dig=findMax_digits(A,n);
    int binarr[n][dig];
    for (i = 0; i < n; i++)
     for (j = 0; j < dig; j++)
      binarr[i][j]=0;
    form_binary(A,n,dig,binarr);
    int one[n];
    for (i = 0; i < n; i++)
     {one[i]=0;
      }
    count_ones(n,dig,binarr,one);
    int max=0;
    for(i=1;i<n;i++)
     {
       if(one[i]>one[max])
       max=i;
     }
    int bucket_nos;
     bucket_nos=one[max]+1;

    struct bucket buckets[bucket_nos];
    for (i = 0; i <= bucket_nos; i++)
    {
        buckets[i].count = 0;
        buckets[i].value = (int*)malloc(sizeof(int) * n);
    }

    for (i = 0; i < n; i++)
      buckets[one[i]].value[buckets[one[i]].count++] = A[i];
    for (k = 0, i = 0; i <= bucket_nos; i++)
    {
        if(buckets[i].count!=0)
          insertionSort(buckets[i].value,buckets[i].count);
        for (j = 0; j < buckets[i].count; j++)
                    A[k + j] = buckets[i].value[j];
        k+=buckets[i].count;
    }

        for(i=0;i<= bucket_nos;i++)
        {
                if(buckets[i].count!=0)
                display(buckets[i].value,buckets[i].count);

        }
}

int main(int argc,char *argv[])
  {     char ch;
        int n,x,p;
        int *arr;
        F1=fopen(argv[1],"r");
        F2=fopen(argv[2],"w");
        if(F1==NULL)
         printf("cant open file");
        else
          {
          while(1)
           {
             fscanf(F1,"%c",&ch);
             if(ch=='r')
             {
               fscanf(F1," %d",&n);
               arr= (int*) malloc(n* sizeof(int));
               read(arr,n);
             }
            else if(ch=='d')
             {
               fscanf(F1,"%d",&p);
               display(arr,n);
             }
             else if(ch=='s')
             {
              bucketSort(arr,n);
             }
             else if(ch=='t')
               break;
           }

         }
   fclose(F1);
   fclose(F2);

}
                       
