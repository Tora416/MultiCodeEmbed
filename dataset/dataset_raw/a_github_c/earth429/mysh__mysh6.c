#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void sigint_catcher() { 
    kill(getpid() + 1, SIGINT); 
}

int main()
{
    int i;
    int childpid, status; 
    int pipe_fd[2], pipe_position; 
    int chpid1, chpid2, status1, status2; 
    int pipe_flag = 0; 
    char dirbuf[BUFSIZ]; 
    char arrow[4] = "> "; 
    char buf[BUFSIZ]; 
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

        
        i = 0;
        pipe_flag = 0;
        
        while (argv[i] != NULL) {
            if (strcmp(argv[i], "|") == 0) { 
                pipe_position = i; 
                argv[i] = '\0'; 
                pipe_flag++; 
                break;
            }
            i++;
        }

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
        } else {  
            if (pipe_flag != 0) {
                
                if (pipe(pipe_fd) == -1) { 
                    perror("pipe");
                    exit(1);
                }
                if ((chpid1 = fork()) == 0) { 
                    
                    close(pipe_fd[0]); 
                    close(1); 
                    dup(pipe_fd[1]); 
                    execvp(argv[0], &argv[0]); 
                    exit(0); 
                } else if ((chpid2 = fork()) == 0) { 
                    
                    close(pipe_fd[1]); 
                    close(0); 
                    dup(pipe_fd[0]); 
                    execvp(argv[pipe_position + 1], &argv[pipe_position + 1]); 
                    exit(0); 
                } else {
                    
                    close(pipe_fd[0]); 
                    close(pipe_fd[1]); 
                    waitpid(chpid1, &status1, 0);    
                    waitpid(chpid2, &status2, 0);    
                    printf("status1:%04x\n", status1); 
                    printf("status2:%04x\n", status2); 
                }
            } else {
                
                if ((childpid = fork()) == 0) {
                    
                    execvp(argv[0], &argv[0]); 
                    exit(0); 
                } else {
                    
                    wait(&status); 
                    printf("status:%04x\n", status); 
                }
            }
        }
        getcwd(dirbuf, BUFSIZ); 
        printf("%s", dirbuf);   
        printf("%s", arrow);
    }
}