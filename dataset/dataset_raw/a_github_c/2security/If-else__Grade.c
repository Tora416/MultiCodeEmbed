#include<stdio.h>
#include<math.h>
int main()
    {
    float p,c,b,m,ca,t;
    printf("Enter makrs of Physics");
    scanf("%f",&p);

    printf("Enter makrs of Chemistry");
    scanf("%f",&c);
    
    printf("Enter makrs of Bialogy");
    scanf("%f",&b);
        
    printf("Enter makrs of Mathematics");
    scanf("%f",&m);
    
    printf("Enter makrs of Computer");
    scanf("%f",&ca);
    
    t=((p+c+b+m+ca)/500)*100;
        
    if(t>=90)
        printf("\nGRADE A\n");
    
    else if(t>=90)
        printf("\nGRADE A\n");
    
    else if(t>=80)
        printf("\nGRADE B\n");
    
    else if(t>=70)
        printf("\nGRADE C\n");
    
    else if(t>=60)
        printf("\nGRADE D\n");

    else if(t>=40)
        printf("\nGRADE E\n");

    else
        printf("\nGRADE F\n");

    printf("\n");   
    return 0;
    }   
        
    
    

    
        
