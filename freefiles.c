#include "ft_ls.h"

void    free_dir(t_ls *sp)
{
    int y;
    y = 0;
    while (sp->p_dir[y])
        free(sp->p_dir[y++]);
    free(sp->p_dir);
    free(sp->p_flags);
	free(sp->fp);
	free(sp); 
}

void    free_folder(char **folder, int x)
{
    char **tmp;

    x = 0;
    tmp = folder;
    while (folder[x])
	{
		free(folder[x]);
		x++;
	}
    free(tmp);
}