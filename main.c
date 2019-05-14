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
    //if their are flags or if there are no flags store the directory in ret
    while (av[x])
    {
        if (av[x][0] != '-')
            ret[y++] = ft_strdup(av[x]);
        x++;
    }
    ret[*dir] = NULL;
    return (ret);
}
void    check_error(char *str)
{
    printf("ls: ");
    printf("%s: ", str);
    printf("No such file or directory\n");
}
void    ls_basic(char *str, t_ls_flags *fp, int x)
{
    printf("%d\n", x);
    printf("%d\n", fp->l_long);
    struct dirent *d_stream;
    DIR *der;
   if (!(der = opendir(str)))
    return;
    while ((d_stream = readdir(der)) != NULL)
    {
        printf("%s\n", d_stream->d_name);
    }

    // Close directory stream
    closedir(der);
    



}

void    ls_print(DIR *dir, t_ls *sp, t_ls_flags *fp, int x)
{
    printf("lsdir = %d\n", sp->ls_dir);
    //open directory stream at path pointed to by sp->p_dir[x], by defauly it goes to the first entry in the directory
    if (!(dir = opendir(sp->p_dir[x])))
        check_error(sp->p_dir[x]);
    else if (sp->ls_dir > 1)
    {
        ft_putendl(sp->p_dir[x]);
        ls_basic(sp->p_dir[x], fp, 0);
        printf("%s\n", sp->p_dir[x]);
    }
    else {
        ls_basic(sp->p_dir[x], fp, 0);
    }
    printf("long = %d\n", fp->l_long);
    closedir(dir);
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
            ls_print(dir, sp, fp, x);
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
        if (!(sp->p_dir = (char **)malloc(sizeof(char*) + 1)))
            exit(1);
        if (!(sp->p_dir[0] = (char *)malloc(sizeof(char) + 1)))
            exit(1);
        sp->p_dir[0][0] = '.';
        sp->p_dir[1] = NULL;
        printf("dir = .");
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