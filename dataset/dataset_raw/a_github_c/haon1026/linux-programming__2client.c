


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int main(int argc, char *argv[])
{
    int clnt_sock = socket(AF_INET, SOCK_STREAM, 0);
    if(clnt_sock == -1)
    {
        sys_err("socket() error");
    }

    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(9999);
    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);
    int ret = connect(clnt_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(ret != 0)
    {
        sys_err("connect() error");
    }

    int counter = 10;
    char buf[BUFSIZ];
    while(counter--)
    {
        write(clnt_sock, "hello\n", 6);
        ret = read(clnt_sock, buf, sizeof(buf));
        write(STDOUT_FILENO, buf, ret);
        sleep(1);
    }

    close(clnt_sock);

    return 0;
}