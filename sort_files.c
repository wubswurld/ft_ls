/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 08:17:46 by jawatter          #+#    #+#             */
/*   Updated: 2019/06/08 08:26:41 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	**a_order(char **ret)
{
	int		x;
	char	*tmp;

	x = 1;
	while (ret[x])
	{
		if (ft_strcmp(ret[x - 1], ret[x]) > 0)
		{
			tmp = ret[x];
			ret[x] = ret[x - 1];
			ret[x - 1] = tmp;
			x = 1;
		}
		x++;
	}
	return (ret);
}

char	**rev_order(char **ret, int x)
{
	char	*tmp;
	int		c;
	int		d;

	c = 0;
	while (c < x - 1)
	{
		d = 1;
		while (d < x - c - 1)
		{
			if (ft_strcmp(ret[d - 1], ret[d]) < 0)
			{
				tmp = ret[d];
				ret[d] = ret[d - 1];
				ret[d - 1] = tmp;
			}
			d++;
		}
		c++;
	}
	return (ret);
}

int		validate_time(char *ret, char *tmp)
{
	struct stat		*buf;
	struct stat		*hold;
	double			tp;

	buf = malloc(sizeof(struct stat));
	hold = malloc(sizeof(struct stat));
	lstat(ret, buf);
	lstat(tmp, hold);
	tp = buf->st_mtime - hold->st_mtime;
	free(buf);
	free(hold);
	if (tp < 0)
		return (-1);
	else if (tp > 0)
		return (1);
	return (0);
}

char	**t_sort(char **ret)
{
	char	*tmp;
	int		x;

	x = 0;
	while (ret[++x])
	{
		if (validate_time(ret[x - 1], ret[x]) < 0)
		{
			tmp = ret[x];
			ret[x] = ret[x - 1];
			ret[x - 1] = tmp;
		}
	}
	return (ret);
}

char	**ls_sort(DIR *dir, t_ls *sp)
{
	struct dirent	*d_stream;
	int				z;
	char			**ret;
	int				x;

	z = 0;
	x = 0;
	while (RD(d_stream, dir))
		x++;
	rewinddir(dir);
	ret = (char **)malloc(sizeof(char *) * (x + 1));
	ret[x] = NULL;
	x = 0;
	while (RD(d_stream, dir))
		ret[x++] = ft_strdup(d_stream->d_name);
	ret[x] = NULL;
	!CH_FLAG(sp->fp->r_lex) && !CH_FLAG(sp->fp->t_sort) ? a_order(ret) : 0;
	CH_FLAG(sp->fp->r_lex) && !CH_FLAG(sp->fp->t_sort) ? rev_order(ret, x) : 0;
	CH_FLAG(sp->fp->t_sort) ? t_sort(ret) : 0;
	return (ret);
}
