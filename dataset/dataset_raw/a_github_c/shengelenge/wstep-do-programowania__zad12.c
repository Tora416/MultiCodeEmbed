#include <stdio.h>

int main()
{
    char ch;

    printf("Podaj jeden znak: ");
    scanf("%c", &ch);

    switch (ch)
    {
        case 65:
            printf("S");
            break;
        case 66:
            printf("N");
            break;
        case 67:
            printf("V");
            break;
        case 68:
            printf("F");
            break;
        case 69:
            printf("R");
            break;
        case 70:
            printf("G");
            break;
        case 71:
            printf("H");
            break;
        case 72:
            printf("J");
            break;
        case 73:
            printf("O");
            break;
        case 74:
            printf("K");
            break;
        case 75:
            printf("L");
            break;
        case 76:
            printf(":");
            break;
        case 77:
            printf("<");
            break;
        case 78:
            printf("M");
            break;
        case 79:
            printf("P");
            break;
        case 80:
            printf("{");
            break;
        case 81:
            printf("W");
            break;
        case 82:
            printf("T");
            break;
        case 83:
            printf("D");
            break;
        case 84:
            printf("Y");
            break;
        case 85:
            printf("I");
            break;
        case 86:
            printf("B");
            break;
        case 87:
            printf("E");
            break;
        case 88:
            printf("C");
            break;
        case 89:
            printf("U");
            break;
        case 90:
            printf("X");
            break;
        case 97:
            printf("s");
            break;
        case 98:
            printf("n");
            break;
        case 99:
            printf("v");
            break;
        case 100:
            printf("f");
            break;
        case 101:
            printf("r");
            break;
        case 102:
            printf("g");
            break;
        case 103:
            printf("h");
            break;
        case 104:
            printf("j");
            break;
        case 105:
            printf("o");
            break;
        case 106:
            printf("k");
            break;
        case 107:
            printf("l");
            break;
        case 108:
            printf(";");
            break;
        case 109:
            printf(",");
            break;
        case 110:
            printf("m");
            break;
        case 111:
            printf("p");
            break;
        case 112:
            printf("[");
            break;
        case 113:
            printf("w");
            break;
        case 114:
            printf("t");
            break;
        case 115:
            printf("d");
            break;
        case 116:
            printf("y");
            break;
        case 117:
            printf("i");
            break;
        case 118:
            printf("b");
            break;
        case 119:
            printf("e");
            break;
        case 120:
            printf("c");
            break;
        case 121:
            printf("u");
            break;
        case 122:
            printf("x");
            break;
        default:
            printf("Podany znak nie jest litera.");
            break;
    }


    return 0;
}