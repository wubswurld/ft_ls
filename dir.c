/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 05:56:30 by jawatter          #+#    #+#             */
/*   Updated: 2019/06/09 23:44:42 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_stat(struct stat *buf)
{
	if (S_ISLNK(buf->st_mode))
		ft_putchar('l');
	else
		ft_putchar(S_ISDIR(buf->st_mode) ? 'd' : '-');
	ft_putchar((buf->st_mode & S_IRUSR) ? 'r' : '-');
	ft_putchar((buf->st_mode & S_IWUSR) ? 'w' : '-');
	ft_putchar((buf->st_mode & S_IXUSR) ? 'x' : '-');
	ft_putchar((buf->st_mode & S_IRGRP) ? 'r' : '-');
	ft_putchar((buf->st_mode & S_IWGRP) ? 'w' : '-');
	ft_putchar((buf->st_mode & S_IXGRP) ? 'x' : '-');
	ft_putchar((buf->st_mode & S_IROTH) ? 'r' : '-');
	ft_putchar((buf->st_mode & S_IWOTH) ? 'w' : '-');
	ft_putchar((buf->st_mode & S_IXOTH) ? 'x' : '-');
}

int		printchr(struct stat *buf, struct passwd *pw, struct group *gp)
{
	ft_printf("%3d ", buf->st_nlink);
	ft_printf("%s\t", pw->pw_name);
	ft_printf("%s%d,", gp->gr_name, 4);
	return (1);
}

int		non_chr(struct stat *buf, struct passwd *pw, struct group *gp)
{
	char	*fix;

	fix = ft_itoa(buf->st_size);
	ft_printf(" %d\t%s %s", buf->st_nlink, pw->pw_name, gp->gr_name);
	(ft_strlen(fix) <= 1) ? ft_printf("	  %s", fix) :
	ft_printf("%6lld", buf->st_size);
	free(fix);
	return (1);
}
