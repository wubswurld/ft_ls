#include "ft_ls.h"

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

void    Recur_print(DIR *dir, t_ls *sp, int x)
{
    if (!(dir = opendir(sp->p_dir[x])))
        check_error(sp->p_dir[x]);
    else
        listdir(sp->p_dir[x], sp, x);
    closedir(dir);
}

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