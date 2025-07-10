
#include <stdio.h>
int main()
{
    int arr1[100], arr2[100], arr3[200];
    int n1, n2, n3;
    int i, k;
       printf("number of elements to be stored in the first array :");
       scanf("%d",&n1);

       printf("Input %d elements in the array :\n",n1);
       for(i=0;i<n1;i++)
            {
          printf("element - %d : ",i);
          scanf("%d",&arr1[i]);
        }
       printf("Input the number of elements to be stored in the second array :");
       scanf("%d",&n2);

       printf("Input %d elements in the array :\n",n2);
       for(i=0;i<n2;i++)
            {
          printf("element - %d : ",i);
          scanf("%d",&arr2[i]);
        }
    n3 = n1 + n2;
    for(i=0;i<n1; i++)
        {
            arr3[i] = arr1[i];
        }
       int j = 0 ;
     while(j<n2)
        {
            arr3[i] = arr2[j];
            i++;
            j++;
        }
   for(i=0;i<n3; i++)
        {
           for(k=0;k<n3-1;k++)
             {

                if(arr3[k]<=arr3[k+1])
                 {
                     
                   j=arr3[k+1];
                   arr3[k+1]=arr3[k];
                   arr3[k]=j;
                 }
              }
         }

     printf("\nThe merged array in decending order is :\n");
    for(i=0; i<n3; i++)
    {
        printf("%d   ", arr3[i]);
    }
    printf("\n");
}