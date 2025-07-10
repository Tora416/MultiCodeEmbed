#include <stdio.h>
#include <stdlib.h>

int main()
{

int c; 
int l; 
int a;
int b;

    printf("Digite um numero: ");
    scanf("%d",&a);

    for (l=1; l<a; l++)
    {
        for (c=1; c<=a; c++)
        {
            if(c<=l){

                    b = c;
                printf("%d ",b);

            }
        }

        printf("\n");
    }
        printf("\n\n\n");





}
