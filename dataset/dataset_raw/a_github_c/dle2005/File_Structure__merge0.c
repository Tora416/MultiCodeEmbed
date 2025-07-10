#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int wfd, rfd;
    char buffer[101];
    size_t count;

    if((wfd = open(argv[1], O_RDWR)) == -1) {
        perror("file1 openning error");
        return 1;
    }

    if((rfd = open(argv[2], O_RDONLY)) == -1) {
        perror("file2 openning error");
        return 1;
    }

    if(lseek(wfd, 0, SEEK_END) == -1) {
        perror("lseek END error");
        close(rfd);
        close(wfd);
        return 1;
    }

    while((count = read(rfd, buffer, 100)) > 0) {
        if(write(wfd, buffer, count) < count) {
            perror("file merge error");
            close(rfd);
            close(wfd);
            return 1;
        }
    }

    puts("file merge success");

    close(rfd);
    close(wfd);

    return 0;
}
