#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c; 
    int l; 
    int a;
    int b = 1;

    printf("Digite um numero: ");
    scanf("%d",&a);

  for (l=0; l<a; l++)
    {
        for (c=0; c<a;c++)
        {
           if (l == c )
           {

               printf("%d ",b);
               b++;
           }else
            {
                printf("  ");
            }

        }
        printf("\n");
    }
        printf("\n\n\n");








}
