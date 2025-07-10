#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int fd;
    int offset = atoi(argv[2]);
    int inputlen = strlen(argv[3]);
    int  filelen, diflen; 
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

    diflen = filelen - offset;
    temp = malloc(sizeof(char) * diflen + 1);

    if(lseek(fd, offset, SEEK_SET) == -1) {
        perror("lseek offset error");
        close(fd);
        return 1;
    }

    read(fd, temp, diflen);


    if(lseek(fd, offset, SEEK_SET) == -1) {
        perror("lseek offset error");
        close(fd);
        return 1;
    }

    write(fd, argv[3], inputlen);
    write(fd, temp, diflen);

    puts("file insert success");

    close(fd);
    free(temp);
    return 0;
}    
