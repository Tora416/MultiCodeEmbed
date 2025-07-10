#include <stdio.h>
#include <stdlib.h>
FILE* F1;
FILE* F2;
void read(int A[], int n)
{
        int i;
        for(i=0;i<n;i++)
        {
                fscanf(F1,"%d", &A[i]);
        }
}
void display(int A[],int n)
{
        int i;
        for(i=0;i<n;i++)
        {
                fprintf(F2,"%d ",A[i]);
        }
        fprintf(F2,"\n");
}
int merge_sort(int A[],int p,int r)
{
        static int flips=0;
    int q = p + (r-p)/2;
    if((r-p+1)%2 == 0)
        q = q + 1;
    if(p<r)
    {

        for(int i=p;i<q;i++)
            for(int j=q;j<=r;j++)
            {
                if(A[j]<A[i])
                {
                    flips++;
                }
            }
        merge_sort(A,p,q-1);
        merge_sort(A,q,r);
    }
    return flips;
}
int inversion(int A[],int n)
{
        int r = n-1;
        int p=merge_sort(A,0,r);
        return p;
}

int main(int argc, char* argv[])
{
        F1 = fopen(argv[1],"r");
        F2 = fopen(argv[2],"w");
        char s;
        int num;
        int size;
        int* A;
        while(1)
        {
                fscanf(F1,"%c",&s);
                if(s=='r')
                {
                        fscanf(F1,"%d", &num);
                        size=num;
                        A=(int*)malloc(sizeof(int)*num);
                        read(A,num);
                }
                else if(s=='i')
                {
                        int p=inversion(A,size);
                        fprintf(F2,"%d\n",p);
                }
                else if(s=='d')
                {
                        fscanf(F1,"%d", &num);
                        display(A,num);
                }
                else if(s=='t')
                        break;
        }
    return 0;
}
                                                                                                                                   

