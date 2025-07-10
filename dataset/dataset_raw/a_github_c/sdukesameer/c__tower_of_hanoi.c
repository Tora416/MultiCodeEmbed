#include <stdio.h>
#define SRC 'A'
#define INTER 'B'
#define DEST 'C'
void move(int n, char src, char dest, char inter);
int main()
{
    int n;
    scanf("%d", &n);                
    printf("Number of disks: %d\n", n);
    move(n, SRC, DEST, INTER);
    return 0;
}
void move(int n,char src, char dest, char inter)
{
    if(n<1)
        printf("ERROR");
    else
    {
        static int c=0;
        if(n==1)
        {
            c++;
            printf("%d: Move top disk from %c to %c\n",c,src,dest);
            return;
        }
        move(n-1,src,inter,dest);
        c++;
        printf("%d: Move top disk from %c to %c\n",c,src,dest);
        move(n-1,inter,dest,src);
    }
}
