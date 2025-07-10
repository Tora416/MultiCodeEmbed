
#include <stdio.h>

int main()
{
    int arr1[100], n,counter=0;
    int i, j, k;

       printf("Number of elements to be stored in the array :");
       scanf("%d",&n);

       printf("Input %d elements in the array :\n",n);
       for(i=0;i<n;i++)
            {
          printf("element - %d : ",i);
          scanf("%d",&arr1[i]);
        }

    printf("\nThe unique elements found in the array are : \n");
    for(i=0; i<n; i++)
    {
        counter=0;

        for(j=0; j<i-1; j++)
        {
            if(arr1[i]==arr1[j])
            {
                counter++;
            }
        }
       for(k=i+1; k<n; k++)
        {
            if(arr1[i]==arr1[k])
            {
                counter++;
            }
        }
       if(counter==0)
        {
          printf("%d ",arr1[i]);
        }
    }
}