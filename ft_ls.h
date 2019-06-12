/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 09:12:39 by jawatter          #+#    #+#             */
/*   Updated: 2019/06/08 22:37:56 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
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

# define CH_FLAG(x) (x == 1)
# define L(x) (x == 'l')
# define R(x) (x == 'R')
# define A(x) (x == 'a')
# define T(x) (x == 't')
# define S_R(x) (x == 'r')
# define RD(stream, dir) ((stream = readdir(dir)) != NULL)
# define OP(dir, fol, x) (dir = opendir(fol[x]))
# define N_OP(dir, fol) (dir = opendir(fol))
# define L_FLIP(fp, fpu, x) (L(fp[x]) ? fpu = 1 : 0)
# define R_FLIP(fp, fpu, x) (R(fp[x]) ? fpu = 1 : 0)
# define S_R_FLIP(fp, fpu, x) (S_R(fp[x]) ? fpu = 1 : 0)
# define A_FLIP(fp, fpu, x) (A(fp[x]) ? fpu = 1 : 0)
# define T_FLIP(fp, fpu, x) (T(fp[x]) ? fpu = 1 : 0)
# define CHECK_ERROR(str) (ft_printf("ls: %s: No such file or directory\n", str)
# define NOT_EQ(str, c) (str != c)

typedef struct	s_ls_flags
{
	bool		l_long;
	bool		r_recur;
	bool		a_hidden;
	bool		r_lex;
	bool		t_sort;
}				t_ls_flags;

typedef struct	s_ls
{
	t_ls_flags	*fp;
	int			ls_flags;
	int			ls_dir;
	char		*p_flags;
	char		**p_dir;
}				t_ls;

char			*createpath(char *path, char *new_path);
int				non_chr(struct stat *buf, struct passwd *pw, struct group *gp);
int				printchr(struct stat *buf, struct passwd *pw, struct group *gp);
void			ls_print(DIR *dir, t_ls *sp, int x);
void			start_print(char *name, t_ls *sp, char *path);
void			ls_basic(char *str, t_ls *sp);
void			print_stat(struct stat *buf);
void			recur_print(DIR *dir, t_ls *sp, int x);
void			rec_perms(char **fol, char *path, t_ls *sp);
int				count_flag(char **av);
char			*convert_2d(char *ret, char **av);
char			*convert_flags(char **av, int *flags);
int				check_flags(t_ls *sp);
t_ls_flags		*index_flag(t_ls *sp);
void			check_error(char *str);
char			**a_order(char **ret);
char			**ls_sort(DIR *dir, t_ls *sp);
int				count_dir(char **av);
char			**get_dir(char **av, int *ls_dirs);
char			**store_dirs(char *argv[], int *dirs);
int				ls_directory(char **folder, t_ls *sp, char *str, int ret);
void			rec_perms(char **fol, char *path, t_ls *sp);
void			listdir(char *str, t_ls *sp, int x);
void			free_folder(char **folder, int x);
void			free_dir(t_ls *sp);
void			help_basic(t_ls *sp, char *str, char **folder, char *tmp);
void			help_recur(t_ls *sp, char *str, char **folder, int x);

#endif
