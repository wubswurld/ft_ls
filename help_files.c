/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 08:07:30 by jawatter          #+#    #+#             */
/*   Updated: 2019/06/08 08:15:07 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	help_basic(t_ls *sp, char *str, char **folder, char *tmp)
{
	int x;

	x = -1;
	while (folder[++x])
	{
		tmp = createpath(str, folder[x]);
		if (tmp == NULL)
			return ;
		if (NOT_EQ(folder[x][0], '.') && !CH_FLAG(sp->fp->a_hidden))
			start_print(folder[x], sp, tmp);
		if (CH_FLAG(sp->fp->a_hidden))
			start_print(folder[x], sp, tmp);
	}
}

void	help_recur(t_ls *sp, char *str, char **folder, int x)
{
	char	*tmp;

	while (folder[x])
	{
		tmp = createpath(str, folder[x]);
		if (NOT_EQ(folder[x][0], '.') && !CH_FLAG(sp->fp->a_hidden))
			start_print(folder[x], sp, tmp);
		if (CH_FLAG(sp->fp->a_hidden))
			start_print(folder[x], sp, tmp);
		x++;
		free(tmp);
	}
}
