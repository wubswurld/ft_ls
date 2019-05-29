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

char    **ls_sort(DIR *dir, t_ls *sp, int x)
{
    struct dirent *d_stream;
    char   **ret;

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
    return (ret);
}