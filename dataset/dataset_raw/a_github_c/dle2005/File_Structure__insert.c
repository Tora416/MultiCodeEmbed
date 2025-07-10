#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    FILE *fp;

    fp = fopen(argv[1], "r+");

    long offset = atol(argv[2]);
    int datalen = strlen(argv[3]);
    fseek(fp, 0, SEEK_END);
    long filelen = ftell(fp);
    char *buf = malloc(sizeof(char) * (filelen - offset) +1);
    char ch;
    int count = 0;

    fseek(fp, offset, SEEK_SET);

    while((ch = fgetc(fp)) != EOF) {
        buf[count] = ch;
        count++;
    }

    fseek(fp, offset, SEEK_SET);

    fwrite(argv[3], sizeof(char), datalen, fp);
    fwrite(buf, sizeof(char), strlen(buf), fp);

    fclose(fp);
    free(fp);
    return 0;
}
