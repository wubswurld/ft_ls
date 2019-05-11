#include "ft_ls.h"
// #include "libft/libft.h"
#include <stdio.h>

int     count_dir(char **av)
{
    int x;
    int ret;

    x = 1;
    ret = 0;
    while (av[x])
    {
        if (av[x][0] != '-')
            ret++;
        x++;
    }
    return (ret);
}

char    **get_dir(char **av, int *dir)
{
    char    **ret;
    int     x;
    int     y;
    *dir = count_dir(av);
    //if no directory set directories to 1 for '.'
    if (*dir <= 0 && (ret = (char **)malloc(sizeof(char *) * 2)))
    {
        ret[0] = ".";
        ret[1] = NULL;
        *dir = 1;
        return (ret);
    }
    if (!(ret = (char **)malloc(sizeof(char) * (*dir + 1))))
        exit(1);
    x = 1;
    y = 0;
    while (av[x])
    {
        if (av[x][0] != '-')
            ret[y++] = ft_strdup(av[x]);
        x++;
    }
    ret[*dir] = NULL;
    return (ret);
}

void    ls_print(char *str, t_ls_flags *fp, int x)
{  
	DIR		*dir;
	char	**fol;
	char	*tmp;
	int		result;

	result = 0;
	dir = opendir(str);
	fol = sort_folders(dir, fp, 0);
	if (flags->l == 1)
	{
		ft_putstr("total ");
		tmp = ft_itoa(totaldirs(fol, flags, str, result));
		ft_putendl(tmp);
		free(tmp);
	}
	while (fol[++x])
	{
		tmp = createpath(str, fol[x]);
		(fol[x][0] != '.' && fp->a_hidden != 1) ? sps(fol[x], fp, tmp) : 0;
		(fp->a_hidden == 1) ? sps(fol[i], flags, tmp) : 0;
		free(fol[i]);
		free(tmp);
	}
	closedir(dir);
	free(fol);
}

void    ls_start(DIR *dir, t_ls *sp, t_ls_flags *fp, int x)
{
    // printf("%s\n", sp->p_dir[x]);
    if (!(dir = opendir(sp->p_dir[x])))
    {
        printf("ls: ");
        printf("%s: ", str);
        printf("No such file or directory\n");    
    }
    else if (sp->ls_dir > 1)
    {
        ft_putendl(sp->p_dir[x]);
    }
    else 
    {
        ls_print(sp->p_dir[x], fp, -1);
    }
}

void    ft_ls(t_ls *sp)
{
    DIR     *dir;
    t_ls_flags  *fp;
    int        x;

    x = 0; 
    dir = NULL;
    fp = index_flag(sp);
    while (x < sp->ls_dir)
    {
        if (fp->R_recur == 1)
            printf("ok");
        else    
            ls_start(dir, sp, fp, x);
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
        //malloc entire 2d array
        if (!(sp->p_dir = (char **)malloc(sizeof(char*) + 1)))
            exit(1);
        //malloc space neccessary for '.'
        if (!(sp->p_dir[0] = (char *)malloc(sizeof(char) + 1)))
            exit(1);
        sp->p_dir[0][0] = '.';
        sp->p_dir[1] = 0;
    }
    else
    {
        //get flags as string
        sp->p_flags = convert_flags(av, &sp->ls_flags);
        sp->p_dir = get_dir(av, &sp->ls_dir);
        printf("directory: %s\n", *sp->p_dir);
        printf("flags: %s\n", sp->p_flags);
    }
    ft_ls(sp);
    return (0);
}