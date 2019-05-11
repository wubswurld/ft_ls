#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <stdio.h>
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
    int         ls_flags;
    int         ls_dir;
    char        *p_flags;
    char        **p_dir;
}               t_ls;

int     count_flag(char **av);
char      *convert_2d(char *ret, char **av);
char     *convert_flags(char **av, int *flags);
int     check_flags(t_ls *sp);
t_ls_flags  *index_flag(t_ls *sp);
char	**sort_folders(DIR *dir, t_flags *flags, int i);

# endif