# include<stdio.h>
float function(float x)
{
    return(2*x-log10(x)-7);
}
void main()
{
    float a,b,fa,fb,c,fc;
    printf("\n\n***INPUT***\n\n");
    do
    {
        printf("Enter intervals a and b");
        
        scanf("%f%f",&a,&b);
        fa=function(a);
        fb=function(b);
    }while(fa*fb>0);
    int i=-1;
    float d=-1;
    do
    {
        i++;
        if(i!=0)
        d=c;
        fa=function(a);
        fb=function(b);
        c=a-((b-a)/(function(b)-function(a)))*function(a);
        fc=function(c);
        if(fa*fc>0)
            a=c;
        else
            b=c;
    }while(d!=c);
    printf("\n\n***OUTPUT***\n\n");
    printf("The required root is %f \n",c);
}
