/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printfiles.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 08:58:58 by jawatter          #+#    #+#             */
/*   Updated: 2019/06/08 09:11:05 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	ls_print(DIR *dir, t_ls *sp, int x)
{
	if (!OP(dir, sp->p_dir, x))
	{
		CHECK_ERROR(sp->p_dir[x]));
		return ;
	}
	else if (sp->ls_dir > 1)
	{
		ft_printf("%s:\n", sp->p_dir[x]);
		ls_basic(sp->p_dir[x], sp);
	}
	else
		ls_basic(sp->p_dir[x], sp);
	closedir(dir);
}

void	recur_print(DIR *dir, t_ls *sp, int x)
{
	if (!OP(dir, sp->p_dir, x))
	{
		CHECK_ERROR(sp->p_dir[x]));
		return ;
	}
	else
		listdir(sp->p_dir[x], sp, x);
	closedir(dir);
}

void	rec_perms(char **fol, char *path, t_ls *sp)
{
	int		i;
	char	*tmp;
	DIR		*dir;

	i = 0;
	dir = NULL;
	while (fol[i] != NULL)
	{
		tmp = createpath(path, fol[i]);
		if (fol[i] && NOT_EQ(fol[i][0], '.') && !CH_FLAG(sp->fp->a_hidden))
			listdir(tmp, sp, 0);
		else if (NOT_EQ(fol[i][0], '.') && CH_FLAG(sp->fp->a_hidden))
			listdir(tmp, sp, 0);
		i++;
		free(tmp);
	}
}

void	start_print(char *name, t_ls *sp, char *path)
{
	struct stat		*buf;
	struct passwd	*passwd;
	struct group	*grp;
	char			*tmp;

	buf = malloc(sizeof(struct stat));
	lstat(path, buf);
	if (CH_FLAG(sp->fp->l_long))
	{
		passwd = getpwuid(buf->st_uid);
		grp = getgrgid(passwd->pw_gid);
		print_stat(buf);
		tmp = ctime(&buf->st_mtime);
		tmp[16] = '\0';
		if ((S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode))&& printchr(buf, passwd, grp))
			ft_printf("%d%d%d %s%s", major(buf->st_rdev), 4, minor(buf->st_rdev), tmp + 4, name);
		else if (non_chr(buf, passwd, grp))
			ft_printf(" %s %s\n", tmp + 4, name);
	}
	else
		ft_printf("%s\n", name);
	free(buf);
}
