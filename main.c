#include "ft_ls.h"
// #include "libft/libft.h"
#include <stdio.h>

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

    // while ((d_stream = readdir(dir)) != 0)
    //     x++;
    while ((d_stream = readdir(dir)) != NULL)
        x++;
    rewinddir(dir);
    ret = (char **)malloc(sizeof(char *) * (x + 1));
    ret[x] = NULL;
    x = 0;
    while ((d_stream = readdir(dir)) != NULL)
    {
        // printf("%s\n", d_stream->d_name);
         ret[x] = ft_strdup(d_stream->d_name);
         x++;
    }
    ret[x] = NULL;
    // fp->r_lex != 1 && fp->t_sort != 1 ? a_order(ret) : 0;
    if (fp->r_lex != 1 && fp->t_sort != 1)
        a_order(ret);
    return (ret);
}

void	sps(char *name, t_ls_flags *flags, char *path)
{
	struct stat		*filestats;
	struct passwd	*psswd;
	struct group	*grp;
	char			*tmp;

	filestats = malloc(sizeof(struct stat));
	lstat(path, filestats);
	psswd = getpwuid(filestats->st_uid);
	grp = getgrgid(psswd->pw_gid);
	if (flags->l_long == 1)
	{
		print_stat(filestats);
		tmp = ctime(&filestats->st_mtime);
		tmp[16] = '\0';
		if ((S_ISCHR(filestats->st_mode) || S_ISBLK(filestats->st_mode))
			&& print_chr_blk(filestats, psswd, grp))
			continue_chr_print(filestats, tmp, name);
		else if (non_chr_blk(filestats, psswd, grp))
			continue_nonchr_print(tmp, name);
		ft_putstr("\n");
	}
	else
		ft_putendl(name);
	free(filestats);
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

void    help_basic(t_ls_flags *fp, char *str, char **folder, char *tmp, int x)
{
    while (folder[++x])
    {
        tmp = createpath(str, folder[x]);
        if (folder[x][0] != '.' && fp->a_hidden != 1)
            sps(folder[x], fp, tmp);
		if (fp->a_hidden == 1)
            sps(folder[x], fp, tmp);
		free(folder[x]);
		free(tmp);
    }
}

void    ls_basic(char *str, t_ls_flags *fp, int x)
{
    DIR *dir;
    char **folder;
    char *tmp;
    int   ret;

    ret = 0;
    tmp = NULL;
    dir = opendir(str);
    // if (!(dir = opendir(str)))
    //     return;
    folder = ls_sort(dir, fp, 0);
    // printf("%s\n", folder[x]);
    if (fp->l_long == 1)
    {
        ft_putstr("total ");
		printf("%s\n", ft_itoa(totaldirs(folder, fp, str, ret)));
		// ft_putendl(tmp);
		// free(tmp);
    }
    while (folder[++x])
    {
        tmp = createpath(str, folder[x]);
        if (folder[x][0] != '.' && fp->a_hidden != 1)
            sps(folder[x], fp, tmp);
		if (fp->a_hidden == 1)
            sps(folder[x], fp, tmp);
        // free(folder[x]);
	    // free(tmp);
    }
    // help_basic(fp, str, folder, tmp, x);
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
        // free(sp->p_dir[y++]);
    // free(sp->p_dir);
    // free(sp->p_flags);
    // free(fp); 
    free_dir(fp, sp);
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