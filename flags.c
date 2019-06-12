/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 07:49:59 by jawatter          #+#    #+#             */
/*   Updated: 2019/06/09 23:48:02 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				count_flag(char **av)
{
	int			j;
	int			x;
	int			ret;

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

char			*convert_2d(char *ret, char **av)
{
	int			x;
	int			y;
	int			z;

	x = 1;
	y = 0;
	while (av[x])
	{
		if (av[x][0] == '-')
		{
			z = 1;
			while (av[x][z])
				ret[y++] = av[x][z++];
		}
		x++;
	}
	return (ret);
}

char			*convert_flags(char **av, int *flags)
{
	char		*ret;

	*flags = count_flag(av);
	if (!(ret = (char *)malloc(sizeof(char) * (*flags + 1))))
		exit(1);
	ret = convert_2d(ret, av);
	return (ret);
}

int				check_flags(t_ls *sp)
{
	int			check;
	int			x;

	x = 0;
	check = 0;
	while (x < sp->ls_flags)
	{
		L(sp->p_flags[x]) ? check += 1 : 0;
		R(sp->p_flags[x]) ? check += 1 : 0;
		S_R(sp->p_flags[x]) ? check += 1 : 0;
		A(sp->p_flags[x]) ? check += 1 : 0;
		T(sp->p_flags[x]) ? check += 1 : 0;
		sp->p_flags[x] == '1' ? check += 1 : 0;
		x++;
	}
	if (check != sp->ls_flags)
		return (-1);
	return (1);
}

t_ls_flags		*index_flag(t_ls *sp)
{
	int			x;

	x = 0;
	if (!(sp->fp = (t_ls_flags*)malloc(sizeof(t_ls_flags))))
		exit(1);
	while (x < sp->ls_flags)
	{
		L_FLIP(sp->p_flags, sp->fp->l_long, x);
		R_FLIP(sp->p_flags, sp->fp->r_recur, x);
		S_R_FLIP(sp->p_flags, sp->fp->r_lex, x);
		A_FLIP(sp->p_flags, sp->fp->a_hidden, x);
		T_FLIP(sp->p_flags, sp->fp->t_sort, x);
		if (check_flags(sp) == -1)
		{
			ft_putstr("ls: illegal option\n");
			exit(1);
		}
		x++;
	}
	return (sp->fp);
}
