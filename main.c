#include "ft_ls.h"
// #include "libft/libft.h"
#include <stdio.h>

void	start_print(char *name, t_ls *sp, char *path)
{
	struct stat		*buf;
	struct passwd	*psswd;
	struct group	*grp;
	char			*tmp;

	if (!(buf = malloc(sizeof(struct stat))))
        exit(1);
	lstat(path, buf);
	psswd = getpwuid(buf->st_uid);
	grp = getgrgid(psswd->pw_gid);
	if (sp->fp->l_long == 1)
	{
		print_stat(buf);
		tmp = ctime(&buf->st_mtime);
		tmp[16] = '\0';
        //checks is st->mode is a special character or is its a block special file && prints it if it a block file
		if ((S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode)) && print_chr_blk(buf, psswd, grp))
			continue_chr_print(buf, tmp, name);
		else if (non_chr_blk(buf, psswd, grp))
			continue_nonchr_print(tmp, name);
	}
	else
		ft_printf("%s", name);
	free(buf);
}

// void    end_out(char *folder, t_ls_flags *fp, char *str)
// {
//     struct passwd   *password;
//     struct stat     *buf;
//     struct group    *grup;
//     char            *gold;

//     buf = malloc(sizeof(stat));
//     // if (!(buf = malloc(sizeof(stat))))
//     //     exit(1);
//     lstat(str, buf);
//     printf("here");
//     password = getpwuid(buf->st_uid);
//     printf("here1");
//     grup = getgrgid(password->pw_gid);
//     printf("here2");
//     if (fp->l_long == 1)
//     {
//         print_stat(buf);
//         //get time of last data modification
//         gold = ctime(&buf->st_mtime);
// 		gold[16] = '\0';
//         if ((S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode)) && print_chr_blk(buf, password, grup))
// 			continue_chr_print(buf, gold, folder);
// 		else if (non_chr_blk(buf, password, grup))
// 			continue_nonchr_print(gold, folder);
// 		ft_putstr("\n");
// 	}
// 	else
// 		printf("%s\n", folder);
//     free(buf);
// }

void    help_basic(t_ls *sp, char *str, char **folder, char *tmp, int x)
{
    while (folder[++x])
    {
        tmp = createpath(str, folder[x]);
        if (folder[x][0] != '.' && sp->fp->a_hidden != 1)
            start_print(folder[x], sp, tmp);
		if (sp->fp->a_hidden == 1)
            start_print(folder[x], sp, tmp);
		// free(folder[x]);
		// free(tmp);
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

void    ls_print(DIR *dir, t_ls *sp, int x)
{
    //open directory stream at path pointed to by sp->p_dir[x], by defauly it goes to the first entry in the directory, or aka the first directory in 2d array
    if (!(dir = opendir(sp->p_dir[x])))
        check_error(sp->p_dir[x]);
    else if (sp->ls_dir > 1)
    {
        ft_printf("%s:\n", sp->p_dir[x]);
        ls_basic(sp->p_dir[x], sp, -1);
    }
    else
        ls_basic(sp->p_dir[x], sp, -1);
    //send opened directory, flags and starting point to print
    closedir(dir);
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
        if (sp->fp->R_recur == 1)
        {
            Recur_print(dir, sp, 0);
        }
        else
            ls_print(dir, sp, x);
        x++;
    }
    // free_dir(sp);
    // x = 0;
    while (sp->p_dir[x])
	{
		free(sp->p_dir[x]);
		x++;
	}
	free(sp->p_dir[x]);
	free(sp->p_flags);
	free(sp);
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