#include<stdio.h>
int main()
{
    int a[2][2];
    int r1,c1;
    for(r1=0; r1<=1; r1++)
    {
        for(c1=0; c1<=1; c1++)
        {
            scanf("%d", &a[r1][c1]);
        }
    }
    printf("The first matrix is:\n");
    for(r1=0; r1<=1; r1++)
    {
        for(c1=0; c1<=1; c1++)
        {
            printf("%d ", a[r1][c1]);
        }
        printf("\n");
    }
    
    int r2,c2;
    for(r2=0; r2<=1; r2++)
    {
        for(c2=0; c2<=1; c2++)
        {
            scanf("%d", &a[r2][c2]);
        }
    }
    printf("The Secound matrix is:\n");
    for(r2=0; r2<=1; r2++)
    {
        for(c2=0; c2<=1; c2++)
        {
            printf("%d ", a[r2][c2]);
        }
        printf("\n");
    }
    for(r1=0; r1<=1; r1++)
    {
        for(c1=0; c1<=1; c1++)
        {
            for(r2=0; r2<=1; r2++)
            {
                for(c2=0; c2<=1; c2++)
                {
                    if(r1==r2&&c1==c2)
                        {
                            printf("Two matrices are equal");
                        }
                    else
                        {
                            printf("Not equal");
                        }


                }
            }
        }
    }


    return 0;
}
