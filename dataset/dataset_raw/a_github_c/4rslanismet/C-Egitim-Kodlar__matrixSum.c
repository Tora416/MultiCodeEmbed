#include<stdio.h>

#define BOYUT 2

int main()
{
    int m1[BOYUT][BOYUT];
    int m2[BOYUT][BOYUT];
    int toplam[BOYUT][BOYUT];
    int i,j;

    for(i=0;i<BOYUT;i++)
        for(j=0;j<BOYUT;j++)
        {
            printf("%s","değer giriniz:\n");
            scanf("%d",&m1[i][j]);
        }

    for(i=0;i<BOYUT;i++)
        for(j=0;j<BOYUT;j++)
        {
            printf("%s","değer giriniz:\n");
            scanf("%d",&m2[i][j]);
        }

    for(i=0;i<BOYUT;i++)
        for(j=0;j<BOYUT;j++)
            toplam[i][j]=m1[i][j] + m2[i][j];

    for(i=0;i<BOYUT;i++)
        for(j=0;j<BOYUT;j++)
            printf("toplam[%d][%d]=%d\n",i,j,toplam[i][j]);

    return 0;

}