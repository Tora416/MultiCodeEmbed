#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int fd;
    int offset = atoi(argv[2]);
    int len = strlen(argv[3]);

    if((fd = open(argv[1], O_RDWR)) == -1) {
        perror("rfd file openning error");
        return 1;
    }

    if(lseek(fd, offset, SEEK_SET) == -1) {
        perror("lseek error");
        close(fd);
        return 1;
    }

    write(fd, argv[3], len);

    puts("file overwrite success");

    close(fd);

    return 0;
}
