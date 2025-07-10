

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

void isFile(char *filename);

void readDir(char *dir)
{
    
    DIR *dp = opendir(dir);
    if(dp == NULL)
    {
        perror("opendir error");
        return;
    }

    
    char path[256] = {0};
    struct dirent *sdp;
    while((sdp = readdir(dp)) != NULL)
    {
        if(strcmp(sdp->d_name, ".") == 0 || strcmp(sdp->d_name, "..") == 0)
            continue;
        
        
        sprintf(path, "%s/%s", dir, sdp->d_name);
        
        isFile(path);
    }

    closedir(dp);
    return;
}

void isFile(char *filename)
{
    
    struct stat buf;
    int ret = stat(filename, &buf);
    if(ret == -1)
    {
        perror("stat error");
        return;
    }

    
    if(S_ISDIR(buf.st_mode))
    {
        readDir(filename);
    }

    
    printf("%s\t%ld\n", filename, buf.st_size);

    return;
}

int main(int argc, char *argv[])
{
    
    if(argc == 1)
    {
        isFile(".");
    }
    else
    {
        isFile(argv[1]);
    }

    return 0;
}