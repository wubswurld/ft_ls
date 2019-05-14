#include "ft_ls.h"

void    check_error(char *str)
{
    printf("ls: ");
    printf("%s: ", str);
    printf("No such file or directory\n");
}

int     count_dir(char **av)
{
    int x;
    int ret;

    x = 1;
    ret = 0;
    while (av[x])
    {
        if (av[x][0] != '-')
            ret++;
        x++;
    }
    return (ret);
}

char    **get_dir(char **av, int *dir)
{
    char    **ret;
    int     x;
    int     y;
    *dir = count_dir(av);
    //if no directory set directories to 1 for '.'
    if (*dir <= 0 && (ret = (char **)malloc(sizeof(char *) * 2)))
    {
        ret[0] = ".";
        ret[1] = NULL;
        *dir = 1;
        return (ret);
    }
    if (!(ret = (char **)malloc(sizeof(char) * (*dir + 1))))
        exit(1);
    x = 1;
    y = 0;
    //if their are flags or if there are no flags store the directory in ret
    while (av[x])
    {
        if (av[x][0] != '-')
            ret[y++] = ft_strdup(av[x]);
        x++;
    }
    ret[*dir] = NULL;
    return (ret);
}