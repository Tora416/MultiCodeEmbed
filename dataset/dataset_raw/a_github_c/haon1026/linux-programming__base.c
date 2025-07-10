


#include "base.h"

void sys_err(const char *str)
{
    perror(str);
    exit(1);
}

int Socket(int domain, int type, int protocol)
{
    int sockfd = socket(domain, type, protocol);
    if(sockfd == -1)
    {
        sys_err("socket() error");
    }
    return sockfd;
}

int Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int ret = bind(sockfd, addr, addrlen);
    if(ret == -1)
    {
        sys_err("bind() error");
    }
    return ret;
}

int Listen(int sockfd, int backlog)
{
    int ret = listen(sockfd, backlog);
    if(ret == -1)
    {
        sys_err("listen() error");
    }
    return ret;
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int clnt_sock;
    while((clnt_sock = accept(sockfd, addr, addrlen)) == -1)
    {
        if(errno == EINTR)      
            continue;
        else
            sys_err("accept() error");
    }
    return clnt_sock;
}

int Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int ret = connect(sockfd, addr, addrlen);
    if(ret == -1)
    {
        sys_err("connect() error");
    }
    return ret;
}

ssize_t Read(int fd, void *buf, size_t count)
{
    int ret;
    while((ret = read(fd, buf, count)) == -1)
    {                                           
        if(errno == EINTR)                      
            continue;                           
        else
            sys_err("read() error");
    }
    return ret;
}

ssize_t Write(int fd, const void *buf, size_t count)
{
    int ret;
    while((ret = write(fd, buf, count)) == -1)
    {
        if(errno == EINTR)
            continue;
        else
            sys_err("write() error");
    }
    return ret;
}

int Close(int fd)
{
    int ret = close(fd);
    if(ret == -1)
    {
        sys_err("close() error");
    }
    return ret;
}