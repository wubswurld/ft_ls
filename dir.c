#include "ft_ls.h"

char	*createpath(char *path, char *new_path)
{
	char	*info;

	info = (char*)malloc(sizeof(char) * (strlen(path) + strlen(new_path) + 2));
	ft_strcpy(info, path);
	ft_strcat(info, "/");
	ft_strcat(info, new_path);
	return (info);
}

void    free_dir(t_ls *sp)
{
    int y;
    y = 0;
    while (sp->p_dir[y])
        free(sp->p_dir[y++]);
    free(sp->p_dir);
    free(sp->p_flags);
    free(sp); 
}


void    print_stat(struct stat *buf)
{
    if (S_ISLNK(buf->st_mode))
		ft_putchar('l');
	else
		ft_putchar((S_ISDIR(buf->st_mode)) ? 'd' : '-');
        ft_putchar((buf->st_mode & S_IRUSR) ? 'r' : '-');
        ft_putchar((buf->st_mode & S_IWUSR) ? 'w' : '-');
        ft_putchar((buf->st_mode & S_IXUSR) ? 'x' : '-');
        ft_putchar((buf->st_mode & S_IRGRP) ? 'r' : '-');
        ft_putchar((buf->st_mode & S_IWGRP) ? 'w' : '-');
        ft_putchar((buf->st_mode & S_IXGRP) ? 'x' : '-');
        ft_putchar((buf->st_mode & S_IROTH) ? 'r' : '-');
        ft_putchar((buf->st_mode & S_IWOTH) ? 'w' : '-');
        ft_putchar((buf->st_mode & S_IXOTH) ? 'x' : '-');
}

int		print_chr_blk(struct stat *buf, struct passwd *password, struct group *grup)
{
    printf("%3d ", buf->st_nlink);
    printf("%s\t", password->pw_name);
    printf("%s%d,", grup->gr_name, 4);
	return (1);
}

int		non_chr_blk(struct stat *buf, struct passwd *password, struct group *grup)
{
	char *fix;

	fix = ft_itoa(buf->st_size);
	ft_putstr(" ");
	ft_putnbr(buf->st_nlink);
	ft_putstr("\t");
	ft_putstr(password->pw_name);
	ft_putstr(" ");
	ft_putstr(grup->gr_name);
	ft_putstr(" ");
	if (ft_strlen(fix) <= 1)
	{
		ft_putstr("   ");
		ft_putstr(fix);
	}
	else {
		printf("%6lld", buf->st_size);
    }
	free(fix);
	return (1);
}

void	continue_chr_print(struct stat *buf, char *tmp, char *str)
{
	ft_putnbr(major(buf->st_rdev));
	ft_putnbr(4);
	ft_putnbr(minor(buf->st_rdev));
	ft_putstr(tmp + 4);
	ft_putstr(str);
}

void	continue_nonchr_print(char *tmp, char *str)
{
	ft_putstr(" ");
	ft_putstr(tmp + 4);
    ft_printf(" %s", str);
}