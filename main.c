#include "ft_ls.h"
#include <stdio.h>

void    help_basic(t_ls *sp, char *str, char **folder, char *tmp, int x)
{
    while (folder[++x])
    {
        tmp = createpath(str, folder[x]);
        if (tmp == NULL)
            return ;
        if (folder[x][0] != '.' && sp->fp->a_hidden != 1)
            start_print(folder[x], sp, tmp);
		if (sp->fp->a_hidden == 1)
            start_print(folder[x], sp, tmp);
        if (folder[x])
            free(folder[x]);
	    free(tmp);
    }
}

void    help_recur(t_ls *sp, char *str, char **folder)
{
    char    *tmp;
    int     x;

    x = 0;
    while (folder[x])
    {
        tmp = createpath(str, folder[x]);
        if (folder[x][0] != '.' && sp->fp->a_hidden != 1)
            start_print(folder[x], sp, tmp);
		if (sp->fp->a_hidden == 1)
            start_print(folder[x], sp, tmp);
		// if (folder[x])
            // free(folder[x]);
		// free(tmp);
        x++;
    }
}

void    ls_basic(char *str, t_ls *sp, int x)
{
    DIR *dir;
    char **folder;
    char *tmp;
    int   ret;

    ret = 0;
    //str is path and we are opening that directory
    if (!(dir = opendir(str)))
        return;
    folder = ls_sort(dir, sp, 0);
    if (sp->fp->l_long == 1)
    {
	    tmp = ft_itoa(ls_directory(folder, sp, str, ret));
        ft_printf("total %s", tmp);
		free(tmp);
    }
    else
        tmp = NULL;
    help_basic(sp, str, folder, tmp, x);
    // Close directory stream
    closedir(dir);
    free (folder);
}

void	rec_perms(char **fol, char *path, t_ls *sp)
{
	int		i;
	char	*tmp;
    DIR     *dir;

	i = 0;
    dir = NULL;
	while (fol[i])
	{
		tmp = createpath(path, fol[i]);
		if (fol[i][0] != '.' && sp->fp->a_hidden != 1)
			listdir(tmp, sp, 0);
		else if (strcmp(fol[i], ".") != 0 && strcmp(fol[i], "..") != 0 && sp->fp->a_hidden == 1)
			listdir(tmp, sp, 0);
		i++;
        // free(tmp);
	}
}

void listdir(char *str, t_ls *sp, int x)
{
    DIR *dir;
    char **folder;
    char *tmp;

    if (!(dir = opendir(str)))
        return ;
    ft_printf("\n%s", str);
    folder = ls_sort(dir, sp, 0);
    if (sp->fp->l_long == 1 && sp->p_dir[x])
    {
        tmp = ft_itoa(ls_directory(folder, sp, str, 0));
        ft_printf("total %s", tmp);
	    free(tmp);
    }
    help_recur(sp, str, folder);
    closedir(dir);
    if (!(dir = opendir(sp->p_dir[x])))
        check_error(sp->p_dir[x]);
    rec_perms(folder, str, sp);
    closedir(dir);
}

void    Recur_print(DIR *dir, t_ls *sp, int x)
{
    if (!(dir = opendir(sp->p_dir[x])))
        check_error(sp->p_dir[x]);
    else
        listdir(sp->p_dir[x], sp, x);
    closedir(dir);
}

void    ft_ls(t_ls *sp)
{
    DIR     *dir;
    int        x;

    x = 0; 
    dir = NULL;
    //assign all flags a boolean value
    sp->fp = index_flag(sp);
    while (x < sp->ls_dir)
    {
        (sp->fp->R_recur == 1) ? Recur_print(dir, sp, 0) : ls_print(dir, sp, x);
        x++;
    }
    free_dir(sp);
}

int     main(int ac, char **av) 
{
    t_ls      *sp;

    //malloc entire struct
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
    }
    else
    {
        //get flags as string
        sp->p_flags = convert_flags(av, &sp->ls_flags);
        //get directory as 2d array in struct
        sp->p_dir = get_dir(av, &sp->ls_dir);
    }
    ft_ls(sp);
    // free(sp);
    return (0);
}