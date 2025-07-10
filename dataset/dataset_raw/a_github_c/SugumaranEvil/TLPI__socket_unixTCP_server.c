






int main()
{
    int soc_fd, bind_fd;
    int listen_fd, accept_fd;
    ssize_t read_fd;
    char buff[1024];

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;

    strcpy(addr.sun_path, PATHNAME);
    perror("strcpy");

    
    soc_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    perror("socket");

    
    bind_fd = bind(soc_fd, (struct sockaddr *) &addr, sizeof(struct sockaddr_un));
    perror("bind");

    
    listen_fd = listen(soc_fd, 11);
    perror("listen");

    
    accept_fd = accept(soc_fd, NULL, NULL);
    perror("accept");

    
    read_fd = read(accept_fd, buff, 30);
    perror("read");

    printf("Data from client\n");
    printf("==> %s\n",buff);

}
