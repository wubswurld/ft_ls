#include "ft_ls.h"

int     count_dir(char **av)
{
    int x;
    int ret;

    x = 1;
    ret = 0;
    while (av[x])
        if (NOT_EQ(av[x++][0], '-'))
            ret++;
    return (ret);
}


char    **get_dir(char **av, int *ls_dirs)
{
	char	**ret;
    int		x;
	int		j;

	*ls_dirs = count_dir(av);
	if (*ls_dirs <= 0 && (ret = (char**)malloc(sizeof(char*) * 2)))
	{
		ret[0] = ft_strdup(".");
		ret[1] = NULL;
		*ls_dirs = 1;
		return (ret);
	}
    if (!(ret = (char**)malloc(sizeof(char*) * (*ls_dirs + 1))))
        exit(1);
	x = 1;
	j = 0;
    while (av[x])
    {
		if (NOT_EQ(av[x][0], '-'))
			ret[j++] = ft_strdup(av[x]);
        x++;
    }
    ret[*ls_dirs] = NULL;
	return (ret);
};

int		ls_directory(char **folder, t_ls *sp, char *str, int ret)
{
	struct stat		*buf;
	void			*tmp;
	int				i;

	if (!(buf = malloc(sizeof(struct stat))))
        exit(1);
	i = -1;
	ret = 0;
	while (folder[++i])
	{
		if (CH_FLAG(sp->fp->a_hidden) && (tmp = createpath(str, folder[i])) && (lstat(tmp, buf)))
		{
			free(tmp);
			ret += buf->st_blocks;
		}
		else if (NOT_EQ(folder[i][0], '.') && !CH_FLAG(sp->fp->a_hidden) && (tmp = createpath(str, folder[i])))
		{
			lstat(tmp, buf);
			free(tmp);
			ret += buf->st_blocks;
		}
		else if (CH_FLAG(sp->fp->l_long) && CH_FLAG(sp->fp->a_hidden))
			free(tmp);
	}
	free(buf);
	return (ret);
}