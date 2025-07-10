#include <stdio.h>

void decToBin(int dec)
{
    float resto;
    int numeriBinari[100], i = 0;

    while(dec > 0)
    {
        numeriBinari[i] = dec % 2;
        dec = dec/2;
        i++;
    }

    for(int j = i-1; j>=0; j--)
    {
        printf("%d",numeriBinari[j]);
    }

}


int main(){
    int n;
    printf("Giac: ");
    scanf("%d",&n);

    decToBin(n);

        

    return 0;
}
