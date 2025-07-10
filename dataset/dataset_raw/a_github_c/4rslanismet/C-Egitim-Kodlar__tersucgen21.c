#include <stdio.h>

int main ()

{
    int i,k,l,yildiz;
    
    printf("boyut giriniz:");
    scanf("%d",&yildiz);

    if(yildiz<0)
    {
        printf("hatalı giriş");
        return 1;
    }

    for(i=1;i<=yildiz;i++)
    {
         for(k=1;k<=yildiz-i;k++)
             printf(" ");
     
          for(l=1;l<=i;l++)
              printf("*");

      printf("\n");
     }


    return 0;

}
