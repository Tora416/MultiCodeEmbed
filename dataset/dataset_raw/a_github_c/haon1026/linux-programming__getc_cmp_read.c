

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp1 = fopen(argv[1], "r");
    if(fp1 == NULL)
    {
        perror("file1 fopen error");
        exit(1);
    }

    FILE *fp2 = fopen(argv[2], "w");
    if(fp2 == NULL)
    {
        perror("file2 fopen error");
        exit(1);
    }

    int n;
    while((n = fgetc(fp1)) != EOF)
    {
        fputc(n, fp2);
    }
    
    fclose(fp1);
    fclose(fp2);
    return 0;
}




