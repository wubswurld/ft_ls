#include "ft_ls.h"

void    check_error(char *str)
{
    printf("ls: ");
    printf("%s: ", str);
    printf("No such file or directory\n");
    exit(1);
}

int     count_dir(char **av)
{
    int x;
    int ret;

    x = 1;
    ret = 0;
    while (av[x])
        if (av[x++][0] != '-')
            ret++;
    return (ret);
}


char    **get_dir(char **av, int *ls_dirs)
{
	char	**ret;
    int		x;
	int		j;
    
    //get number of directories
	*ls_dirs = count_dir(av);
     //if no directory set directories to 1 for '.'
	if (*ls_dirs <= 0 && (ret = (char**)malloc(sizeof(char*) * 2)))
	{
		ret[0] = ft_strdup(".");
		ret[1] = NULL;
		*ls_dirs = 1;
		return (ret);
	}
    //malloc string to for size of directories
    if (!(ret = (char**)malloc(sizeof(char*) * (*ls_dirs + 1))))
        exit(1);
	x = 1;
	j = 0;
    //put directories into 2d array
    while (av[x])
    {
		if(av[x][0] != '-')
			ret[j++] = ft_strdup(av[x]);
        x++;
    }
    //dir is at max size of directory so set that point to null
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
		if (sp->fp->a_hidden == 1 && (tmp = createpath(str, folder[i])) && (lstat(tmp, buf)))
		{
			free(tmp);
			ret += buf->st_blocks;
		}
		else if (folder[i][0] != '.' && sp->fp->a_hidden != 1 && (tmp = createpath(str, folder[i])))
		{
			lstat(tmp, buf);
			free(tmp);
			ret += buf->st_blocks;
		}
	}
	free(buf);
	return (ret);
}