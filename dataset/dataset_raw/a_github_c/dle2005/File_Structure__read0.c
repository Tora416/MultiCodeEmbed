#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    char c;
    int rfd;
    int offset = atoi(argv[2]);
    int readbyte = atoi(argv[3]);
    int count = 0;

    if((rfd = open(argv[1], O_RDONLY)) == -1) {
        perror("file openning error");
        return 1;
    }

    if(lseek(rfd, offset, SEEK_SET) == -1) {
        perror("lseek error");
        close(rfd);
        return 1;
    }
    
    while(read(rfd, &c, 1) !=0 && count < readbyte) {
        write(1, &c, 1);
        count++;
    }

    puts("file read success");

    close(rfd);
    
    return 0;
}
    


