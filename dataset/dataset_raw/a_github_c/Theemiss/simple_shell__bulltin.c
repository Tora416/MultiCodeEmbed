#include "shell.h"

void  exit_bul(char **cmd, char *input, char **argv, int c)
{
    int statue, i = 0;

    if (cmd[1] == NULL)
    {
        free(input);
        free(cmd);
        exit(EXIT_SUCCESS);
    }
    while (cmd[1][i])
    {
        if (_isalpha(cmd[1][i++]) != 0)
        {
            _prerror(argv, c, cmd);
            break;
        }
        else
        {
            statue = _atoi(cmd[1]);
            free(input);
            free(cmd);
            exit(statue);
        }
    }
}



int change_dir(char **cmd, __attribute__((unused))int er)
{
    int value = -1;
    char cwd[PATH_MAX];

    if (cmd[1] == NULL)
        value = chdir(getenv("HOME"));
    else if (_strcmp(cmd[1], "-") == 0)
    {
        value = chdir(getenv("OLDPWD"));
    }
    else
        value = chdir(cmd[1]);

    if (value == -1)
    {
        perror("hsh");
        return (-1);
    }
    else if (value != -1)
    {
        getcwd(cwd, sizeof(cwd));
        setenv("OLDPWD", getenv("PWD"), 1);
        setenv("PWD", cwd, 1);
    }
    return (0);
}

int dis_env(__attribute__((unused)) char **cmd, __attribute__((unused)) int er)
{
size_t i;
    int len;

    for (i = 0; environ[i] != NULL; i++)
    {
        len = _strlen(environ[i]);
        write(1, environ[i], len);
        write(STDOUT_FILENO, "\n", 1);
    }
    return (0);
}

int display_help(char **cmd, __attribute__((unused))int er)
{
    int fd, fw, rd = 1;
    char c;

    fd = open(cmd[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error");
        return (0);
    }
    while (rd > 0)
    {
        rd = read(fd, &c, 1);
        fw = write(STDOUT_FILENO, &c, rd);
        if (fw < 0)
        {
            return (-1);
        }
    }
    _putchar('\n');
    return (0);
}

int echo_bul(char **cmd, int st)
{
    char *path;
    unsigned int  pid = getppid();

    if (_strncmp(cmd[1], "$?", 2) == 0)
    {
        print_number_in(st);
        PRINTER("\n");
    }
    else if (_strncmp(cmd[1], "$$", 2) == 0)
    {
        print_number(pid);
        PRINTER("\n");

    }
    else if (_strncmp(cmd[1], "$PATH", 5) == 0)
    {
        path = _getenv("PATH");
        PRINTER(path);
        PRINTER("\n");
        free(path);

    }
    else
        return (print_echo(cmd));

    return (1);
}
