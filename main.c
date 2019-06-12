/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 15:53:58 by jawatter          #+#    #+#             */
/*   Updated: 2019/06/08 05:55:12 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_basic(char *str, t_ls *sp)
{
	DIR		*dir;
	char	**folder;
	char	*tmp;
	int		ret;

	ret = 0;
	if (!N_OP(dir, str))
		return ;
	folder = ls_sort(dir, sp);
	if (CH_FLAG(sp->fp->l_long))
	{
		tmp = ft_itoa(ls_directory(folder, sp, str, ret));
		ft_printf("total %s\n", tmp);
		free(tmp);
	}
	else
		tmp = NULL;
	help_basic(sp, str, folder, tmp);
	closedir(dir);
	free(folder);
}

void	listdir(char *str, t_ls *sp, int x)
{
	DIR		*dir;
	char	**folder;
	char	*extra;

	if (!N_OP(dir, str))
		return ;
	ft_putstr(str);
	ft_putchar('\n');
	folder = ls_sort(dir, sp);
	if (CH_FLAG(sp->fp->l_long) && sp->p_dir[x])
	{
		extra = ft_itoa(ls_directory(folder, sp, str, 0));
		ft_printf("total %s\n", extra);
		free(extra);
	}
	help_recur(sp, str, folder, x);
	closedir(dir);
	(!OP(dir, sp->p_dir, x)) ? CHECK_ERROR(sp->p_dir[x])) : 0;
	rec_perms(folder, str, sp);
	closedir(dir);
	free_folder(folder, 0);
}

void	ft_ls(t_ls *sp)
{
	DIR		*dir;
	int		x;

	x = 0;
	dir = NULL;
	sp->fp = index_flag(sp);
	while (x < sp->ls_dir)
	{
		(CH_FLAG(sp->fp->r_recur)) ? recur_print(dir, sp, 0) : ls_print(dir, sp, x);
		x++;
	}
	free_dir(sp);
}

int		main(int ac, char **av)
{
	t_ls	*sp;

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
		sp->p_flags = convert_flags(av, &sp->ls_flags);
		sp->p_dir = get_dir(av, &sp->ls_dir);
	}
	ft_ls(sp);
	return (0);
}
