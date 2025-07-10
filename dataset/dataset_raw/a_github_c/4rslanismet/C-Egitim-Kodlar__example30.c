


#include <stdio.h>

#define SIZE 11

void okuYaz (void);

int main()
{
   okuYaz();

   return 0;

}

void okuYaz (void)
{
    int num[SIZE], i;

    printf("%s","okul numaranızı giriniz:");
    
    for(i=0;i<SIZE;i++)
        scanf("%d",&num[i]);

    printf("%s\n","okul numaranız:");

    for(i=0;i<SIZE;i++)
        printf("%d",num[i]);
}