#include "ft_ls.h"
#include <stdio.h>

int     count_flag(char **av)
{
    int x;
    int y;
    int ret;
    
    x = 1;
    ret = 0;
    while (av[x])
    {
        if (av[x][0] == '-')
        {
            y = 1;
            while (av[x][y])
            {
                ret++;
                y++;
            } 
        }
        x++;
    }
    return (ret);
}

char     *convert_flags(char **av, int *flags)
{
    int         x;
    int         y;
    int         z;
    char        *ret;
    if (!(*flags = count_flag(av)))
        return (NULL);
    if (!(ret = (char *)malloc(sizeof(&flags) + 1)))
        exit(1);
    x = 1;
    y = 0;
    while (av[x])
    {
        if (av[x][0] == '-')
        {
            z = 1;
            //start at 2nd char of 2d array and copy it into ret[y]
            if (av[x][z])
            {
                ret[y] = av[x][z];
                y++;
                z++;
            }
        }
           x++;
    }
    printf("%s\n", ret);
    return (ret);
}

// char    **get_dir(char **av, int dir)
// {

// }

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
        printf("%s\n", sp->p_dir[0]);
    }
    else
    {
        sp->p_flags = convert_flags(av, &sp->ls_flags);
        // sp->p_dir = get_dir(av, &sp->ls_dir);
        printf("%s\n", sp->p_flags);
    }
    return (0);
}