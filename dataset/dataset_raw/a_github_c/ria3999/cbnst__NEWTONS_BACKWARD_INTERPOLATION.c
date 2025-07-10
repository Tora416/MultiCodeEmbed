#include <stdio.h>

float u_cal(float u, int n)
{
    float temp = u;
    for (int i = 1; i < n; i++)
        temp = temp * (u + i);
    return temp;
}
int fact(int n)
{
    int f = 1;
    for (int i = 2; i <= n; i++)
        f *= i;
    return f;
}

int main()
{
    int n,i,j;
    float x[90],value,sum=0;
    float y[90][90];
    printf("\n\n***INPUT***\n\n");
    printf("Enter n\n");
    scanf("%d",&n);
    printf("Enter value of x:\n");
    for(i=0;i<n;i++)
        scanf("%f",&x[i]);
    printf("Enter value of y:\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<1;j++)
        {
            printf("Enter y[%d][%d] ",i,j);
            scanf("%f",&y[i][j]);
        }
    }
    for (int i = 1; i < n; i++) {
        for (int j = n - 1; j >= i; j--)
            y[j][i] = y[j][i - 1] - y[j - 1][i - 1];
    }
    printf("Backward difference table:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++)
            printf("%.2f ",y[i][j]);
        printf("\n");
    }
    printf("Enter value of which you want the answer:\n");
    scanf("%f",&value);
    sum = y[n - 1][0];
    float u = (value - x[n - 1]) / (x[1] - x[0]);
    for (int i = 1; i < n; i++) {
        sum = sum + (u_cal(u, i) * y[n - 1][i]) /
                                     fact(i);
    }
    printf("\n\n***OUTPUT***\n\n");
    printf("\n Value at %f is %f",value,sum);
    return 0;
}
