#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {

    int rfd, wfd;
    char buffer[101];
    size_t count;

    if((rfd = open(argv[1], O_RDONLY)) == -1) {
        perror("rfd file opening error");
        return 1;
    }
    if((wfd = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0751)) == -1) {
        perror("wfd file openning error");
        return 1;
    }
    while((count = read(rfd, buffer, 100)) > 0) {
        if(write(wfd, buffer, count) < count) {
            perror("file copying error");
            close(rfd);
            close(wfd);
            return 1;
        }
    }

    puts("file copying success");

    close(rfd);
    close(wfd);

    return 0;
}
