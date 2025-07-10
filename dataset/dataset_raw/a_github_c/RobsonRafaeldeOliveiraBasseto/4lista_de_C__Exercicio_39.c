

#include <stdio.h>
#include <stdlib.h>

int fatorial(int x);
int comb(int lin, int col);

int main()
{
    int lin, col, n, num;

    printf("Digite a quantidade de linhas: ");
    scanf("%d", &n);
    printf("\n");

    for(lin=0;lin<=n;lin++){
        for(col=n-lin;col!=0;col--){
            printf("   ");
        }
        for(col=0;col<=lin;col++){
            num = comb(lin, col);
            printf(" %4d ", num);
        }
        printf("\n");
    }
    return 0;
}

int fatorial(int x){
  int i, fatorial=1;

  for(i=x;i>0;i--){
    fatorial = fatorial*i;
  }
  return fatorial;
}

int comb(int lin, int col){

 return fatorial(lin) / (fatorial(col) * fatorial(lin-col));
}
