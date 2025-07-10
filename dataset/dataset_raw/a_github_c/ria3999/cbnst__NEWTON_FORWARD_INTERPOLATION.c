#include <stdio.h>
float cal(float u, int n)
{
    float temp = u;
    for (int i = 1; i < n; i++)
        temp = temp * (u - i);
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
    int n,i,j,u;
    float x[90],value;
    float y[90][90],sum=0;
    printf("\n\n***INPUT***\n\n");
    printf("Enter n:\n");
    scanf("%d",&n);
    printf("Enter the values of x\n");
    for(i=0;i<n;i++)
        scanf("%f",&x[i]);
    printf("Enter the values of y\n");
    for(i=0;i<n;i++)
    {
        for(j=0;j<1;j++)
        {
            scanf("%f",&y[i][j]);
        }
    }
    for (int i = 1; i < n; i++)
    {
        for (int j = 0; j < n - i; j++)
            y[j][i] = y[j + 1][i - 1] - y[j][i - 1];
    }
    printf("forward difference table is:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%f ",x[i]);
        for (int j = 0; j < n - i; j++)
            printf("%f ",y[i][j]);
        printf("\n");
    }
    printf("Enter value:\n");
    scanf("%f",&value);
    sum = y[0][0];
    u = (value - x[0]) / (x[1] - x[0]);
    for (int i = 1; i < n; i++) {
        sum = sum + (cal(u, i) * y[0][i]) /
                                 fact(i);
    }
    printf("\n\n***OUTPUT***\n\n");
    printf("Value at %f is %f",value,sum);
    return 0;
}
