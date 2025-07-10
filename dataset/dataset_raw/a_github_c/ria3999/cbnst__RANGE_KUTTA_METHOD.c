# include<stdio.h>
float func(float x,float y)
{
    return ((x-y)/(x+y));
}
int main()
{
    int i,n;
    float x0,y0,h,xn,k1,k2,k3,k4,x,y,k;
    printf("\n\n***INPUT***\n\n");
    printf("Enter x0,y0,h,xn:\n");
    scanf("%f%f%f%f",&x0,&y0,&h,&xn);
    n=(xn-x0)/h;
    x=x0;
    y=y0;
    for(i=0;i<=n;i++)
    {
        k1=h*func(x,y);
        k2=h*func(x+(h/2),y+(k1/2));
        k3=h*func(x+(h/2),y+(k2/2));
        k4=h*func(x+h,y+k3);
        k=(k1+2*(k2+k3)+k4)/6.0;
        x=x+h;
        y=y+k;
    }
    printf("\n\n***OUTPUT***\n\n");
    printf("Result is:\n");
    printf("x=%f y=%f",x,y);
    return 0;
}
