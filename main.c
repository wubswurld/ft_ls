#include "ft_ls.h"
#include <stdio.h>

int     convert_flags(char **av, int *flags)
{
    int         x;
    int         y;
    int         z;
    char        *ret;
    if (!(count_flag(av)))
        return (NULL);
    if (!(ret = (char *)malloc(sizeof(char) + 1)))
        exit(1);
    x = 1;
    y = 0;
    while (av[x])
    {
        if (av[x][0] == '-')
        {
            z = 1;
            //start at 2nd char of 2d array and copy it into ret[y]


        }
    }
}

int     main(int ac, char **av) 
{
    t_ls      *sp;

    if (!(sp = (t_ls *)malloc(sizeof(t_ls))))
            exit(1);
    if (ac < 2)
    {
        sp->ls_dir = 1;
        sp->ls_flags = 0;
        sp->p_flags = NULL;
        if (!(sp->p_dir = (char **)malloc(sizeof(char*) + 1)))
            exit(1);
        if (!(sp->p_dir[0] = (char *)malloc(sizeof(char) + 1)))
            exit(1);
        sp->p_dir[0][0] = '.';
        sp->p_dir[1] = NULL;
    }
    else
    {
        sp->p_flags = convert_flags(av, sp->ls_flags);
        printf("%s\n", sp->p_flags);
    }
    printf("%s\n", sp->p_dir[0]);
    return (0);
}