
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *A;
    int n;
    int choice;
    int size = 0;
    int t;
    printf("1 : Lower Triangular Matrix\n");
    printf("2 : Upper Triangular Matrix\n");
    printf("Enter Choice : ");
    scanf("%d", &choice);
    printf("Enter Dimensions : ");
    scanf("%d", &n);

    switch(choice)
    {
        case 1 :
        size = n*(n + 1) / 2;
        A = (int*)malloc(size * sizeof(int));
        printf("\nEnter elements : \n");
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                scanf("%d", &t);
                if(i >= j)
                    A[i*(i-1)/2 + (j-1)] = t ;
            }
        }
        printf("\n1D array storing the elements : ");
        for(int i = 0 ; i < size ; i++)
        {
            printf("%d ", A[i]);
        }
        printf("\n\nDisplaying matrix from stored 1D array values :\n");
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                if(i >= j)
                    printf("%d ", A[i*(i-1)/2 + (j-1)]);
                else
                    printf("  ");
            }
            printf("\n");
        }
        break;

        case 2 :
        size = n * (n + 1) / 2;
        A = (int*)malloc(size * sizeof(int));
        printf("\nEnter elements : \n");
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                scanf("%d", &t);
                if(i <= j)
                    A[(n*(i-1) - (i-1)*(i-2)/2) + (j-i)] = t ;
            }
        }
        printf("\n1D array storing the elements : ");
        for(int i = 0 ; i < size ; i++)
        {
            printf("%d ", A[i]);
        }
        printf("\n\nDisplaying matrix from stored 1D array values :\n");
        for(int i = 1 ; i <= n ; i++)
        {
            for(int j = 1 ; j <= n ; j++)
            {
                if(i <= j)
                    printf("%d ", A[(n*(i-1) - (i-1)*(i-2)/2) + (j-i)]);
                else
                    printf("  ");
            }
            printf("\n");
        }
        break;
    }

}