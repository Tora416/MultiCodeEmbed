#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void sigint_catcher() { 
    kill(getpid() + 1, SIGINT); 
}

int main()
{
    int i;
    int childpid;
    int status;
    char buf[BUFSIZ];
    char dirbuf[BUFSIZ];
    char arrow[4] = "> "; 
    char **ap, *argv[10], *inputstring;
    getcwd(dirbuf, BUFSIZ); 
    printf("%s", dirbuf);   
    printf("%s", arrow);
    signal(SIGINT, sigint_catcher); 
    while (fgets(buf, BUFSIZ, stdin) != NULL) {
        buf[strlen(buf) - 1] = '\0'; 
        inputstring = buf;
        
        for (ap = argv; (*ap = strsep(&inputstring, " \t")) != NULL;)
            if (**ap != '\0')
                if (++ap >= &argv[10])
                    break;
        
        if (strcmp(argv[0], "k") == 0) { 
            kill(atoi(argv[1]), SIGINT); 
        } else if (strcmp(argv[0], "s") == 0) { 
            kill(atoi(argv[1]), SIGSTOP); 
        } else if (strcmp(argv[0], "c") == 0) { 
            kill(atoi(argv[1]), SIGCONT); 
        } else if (strcmp(argv[0], "cd") == 0) { 
            if (argv[1] == NULL) { 
                chdir(getenv("HOME")); 
            } else {
                chdir(argv[1]); 
            }
        } else if (strcmp(argv[0], "exit") == 0) { 
            exit(0); 
        } else if ((childpid = fork()) == 0) { 
            
            execv(argv[0], argv); 
            exit(0); 
        } else {
            
            wait(&status); 
            printf("status:%04x\n", status); 
        }
        getcwd(dirbuf, BUFSIZ); 
        printf("%s", dirbuf);   
        printf("%s", arrow);
    }
}