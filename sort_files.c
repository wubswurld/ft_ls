#include "ft_ls.h"

char	**a_order(char **ret)
{
	int		x;
	char	*tmp;

	x = 1;
	while (ret[x])
	{
		//checks if we are at the end of the files and if the next item needs to go higher in order than the first
		//if we are at the end strcmp returns 0 or negative and we dont sort anymore
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
	int c;
	int d;

	c = 0;
	while (c < x - 1)
  	{
		d = 1;
		while (d < x - c - 1)
		{
			if (ft_strcmp(ret[d - 1], ret[d]) < 0)
			{
				tmp  = ret[d];
				ret[d] = ret[d-1];
				ret[d-1] = tmp;
			}
			d++;
		}
		c++;
	}
	return (ret);
}

int        validate_time(char *ret, char *tmp)
{
	struct stat		*buf;
	struct stat		*hold;
	double			tp;

	buf = malloc(sizeof(struct stat));
	hold = malloc(sizeof(struct stat));
	//get symbolic link from folders passed in and pull info from link
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

char 	**t_sort(char **ret)
{
	char	*tmp;
	int 	x;

	x = 0;
	while (ret[++x])
	{
		if (validate_time(ret[x - 1], ret[x]) < 0)
		{
			tmp = ret[x];
			ret[x] = ret[x-1];
			ret[x-1] = tmp;
		}
	}
	return (ret);
}

char    **ls_sort(DIR *dir, t_ls *sp, int x)
{
    struct dirent *d_stream;
	int z;
    char   **ret;

	z = 0;
	//get number of items of directory
    while ((d_stream = readdir(dir)) != NULL)
        x++;
	//set directory stream of DIR to the beginning of the directory
    rewinddir(dir);
    ret = (char **)malloc(sizeof(char *) * (x + 1));
    ret[x] = NULL;
    x = 0;
	//read directory and store the names of each item in the directory
    while ((d_stream = readdir(dir)) != NULL)
         ret[x++] = ft_strdup(d_stream->d_name);
    ret[x] = NULL;
    sp->fp->r_lex != 1 && sp->fp->t_sort != 1 ? a_order(ret) : 0;
	sp->fp->r_lex == 1 && sp->fp->t_sort != 1 ? rev_order(ret, x) : 0;
	sp->fp->t_sort == 1 ? t_sort(ret) : 0;
    return (ret);
}