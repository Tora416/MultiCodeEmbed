











#include "get_next_line.h"

int pre_work(int fd, char **rest, char **line)
{
    char            *tmp;

    if (BUFFER_SIZE < 0 || !line || read(fd, NULL, 0) < 0)
        return (-1);
    *line = ft_strdup("");
    if (rest[fd] != '\0')
    {
        if (!has_nl(rest[fd]))
        {
            *line = ft_strjoin(*line, rest[fd]);
            rest[fd] = NULL;
        }
        else
        {
            *line = ft_strjoin(*line, ft_substr(rest[fd], 0,
                has_nl(rest[fd]) - rest[fd]));
            tmp = rest[fd];
            rest[fd] = ft_strdup(&rest[fd][has_nl(rest[fd]) - rest[fd] + 1]);
            free(tmp);
            return (1);
        }
    }
    return (2);
}

int get_next_line(int fd, char **line)
{
    int             re;
    char            *str;
    static  char    *rest[1024];

    re = 0;
    if ((re = pre_work(fd, rest, line)) < 2)
        return (re);
    str = (char *)malloc(BUFFER_SIZE + 1);
    while ((re = read(fd, str, BUFFER_SIZE)))
    {
        str[re] = '\0';
        if (!has_nl(str))
            *line = ft_strjoin(*line, str);
        else
        {
            *line = ft_strjoin(*line, ft_substr(str, 0, has_nl(str) - str));
            rest[fd] = ft_strdup(&str[has_nl(str) - str + 1]);
            free(str);
            return (1);
        }
        str = (char *)malloc(BUFFER_SIZE + 1);
    }
    free(str);
    return (0);
}
