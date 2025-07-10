#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int fd;
    int offset = atoi(argv[2]);
    int deletebyte = atoi(argv[3]);
    int filelen, templen;
    char *temp;

    if((fd = open(argv[1], O_RDWR)) == -1) {
        perror("file openning error");
        return 1;
    }

    if((filelen = lseek(fd, 0, SEEK_END)) == -1) {
        perror("lseek END error");
        close(fd);
        return 1;
    }

    templen = filelen - offset - deletebyte;
    temp = malloc(sizeof(char) * templen + 1);

    if(lseek(fd, offset +deletebyte, SEEK_SET) == -1) {
        perror("lseek error");
        close(fd);
        return 1;
    }
    
    read(fd, temp, templen);
    
    if(lseek(fd, offset, SEEK_SET) == -1) {
        perror("lseek error");
        close(fd);
        return 1;
    }

    write(fd, temp, templen);

    if(truncate(argv[1], filelen - deletebyte) == -1) {
        perror("truncate error");
        close(fd);
        return 1;
    }

    puts("file delete success");

    close(fd);
    free(temp);
    return 0;
}
