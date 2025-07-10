# include<stdio.h>
float fun(float x)
{
    float temp;
    temp=1/(1+(x*x));
    return temp;
}
int main()
{
    float x0,xn;
    int n;
    float h,s=0,sume=0,sumo=0;
    printf("\n\n***INPUT***\n\n");
    printf("Enter value of n\n");
    scanf("%d",&n);
    printf("Enter x0 and xn\n");
    scanf("%f%f",&x0,&xn);
    h=(xn-x0)/n;
    s=fun(x0)+fun(xn);
    for(int i=1;i<n;i++)
    {
        if(i%2==0)
            s=s+2*fun(x0+i*h);
        else
            s=s+4*fun(x0+i*h);
    }
    s=s*h/3;
    printf("\n\n***OUTPUT***\n\n");
    printf("Result is %f",s);
    return 0;
}
