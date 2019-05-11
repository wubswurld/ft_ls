#include "ft_ls.h"
// #include "libft/libft.h"
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
            while (av[x][y++])
                ret++;
        }
        x++;
    }
    return (ret);
}
char      *convert_2d(char *ret, char **av) 
{
    int x;
    int y;
    int z;

    x = 1;
    y = 0;
    while (av[x])
    {
        if (av[x][0] == '-')
        {
            z = 1;
            //start at 2nd char of 2d array and copy it into ret[y]
            while (av[x][z])
                ret[y++] = av[x][z++];
        }
        x++;
    }
    return (ret);
}

char     *convert_flags(char **av, int *flags)
{
    char        *ret;
    *flags = count_flag(av);
    if (!(ret = (char *)malloc(sizeof(char) * (*flags + 1))))
        exit(1);
    ret = convert_2d(ret, av);
    return (ret);
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
    while (av[x])
    {
        if (av[x][0] != '-')
            ret[y++] = ft_strdup(av[x]);
        x++;
    }
    ret[*dir] = NULL;
    return (ret);
}

t_ls_flags  *index_flag(t_ls *sp)
{
    int x;
    t_ls_flags      *fp;
    
    x = 0;
    if (!(fp = (t_ls_flags*)malloc(sizeof(t_ls_flags))))
        exit(1);
    while (x < sp->ls_flags)
    {
        if (sp->p_flags[x] == 'l')
            fp->l_long = 1;
        x++;    
    }
    return (fp);
}


void    ft_ls(t_ls *sp)
{
    DIR     *dir;
    t_ls_flags  *fp;
    int        x;

    x = 0; 
    dir = NULL;
    fp = index_flag(sp);
    printf("%d\n", fp->l_long);
}

int     main(int ac, char **av) 
{
    t_ls      *sp;

    if (!(sp = (t_ls *)malloc(sizeof(t_ls))))
            exit(1);
    if (ac < 2)
    {
        //if command is 'ls' with no flags or arguments set directory to . and no flags
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
        sp->p_flags = convert_flags(av, &sp->ls_flags);
        sp->p_dir = get_dir(av, &sp->ls_dir);
        printf("directory: %s\n", *sp->p_dir);
        printf("flags: %s\n", sp->p_flags);
    }
    ft_ls(sp);
    return (0);
}