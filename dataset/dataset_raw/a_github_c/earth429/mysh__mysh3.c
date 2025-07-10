#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
    int i;
    int childpid;
    int status;
    char buf[BUFSIZ];
    char prompt[16] = "prompt> ";
    char **ap, *argv[10], *inputstring;
    printf("%s", prompt);
    while (fgets(buf, BUFSIZ, stdin) != NULL) {
        buf[strlen(buf) - 1] = '\0'; 
        inputstring = buf;
        
        for (ap = argv; (*ap = strsep(&inputstring, " \t")) != NULL;)
            if (**ap != '\0')
                if (++ap >= &argv[10])
                    break;
        
        
        if ((childpid = fork()) == 0) {
            
            execv(argv[0], argv);
            exit(0);
        } else {
            wait(&status);
        }
        printf("%s", prompt);
    }
}