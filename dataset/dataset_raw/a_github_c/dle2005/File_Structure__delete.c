#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    FILE *fp;

    fp = fopen(argv[1], "r+");

    long offset = atol(argv[2]);
    int deletelen = atoi(argv[3]);

    fseek(fp, 0, SEEK_END);
    int filelen = ftell(fp);
    char *buf = malloc(sizeof(char) * (filelen - offset - deletelen) +1);
    char ch;
    int count = 0;

    fseek(fp, offset + deletelen, SEEK_SET);

    while((ch = fgetc(fp)) != EOF) {
        buf[count] = ch;
        count++;
    }

    fseek(fp, offset, SEEK_SET);

    fwrite(buf, sizeof(char), strlen(buf), fp);

    truncate(argv[1], filelen - deletelen);

    fclose(fp);
    free(buf);

    return 0;
}
