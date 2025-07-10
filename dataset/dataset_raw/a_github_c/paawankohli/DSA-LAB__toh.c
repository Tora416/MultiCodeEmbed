#include <stdio.h>
#include <string.h>

int move(int n, char s, char d, char a)
{
    
    
    

    if (n == 1)
    {
        printf("Move disk from %c to %c \n", s, d);
        return 1;
    }

    else

    {
        int n1  = move(n - 1, s, a, d);
    
        int n2 = 1; 
        printf("Move disk from %c to %c \n", s, d);

        int n3 = move(n - 1, a, d, s);

        return n1 + n2 + n3;
    }
}


int main()
{
    int plates;
    char source = 'A', destin = 'C', aux = 'B';

    printf("Enter number of plates on A:");
    scanf("%d", &plates);

    printf("No. of moves: %d \n", move(plates, source, destin, aux));

    
}