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

void    free_dir(t_ls_flags *fp, t_ls *sp)
{
    int y;
    y = 0;
    while (sp->p_dir[y])
        free(sp->p_dir[y++]);
    free(sp->p_dir);
    free(sp->p_flags);
    free(fp); 
}