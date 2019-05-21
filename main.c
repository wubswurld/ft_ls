#include "ft_ls.h"
// #include "libft/libft.h"
#include <stdio.h>

char	*createpath(char *path, char *new_path)
{
	char	*info;

	info = (char*)malloc(sizeof(char) * (strlen(path) + strlen(new_path) + 2));
	ft_strcpy(info, path);
	ft_strcat(info, "/");
	ft_strcat(info, new_path);
	return (info);
}

int		totaldirs(char **folder, t_ls_flags *fp, char *str, int ret)
{
	struct stat		*filestat;
	void			*tmp;
	int				i;

	filestat = malloc(sizeof(struct stat));
	i = -1;
	ret = 0;
	while (folder[++i])
	{
		if (fp->a_hidden == 1 && (tmp = createpath(str, folder[i])) &&
			(lstat(tmp, filestat)))
		{
			free(tmp);
			ret += filestat->st_blocks;
		}
		else if (folder[i][0] != '.' && fp->a_hidden != 1 &&
			(tmp = createpath(str, folder[i])))
		{
			lstat(tmp, filestat);
			free(tmp);
			ret += filestat->st_blocks;
		}
	}
	free(filestat);
	return (ret);
}

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

char    **ls_sort(DIR *dir, t_ls_flags *fp, int x)
{
    struct dirent *d_stream;
    char   **ret;

    while ((d_stream = readdir(dir)) != 0)
        x++;
    // while ((d_stream = readdir(dir) != NULL))
    //     x++;
    printf("this is %d\n", x);
    rewinddir(dir);
    ret = (char **)malloc(sizeof(char *) * (x + 1));
    ret[x] = NULL;
    while ((d_stream = readdir(dir)) != NULL)
    {
        printf("%s\n", d_stream->d_name);
         ret[x++] = ft_strdup(d_stream->d_name);
    }
    ret[x] = NULL;
    fp->r_lex != 1 && fp->t_sort != 1 ? a_order(ret) : 0;
    return (ret);
}

void    ls_basic(char *str, t_ls_flags *fp, int x)
{
    DIR *dir;
    char **folder;
    char *tmp;
    int   ret;

    ret = 0;
    tmp = NULL;
    if (!(dir = opendir(str)))
        return;
    folder = ls_sort(dir, fp, 0);
    if (fp->l_long == 1)
    {
        ft_putstr("total ");
		printf("%s\n", ft_itoa(totaldirs(folder, fp, str, ret)));
		// ft_putendl(tmp);
		free(tmp);
    }
       printf("blah %d\n", x);
    // Close directory stream
    closedir(dir);
}

void    ls_print(DIR *dir, t_ls *sp, t_ls_flags *fp, int x)
{
    //open directory stream at path pointed to by sp->p_dir[x], by defauly it goes to the first entry in the directory
    if (!(dir = opendir(sp->p_dir[x])))
        check_error(sp->p_dir[x]);
    else if (sp->ls_dir > 1)
    {
        printf("%s\n", sp->p_dir[x]);
        ls_basic(sp->p_dir[x], fp, -1);
    }
    else {
        printf("%s\n", sp->p_dir[x]);
        ls_basic(sp->p_dir[x], fp, -1);
    }
    closedir(dir);
}

void    ft_ls(t_ls *sp)
{
    DIR     *dir;
    t_ls_flags  *fp;
    int        x;

    x = 0; 
    dir = NULL;
    //assign all flags a boolean value
    fp = index_flag(sp);
    while (x < sp->ls_dir)
    {
        if (fp->R_recur == 1)
            printf("ok");
        else    
            ls_print(dir, sp, fp, x);
        x++;
    }
    // int y;
    // y = 0;
    // while (sp->p_dir[y])
    //     free(sp->p_dir[y++]);
    // free(sp->p_dir);
    // free(sp->p_flags);
    // free(fp); 
}

int     main(int ac, char **av) 
{
    t_ls      *sp;

    if (!(sp = (t_ls *)malloc(sizeof(t_ls))))
            exit(1);
    if (ac < 2)
    {
        //if command is 'ls' with no flags or arguments set directory to . and no flags
        sp->ls_dir = 1;
        sp->ls_flags = 0;
        sp->p_flags = NULL;
        if (!(sp->p_dir = (char **)malloc(sizeof(char*) + 1)))
            exit(1);
        if (!(sp->p_dir[0] = (char *)malloc(sizeof(char) + 1)))
            exit(1);
        sp->p_dir[0][0] = '.';
        sp->p_dir[1] = NULL;
        printf("%d\n", sp->ls_dir);
    }
    else
    {
        //get flags as string
        sp->p_flags = convert_flags(av, &sp->ls_flags);
        sp->p_dir = get_dir(av, &sp->ls_dir);
    }
    ft_ls(sp);
    return (0);
}