#include<stdio.h>
#include<math.h>
int main()
    {
    float a,b,c,t,t1,t2,real,ima;
    printf("Enter the co-efficients of the quadratic equation");
    scanf("%f%f%f",&a,&b,&c);
    
    t=sqrt(b*b-4*a*c);
    printf("%f",t);
    
    if(t>0)
        {
        t1=(-b+t)/(2*a);
        t2=(-b-t)/(2*a);
        printf("\nRoots are unequal and roots are %.2f %.2f\n",t1,t2);
        }
    else if(t==0)   
        {
        printf("\nTwo roots are equal and roots are %.2f %.2f\n",-b/(2*a),-b/(2*a));
        }
    else
        {
        real=-b/(2*a);
        ima=sqrt(4*a*c-b*b)/(2*a);
        printf("\nTwo distinct complex Roots are %.2f+i%.2f and %.2f-i%.2f \n",real,ima,real,ima);
        }
    return 0;
    }   
        
    
    

    
        
