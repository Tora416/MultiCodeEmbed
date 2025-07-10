#include <stdio.h>

int main()
{
    int n;
    scanf ("%i", &n);

    n = (n/2)+1;

    for (int i=1; i<=n; i++)
    {
        for (int j=(n-1); j>=i; j--)
        {
            putchar (' ');
        }
        for (int k=1; k<=i; k++)
        {
            putchar ('*');
        }
        for (int l=1; l<i; l++)
        {
            putchar ('*');
        }
        putchar ('\n');
    }
    for (int i=(n-1); i>0; i--)
    {
        for (int j=i; j<n; j++)
        {
            putchar (' ');
        }
        for (int k=1; k<=i; k++)
        {
            putchar ('*');
        }
        for (int l=1; l<i; l++)
        {
            putchar ('*');
        }
        putchar ('\n');
    }
    putchar ('\n');

    return 0;
}