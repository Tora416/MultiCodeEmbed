#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void sigint_catcher() { 
    printf("-----SIGINT was sent to the childprocess!-----\n");
    kill(getpid() + 1, SIGINT); 
}

int main()
{
    int i;
    int childpid;
    int status;
    char buf[BUFSIZ];
    char prompt[16] = "prompt> ";
    char **ap, *argv[10], *inputstring;
    printf("%s", prompt);
    signal(SIGINT, sigint_catcher); 
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
            printf("status:%04x\n", status); 
        }
        printf("%s", prompt);
    }
}