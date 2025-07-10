#include <stdio.h>
#include <stdlib.h>

int main()
{
    int c; 
    int l; 


for (l=1; l<6; l++)
    {
        for (c=1; c<6; c++)
        {
            if(c<l){
                printf("# ");

            }else if (c == l)
                {
                    printf("+ ");

                }else if(c > 1)
                {
                    printf("# ");
                }

        }



        printf("\n");
    }
        printf("\n\n\n");




}
