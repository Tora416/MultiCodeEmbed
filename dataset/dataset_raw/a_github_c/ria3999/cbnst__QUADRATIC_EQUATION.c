# include<stdio.h>
void main()
{
    float a,b,c,d,x1,x2,realpart,imaginarypart;
    printf("\n\n***INPUT***\n\n");
    printf("enter coefficients a,b and c \n");
    scanf("%f%f%f",&a,&b,&c);
    d=b*b-4*a*c;
    printf("\n\n***OUTPUT***\n\n");
    if(d>0)
    {
        x1=(-b+sqrt(d))/(2*a);
        x2=(-b-sqrt(d))/(2*a);
        printf("root1 is %f and root2 is %f",x1,x2);
    }
    else if(d==0)
    {
        x2=(-b)/(2*a);
        x1=x2;
        printf("equal roots are %f and %f",x1,x2);
    }
    else
    {
        realpart=-b/(2*a);
        imaginarypart=sqrt(-d)/(2*a);
        printf("root1=%f+i%f & root2=%f-i%f",realpart,imaginarypart,realpart,imaginarypart);

    }

}
