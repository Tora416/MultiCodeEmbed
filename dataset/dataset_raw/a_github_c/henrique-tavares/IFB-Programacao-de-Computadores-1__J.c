#include <stdio.h>

int main ()
{
    int n, qtd;
    scanf ("%i", &qtd);

    for (int i=0; i<qtd; i++)
    {
        scanf ("%i", &n);

        while (n>=1000)
        {
            putchar ('M');
            n -= 1000;
        }

        if ((900<=n)&&(n<=999))
        {
            printf ("CM");
            n -= 900;
        }
        else if ((800<=n)&&(n<=899))
        {
            printf ("DCCC");
            n -= 800;
        }
        else if ((700<=n)&&(n<=799))
        {
            printf ("DCC");
            n -= 700;
        }
        else if ((600<=n)&&(n<=699))
        {
            printf ("DC");
            n -= 600;
        }
        else if ((500<=n)&&(n<=599))
        {
            printf ("D");
            n -= 500;
        }
        else if ((400<=n)&&(n<=499))
        {
            printf ("CD");
            n -= 400;
        }
        else if ((300<=n)&&(n<=399))
        {
            printf ("CCC");
            n -= 300;
        }
        else if ((200<=n)&&(n<=299))
        {
            printf ("CC");
            n -= 200;
        }
        else if ((100<=n)&&(n<=199))
        {
            printf ("C");
            n -= 100;
        }

        if ((90<=n)&&(n<=99))
        {
            printf ("XC");
            n -= 90;
        }
        else if ((80<=n)&&(n<=89))
        {
            printf ("LXXX");
            n -= 80;
        }
        else if ((70<=n)&&(n<=79))
        {
            printf ("LXX");
            n -= 70;
        }
        else if ((60<=n)&&(n<=69))
        {
            printf ("LX");
            n -= 60;
        }
        else if ((50<=n)&&(n<=59))
        {
            printf ("L");
            n -= 50;
        }
        else if ((40<=n)&&(n<=49))
        {
            printf ("XL");
            n -= 40;
        }
        else if ((30<=n)&&(n<=39))
        {
            printf ("XXX");
            n -= 30;
        }
        else if ((20<=n)&&(n<=29))
        {
            printf ("XX");
            n -= 20;
        }
        else if ((10<=n)&&(n<=19))
        {
            printf ("X");
            n -= 10;
        }

        switch (n)
        {
            case 9:
                printf ("IX");
                n -= 9;
                break;
            case 8:
                printf ("VIII");
                n -= 8;
                break;
            case 7:
                printf ("VII");
                n -= 7;
                break;
            case 6:
                printf ("VI");
                n -= 6;
                break;
            case 5:
                printf ("V");
                n -= 5;
                break;
            case 4:
                printf ("IV");
                n -= 4;
                break;
            case 3:
                printf ("III");
                n -= 3;
                break;
            case 2:
                printf ("II");
                n -= 2;
                break;
            case 1:
                printf ("I");
                n -= 1;
                break;

        }
        printf ("\n");
    }

    return 0;

}