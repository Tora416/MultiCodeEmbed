

#include<stdio.h>

int main(void){
    setvbuf(stdout , NULL , _IONBF , 0);                        
    setvbuf(stderr , NULL , _IONBF , 0);

    int i,j,rows;

        printf("Enter number of rows: ");
        scanf("%d",&rows);
        printf("\n");

        for(i=0;i<rows;i++)
        {
            if(i == rows/2){
                continue;
            }
            for(j=0;j<rows;j++)
            {
                if(j == rows/2){
                    continue;
                }
                if( (j==i) || (j==rows-i-1) )
                {
                    printf("*");
                }
                else
                {
                    printf(" ");
                }
            }
            printf("\n");
        }
        return 0;

}
