#include<stdio.h>
#include<stdlib.h>
FILE* F1;
FILE* F2;
int* read(int n)
{
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


int binary_search(int a[], int str, int end, int k)
{
    int mid = (end+str)/2;
    while(str<=end)
    {
        mid = (end+str)/2;
        if(a[mid] == k)
            return mid;
        else if(a[mid]>k)
        {
            end = mid-1;
        }
        else if(a[mid]<k)
        {
            str = mid+1;
        }
    }
    return -1;

}

int binary_search_rev(int a[], int str, int end, int k)
{
        int mid = (end+str)/2;
        while(str<=end)
        {
                mid = (end+str)/2;
                if(a[mid] == k)
                        return mid;
                else if(a[mid]>k)
                {
                        str = mid+1;
                }
                else if(a[mid]<k)
                {
                        end = mid-1;
                }
        }
        return -1;

}
int binary_bitonic(int arr[],int str, int end ) 
{ 
    int mid; 
      
    mid = (str + end) / 2; 
    if(arr[mid] > arr[mid-1] && arr[mid] > arr[mid + 1]) 
    { 
        return mid; 
    } 
      
    else if(arr[mid] > arr[mid - 1] && arr[mid] < arr[mid + 1]) 
    { 
        binary_bitonic(arr, mid , end); 
    } 
  
    else if(arr[mid] < arr[mid - 1] && arr[mid] > arr[mid + 1]) 
    { 
        binary_bitonic(arr, str, mid); 
    } 
} 

int search(int a[], int k, int size)
{
    
    int str = 0; 
    int end = size - 1;
    int b = binary_bitonic(a, str, end);
    
    int bs = binary_search(a, 0, b, k);
    if(bs!=-1)
    {
        printf("search succesful : normal\n");  
        return bs;
    }
    else if (bs == -1)
    {
        int rbs = binary_search_rev(a, b, end, k);
            return rbs;
    }
}

int main(int argc, char* argv[])
{
    int num; char s;int size;
        int* arr;
        F1 = fopen(argv[1], "r");
        F2 = fopen(argv[2], "w");
        while(1)
        {
        fscanf(F1 ,"%c %d",&s, &num);
        if(s == 'r')
        {
                size = num;
                arr = read(num);

        }
        else if(s == 's')
        {
                int p = search(arr, num, size);
                fprintf(F2,"%d\n", p);
        }

        else if(s == 'd')
        {
                display(arr, size);
                fprintf(F2, "\n");
        }
        else if(s == 't')
                return 0;
        }
    fclose(F1);
    fclose(F2);
}
