#include "ft_ls.h"

// int     count_flag(char **av)
// {
//     int x;
//     int y;
//     int ret;
    
//     x = 1;
//     ret = 0;
//     while (av[x])
//     {
//         if (av[x][0] == '-')
//         {
//             y = 1;
//             while (av[x][y++])
//                 ret++;
//         }
//         x++;
//     }
//     return (ret);
// }
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
            ret = ft_strlen(&av[x][y]);
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
    printf("here = %d\n", *flags);
    if (!(ret = (char *)malloc(sizeof(char) * (*flags + 1))))
        exit(1);
    ret = convert_2d(ret, av);
    return (ret);
}

int     check_flags(t_ls *sp)
{
    int check;
    int x;

    x = 0;
    check = 0;
    while (x < sp->ls_flags)
	{
		sp->p_flags[x] == 'l' ? check += 1 : 0;
		sp->p_flags[x] == 'R' ? check += 1 : 0;
		sp->p_flags[x] == 'r' ?	check += 1 : 0;
		sp->p_flags[x] == 'a' ? check += 1 : 0;
		sp->p_flags[x] == 't' ? check += 1 : 0;
		sp->p_flags[x] == '1' ? check += 1 : 0;
		x++;
	}
	if (check != sp->ls_flags)
		return (-1);
	return (1);
}

t_ls_flags  *index_flag(t_ls *sp)
{
    int x;
    t_ls_flags      *fp;
    
    x = 0;
    if (!(fp = (t_ls_flags*)malloc(sizeof(t_ls_flags ))))
        exit(1);
    while (x < sp->ls_flags)
    {  
        sp->p_flags[x] == 'l' ? fp->l_long = 1 : 0;
        sp->p_flags[x] == 'R' ? fp->R_recur = 1 : 0;
        sp->p_flags[x] == 'r' ? fp->r_lex = 1 : 0;
        sp->p_flags[x] == 'a' ? fp->a_hidden = 1 : 0;
        sp->p_flags[x] == 't' ? fp->t_sort = 1 : 0;
        if (check_flags(sp) == -1)
            ft_putstr("ls: illegal option\n");
        x++;
    }
    return (fp);
}