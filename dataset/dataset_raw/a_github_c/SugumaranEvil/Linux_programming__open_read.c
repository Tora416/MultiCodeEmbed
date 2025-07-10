







#include "open_read.h"

int main()
{
    int file_des,c;
    ssize_t rd,wt;
    char arr[50],arr1[50];

    file_des = open("/home/sugu/Linux_Programming/file.txt",O_RDONLY,0640);

    perror("open");
    printf("File_descriptor %d\n",file_des);

    rd = read(file_des,arr,10);
    perror("read");
    printf("Read %d\n",rd);

    snprintf(arr1,10,"%s\n",arr);
    printf("%s\n",arr1);

    c = close(file_des);
    perror("close");
    printf("close%d\n",c);
}
