#include <stdio.h>

double add(double L[], int n)
{
    double sum = 0;

    for(int i = 0 ; i < n ; i++)
        sum += L[i];

    return sum;
}

int Lsearch(int arr[], int n, int x)
{
    for(int i = 0 ; i < n ; i++)
        if(arr[i] == x)
            return i + 1;

    return -1;
}

void multiply(int a[][10], int b[][10], int m, int n, int p, int q)
{
    int f[10][10], sum = 0;

    if(n != p)
    {
        printf("Invalid Order\n");
        return;
    }

    for(int c = 0 ; c < m ; c++)
        for(int d = 0 ; d < q ; d++)
        {
            for(int k = 0 ; k < p ; k++)
                sum += a[c][k] * b[k][d];

            f[c][d] = sum;
            sum = 0;
        }

    printf("Product of matrices: \n");

    for(int c = 0 ; c < m ; c++)
    {
        for(int d = 0 ; d < q ; d++)
            printf("%d\t", f[c][d]);

        printf("\n");
    }

    printf("\n");
}

int secLar(int a[], int n)
{
    int first, second;

    first = second = -99999;

    for(int i = 0; i < n ; i++)
        if(a[i] > first)
        {
            second = first;
            first = a[i];
        }
        else if(a[i] > second && a[i] < first)
            second = a[i];

    return second;
}

int main()
{
    int ch;

    do
    {
        printf("1. Add array elements\n");
        printf("2. Linear Search\n");
        printf("3. Multiply Matrices\n");
        printf("4. Find second largest element in an array\n");
        printf("5. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &ch);

        int size1; double arr1[50];                         
        int size2, arr2[50], x;                             
        int m, n, p, q, first[10][10], second[10][10];      
        int size3, arr3[50];                                

        switch(ch)
        {
            case 1:
                    

                    printf("Enter size: ");
                    scanf("%d", &size1);
                    
                    printf("Enter elements: ");
                    for(int i = 0 ; i < size1 ; i++)
                        scanf("%lf", &arr1[i]);

                    printf("Sum of elements is %lf \n\n", add(arr1, size1));
                    break;

            case 2:
                    

                    printf("Enter size: ");
                    scanf("%d", &size2);

                    printf("Enter elements: ");
                    for(int i = 0 ; i < size2 ; i++)
                        scanf("%d", &arr2[i]);

                    printf("Enter element to be searched: ");
                    scanf("%d", &x);

                    printf("Element found at %dth position.\n\n", Lsearch(arr2, size2, x));
                    break;

            case 3:
                    

                    printf("Enter order of first matrice: ");
                    scanf("%d %d", &m, &n);
                    printf("Enter elements: \n");
                    for(int i = 0 ; i < m ; i++)
                        for(int j = 0 ; j < n ; j++)
                            scanf("%d", &first[i][j]);

                    printf("Enter order of second matrice: ");
                    scanf("%d %d", &p, &q);
                    printf("Enter elements: \n");
                    for(int i = 0 ; i < p ; i++)
                        for(int j = 0 ; j < q ; j++)
                            scanf("%d", &second[i][j]);

                    multiply(first, second, m, n, p, q);
                    break;
            
            case 4: 
                    

                    printf("Enter size: ");
                    scanf("%d", &size3);

                    printf("Enter elements: ");
                    for(int i = 0 ; i < size3 ; i++)
                        scanf("%d", &arr3[i]);

                    printf("Second largest element is %d.\n\n", secLar(arr3, size3));
                    break;
            
            case 5: 
                    break;

            default:
                    printf("Invalid input. Please try again!\n\n");
        }

    }while(ch != 5);
}