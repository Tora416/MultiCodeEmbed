#include <stdio.h>
#include "sort.h"


void merge_sort(int *array, size_t size)
{
    int n = (int)size;
    int *brray;

    if (size < 2)
        return;
    brray = malloc(sizeof(int) * size);
    CopyArray(array, 0, n, brray);
    TopDownSplitMerge(brray, 0, n, array);
    free(brray);
}


void TopDownSplitMerge(int B[], int iBegin, int iEnd, int A[])
{
    int iMiddle, index;

    if (iEnd - iBegin <= 1)
        return;
    iMiddle = (iEnd + iBegin) / 2;

    TopDownSplitMerge(A, iBegin,  iMiddle, B);
    TopDownSplitMerge(A, iMiddle, iEnd, B);

    printf("Merging...\n");
    TopDownMerge(B, iBegin, iMiddle, iEnd, A);
    printf("[Done]: ");
    for (index = iBegin; index < iEnd; index++)
    {
        printf("%d", A[index]);
        if (index != iEnd - 1)
            printf(", ");
    }
    printf("\n");
}



void TopDownMerge(int A[], int iBegin, int iMiddle, int iEnd, int B[])
{
    int i = iBegin, j = iMiddle, k, index;

    for (k = iBegin; k < iEnd; k++)
    {
        if (i < iMiddle && (j >= iEnd || A[i] <= A[j]))
        {
            B[k] = A[i];
            i = i + 1;
        }
        else
        {
            B[k] = A[j];
            j = j + 1;
        }
    }
    printf("[left]: ");
    for (index = iBegin; index < iMiddle; index++)
    {
        printf("%d", A[index]);
        if (index != iMiddle - 1)
            printf(", ");
    }
    printf("\n");
    printf("[right]: ");
    for (index = iMiddle; index < iEnd; index++)
    {
        printf("%d", A[index]);
        if (index != iEnd - 1)
            printf(", ");
    }
    printf("\n");
}


void CopyArray(int A[], int iBegin, int iEnd, int B[])
{
    int k;

    for (k = iBegin; k < iEnd; k++)
        B[k] = A[k];
}
