#include<stdio.h>
#include<stdlib.h>

FILE* F1;
FILE* F2;

int flag =0;

int a[200];
int* read(int n)
{
        flag++;
        int i;
        int s = sizeof(int);
        int* arr1= (int*)malloc(s * n);
        for(i = 0; i<n; i++)
        {
                fscanf(F1, "%d", (arr1+i));
        }
        return arr1;

}



void display(int arr2[], int n)
{   
        int i;
        for(i = 0; i<n; i++)
        {
                fprintf(F2, "%d ", arr2[i]);
        }

}

float findMedian(int X[],int Y[],int m,int n)
{
    float median;
    int s = sizeof(int);
    
    int j=0; int k =0;
    int i=0;

    while(i<m+n)
    {
        if(j<m && k<n)
        {
            if(X[j]<=Y[k])
            {
                a[i] = X[j];
                j++;
            }
            else
            {
                a[i] = Y[k];
                k++;
            }
            i++;
        }
    
        else if(j == m)
        {
            a[i]=Y[k];
            k++;
            i++;
        }
        else if(k == n)
        {
            a[i]=X[j];
            j++;
            i++;
        }

    }

    if((m+n)%2 != 0)
    {
        median = a[(m+n)/2];
        return median;
    }
    else
    {
        median = (a[(m+n-1)/2]+a[(m+n-1)/2+1])/2.0;
        return median;
    }
}

int main(int argc, char* argv[])
{
    
        int num; char s;int size1, size2;
        int* arr1;
        int* arr2;
        F1 = fopen(argv[1], "r");
        F2 = fopen(argv[2], "w");
        while(1)
        {
        fscanf(F1 ,"%c %d",&s, &num);
        if(s == 'r')
        {
            if(flag%2==0)
            {
                size1 = num;
                arr1 = read(num);
            }
            else if(flag%2==1)
            {
                size2 = num;
                arr2 = read(num);
            }
        }
        else if(s == 'f')
        {
                float p = findMedian(arr1,arr2,size1,size2);
        if((size1+size2)%2 == 0)
        {
                fprintf(F2,"%0.2f\n", p);
        }
        else
            fprintf(F2, "%d\n", (int)p);
        }

        else if(s == 'd')
        {
        float med = findMedian(arr1, arr2, size1, size2);
                display(a, size1+size2);
                fprintf(F2, "\n");
        }
        else if(s == 't')
                return 0;
        }
        fclose(F1);
        fclose(F2);

}
