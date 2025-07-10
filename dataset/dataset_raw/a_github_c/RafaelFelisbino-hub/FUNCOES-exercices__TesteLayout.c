#include <stdio.h>
#include <Windows.h>
#include <stdlib.h>

void gotoxy(int x, int y);
int i;
int main()
{
    gotoxy(0,0); printf("%c",218);
    for(i = 1; i <= 69; i++)
    {
        gotoxy(i,0); printf("%c",196);
    }
    gotoxy(70,0); printf("%c",191);
    for(i = 1; i <= 15; i++)
    {
        gotoxy(0,i); printf("%c",179);
    }
     for(i = 1; i <= 15; i++)
    {
        gotoxy(70,i); printf("%c",179);
    }
    gotoxy(0,16); printf("%c",192);
    gotoxy(70,16); printf("%c",217);
    for(i = 1; i <= 69; i++)
    {
        gotoxy(i,16); printf("%c",196);
    }
    gotoxy(19,1); printf("%c",218);
    for(i = 20; i <= 50; i++)
    {
        gotoxy(i,1); printf("%c",196);
    }
    gotoxy(51,1); printf("%c",191);
    gotoxy(19,2); printf("%c",179);
    gotoxy(51,2); printf("%c",179);
    gotoxy(19,3); printf("%c",192);
    gotoxy(51,3); printf("%c",217);
    for(i = 20; i <= 50; i++)
    {
        gotoxy(i,3); printf("%c",196);
    }
    gotoxy(19,5); printf("%c",218);
    for(i = 20; i <= 50; i++)
    {
        gotoxy(i,5); printf("%c",196);
    }
    gotoxy(51,5); printf("%c",191);
    gotoxy(19,6); printf("%c",179);
    gotoxy(51,6); printf("%c",179);
    gotoxy(19,7); printf("%c",192);
    gotoxy(51,7); printf("%c",217);
    for(i = 20; i <= 50; i++)
    {
        gotoxy(i,7); printf("%c",196);
    }
    gotoxy(19,9); printf("%c",218);
    for(i = 20; i <= 50; i++)
    {
        gotoxy(i,9); printf("%c",196);
    }
    gotoxy(51,9); printf("%c",191);
    gotoxy(19,10); printf("%c",179);
    gotoxy(51,10); printf("%c",179);
    gotoxy(19,11); printf("%c",192);
    gotoxy(51,11); printf("%c",217);
    for(i = 20; i <= 50; i++)
    {
        gotoxy(i,11); printf("%c",196);
    }
    
    gotoxy(19,13); printf("%c",218);
    for(i = 20; i <= 50; i++)
    {
        gotoxy(i,13); printf("%c",196);
    }
    gotoxy(51,13); printf("%c",191);
    gotoxy(19,14); printf("%c",179);
    gotoxy(51,14); printf("%c",179);
    gotoxy(19,15); printf("%c",192);
    gotoxy(51,15); printf("%c",217);
    for(i = 20; i <= 50; i++)
    {
        gotoxy(i,15); printf("%c",196);
    }

    
    gotoxy(6,3); printf("%c",218);
    gotoxy(7,3); printf("%c",196);
    gotoxy(8,3); printf("%c",191);
    for (i = 4; i <= 13; i++)
    {
        gotoxy(6,i); printf("%c",179);
    }
     for (i = 4; i <= 13; i++)
    {
        gotoxy(8,i); printf("%c",179);
    }
    gotoxy(6,14); printf("%c",192);
    gotoxy(7,14); printf("%c",196);
    gotoxy(8,14); printf("%c",217);
    gotoxy(7,4); printf("T");
    gotoxy(7,5); printf("A");
    gotoxy(7,6); printf("X");
    gotoxy(7,7); printf("I");
    gotoxy(7,9); printf("A");
    gotoxy(7,10); printf("E");
    gotoxy(7,11); printf("R");
    gotoxy(7,12); printf("E");
    gotoxy(7,13); printf("O");


    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    system("pause");
}

void gotoxy(int x, int y)
{
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
