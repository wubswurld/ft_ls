#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <stdio.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include "final-libft/libft.h"

typedef struct s_ls_flags
{
    bool        l_long;
    bool        R_recur;
    bool        a_hidden;
    bool        r_lex;
    bool        t_sort;
}               t_ls_flags;

typedef struct s_ls
{
    t_ls_flags  *fp;
    int         ls_flags;
    int         ls_dir;
    char        *p_flags;
    char        **p_dir;
}               t_ls;

//create path
char	*createpath(char *path, char *new_path);
//print files
void	continue_nonchr_print(char *tmp, char *str);
void	continue_chr_print(struct stat *buf, char *tmp, char *str);
int		non_chr_blk(struct stat *buf, struct passwd *password, struct group *grup);
int		print_chr_blk(struct stat *buf, struct passwd *password, struct group *grup);
//print permissions
void    print_stat(struct stat *buf);
//flags
int     count_flag(char **av);
//convert str into 2d array
char      *convert_2d(char *ret, char **av);
//convert flags into str
char     *convert_flags(char **av, int *flags);
//assign boolean values to each flag
int     check_flags(t_ls *sp);
t_ls_flags  *index_flag(t_ls *sp);
//error
void    check_error(char *str);
//sort
char	**a_order(char **ret);
char    **ls_sort(DIR *dir, t_ls *sp, int x);
//directory
int     count_dir(char **av);
char    **get_dir(char **av, int *dir);
void    free_dir(t_ls_flags *fp, t_ls *sp);
char	**store_dirs(char *argv[], int *dirs);
// int		ls_directory(char **folder, t_ls_flags *fp, char *str, int ret);
int		ls_directory(char **folder, t_ls *sp, char *str, int ret);

# endif