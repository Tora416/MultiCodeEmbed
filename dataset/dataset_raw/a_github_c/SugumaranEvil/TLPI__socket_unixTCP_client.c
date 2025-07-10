






int main()
{
    int soc_fd, bind_fd;
    int connect_fd;
    ssize_t write_fd;
    char buff[]="data from client\n";

    struct sockaddr_un addr;
    addr.sun_family = AF_UNIX;

    
    strcpy(addr.sun_path, PATHNAME);
    perror("strcpy");

    
    soc_fd = socket(AF_UNIX, SOCK_STREAM, 0);
    perror("socket");
    printf("Return value of Socket = %d\n",soc_fd);

    
    connect_fd = connect(soc_fd, (struct sockaddr *)&addr, sizeof(struct sockaddr_un));
    perror("connect");

    
    write_fd = write(soc_fd, buff, sizeof(buff));
    perror("write");

    close(soc_fd);
}
