#include<stdio.h>
int main()
{
    int m,i,j;
    float Y[20][20]={0},x,res=1.0,sum=0;
    printf("\n\n\t\t\t\t***INPUT*");
    printf("\nEnter the limit:");
    scanf("%d",&m);
    printf("\nEnter the elements of x and y:");
    for(i=0;i<m;i++)
    {
        for(j=0;j<2;j++)
            scanf("%f",&Y[i][j]);
    }
    printf("\nThe table entered is:\n");
     for(i=0;i<m;i++)
    {
        for(j=0;j<2;j++)
            printf("%0.3f  ",Y[i][j]);
        printf("\n");
    }
    printf("\nEnter the value of x to find y:");
    scanf("%f",&x);
    printf("\n\n\t\t\t\t***OUTPUT*\n");
    for(i=0;i<m;i++)
    {
        res=1.0;
        for(j=0;j<m;j++)
        {
            if(j!=i)
                res*=((x-Y[j][0])*1.0)/(Y[i][0]-Y[j][0]);
            else
                continue;
        }
        sum+=res*Y[i][1];
    }
    printf("The value of y at x=%0.3f is %0.3f",x,sum);
}
