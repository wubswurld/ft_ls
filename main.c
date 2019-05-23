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
		if ((S_ISCHR(buf->st_mode) || S_ISBLK(buf->st_mode)) && print_chr_blk(buf, psswd, grp))
			continue_chr_print(buf, tmp, name);
		else if (non_chr_blk(buf, psswd, grp))
			continue_nonchr_print(tmp, name);
	}
	else
		printf("%s\n", name);
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
		free(folder[x]);
		free(tmp);
    }
}

void    ls_basic(char *str, t_ls *sp, int x)
{
    DIR *dir;
    char **folder;
    char *tmp;
    int   ret;

    ret = 0;
    if (!(dir = opendir(str)))
        return;
    folder = ls_sort(dir, sp, 0);
    if (sp->fp->l_long == 1)
    {
        // ft_putstr("total ");
	    tmp = ft_itoa(ls_directory(folder, sp, str, ret));
		// ft_putendl(tmp);
        printf("total %s\n", tmp);
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
    //open directory stream at path pointed to by sp->p_dir[x], by defauly it goes to the first entry in the directory
    if (!(dir = opendir(sp->p_dir[x])))
        check_error(sp->p_dir[x]);
    else if (sp->ls_dir > 1)
    {
        printf("%s:\n\n", sp->p_dir[x]);
        ls_basic(sp->p_dir[x], sp, -1);
    }
    else
        ls_basic(sp->p_dir[x], sp, -1);
    closedir(dir);
}

void    ft_ls(t_ls *sp)
{
    DIR     *dir;
    // t_ls_flags  *fp;
    int        x;

    x = 0; 
    dir = NULL;
    //assign all flags a boolean value
    // fp = index_flag(sp);
    sp->fp = index_flag(sp);
    printf("%d\n", sp->fp->l_long);
    while (x < sp->ls_dir)
    {
        if (sp->fp->R_recur == 1)
            printf("ok");
        else
            ls_print(dir, sp, x);
        // else
        //     ls_print(dir, sp, fp, x);
        x++;
    }
    // free_dir(fp, sp);
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