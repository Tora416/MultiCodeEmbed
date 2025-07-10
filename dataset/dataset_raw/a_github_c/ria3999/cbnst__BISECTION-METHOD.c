# include<stdio.h>
# include<math.h>
float function(float);
void main()
{
    float a,b,fa,fb,c,fc;
    do
    {
        printf("Enter interval\n");
        scanf("%f%f",&a,&b);
        fa=function(a);
        printf("Value of fa=%f\n",fa);
        fb=function(b);
        printf("Value of fb=%f\n",fb);
    }while(fa*fb>0);
    printf("next loop");
    do
    {
        c=(a+b)/2.0;
        printf("c is now=%f\n",c);
        fa=function(a);
        fb=function(c);
        printf("fb becomes=%f\n",fb);
        if(fa*fb<0)
            b=c;
        else
            a=c;
        printf("fabs=%f",fabs(fb));
    }while(fabs(fb)>=0.0001);
    printf("The root is %f",c);
}
float function(float x)
{
    float f;
    f=x+cos(x);
    return(f);
}
