#include "ft_ls.h"

int     count_flag(char **av)
{
    int		j;
	int		x;
	int		ret;

	ret = 0;
	x = 1;
	while (av[x])
	{
		if (av[x][0] == '-')
		{
			j = 1;
			while (av[x][j])
			{
				ret++;
				j++;
			}
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
    //get # of flags
    *flags = count_flag(av);
    if (!(ret = (char *)malloc(sizeof(char) * (*flags + 1))))
        exit(1);
    //take argv and convert to 2d array
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

    x = 0;
    if (!(sp->fp = (t_ls_flags*)malloc(sizeof(t_ls_flags))))
        exit(1);
    //iterate through 2d array of flags and assign values
    while (x < sp->ls_flags)
    {  
        sp->p_flags[x] == 'l' ? sp->fp->l_long = 1 : 0;
        sp->p_flags[x] == 'R' ? sp->fp->R_recur = 1 : 0;
        sp->p_flags[x] == 'r' ? sp->fp->r_lex = 1 : 0;
        sp->p_flags[x] == 'a' ? sp->fp->a_hidden = 1 : 0;
        sp->p_flags[x] == 't' ? sp->fp->t_sort = 1 : 0;
        if (check_flags(sp) == -1)
        {
            ft_putstr("ls: illegal option\n");
            exit(1);
        }
        x++;
    }
    return (sp->fp);
}