#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include<string.h>
void listFilesRecursively(char *path);


int main()
{
    
    char path[100];

    
    printf("Enter path to list files: ");
    scanf("%s", path);

    listFilesRecursively(path);

    return 0;
}



void listFilesRecursively(char *basePath)
{
    char path[1000];
    struct dirent *dp;
    DIR *dir = opendir(basePath);

    
    if (!dir)
        return;

    while ((dp = readdir(dir)) != NULL)
    {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0)
        {
            printf("%s\n", dp->d_name);

            
            strcpy(path, basePath);
            strcat(path, "/");
            strcat(path, dp->d_name);

            listFilesRecursively(path);
        }
    }

    closedir(dir);
}
