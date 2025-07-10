#include<stdio.h>
int main()
{
    int
    a[5][5], b[5][5], sum=0;
    int r, c;
    for(r=0; r<=2; r++)
        {
            for(c=0; c<=2; c++)
            {
                scanf("%d", &a[r][c]);
            }
        }
        printf("\n");
        for(r=0; r<=2; r++)
        {
            for(c=0; c<=2; c++)
            {
                scanf("%d", &b[100][100]);
            }
        }
        printf("\n");
        for(r=0; r<=2; r++)
        {
            for(c=0; c<=2; c++)
            {
                sum=a[r][c];
            }
            printf("%d", sum);
        }
        return 0;
}
