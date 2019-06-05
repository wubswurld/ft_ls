#include "ft_ls.h"

char	*createpath(char *path, char *np)
{
	char	*info;

	info = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(np) + 1));
	// if (!(info = (char*)malloc(sizeof(char) * (strlen(path) + strlen(np) + 1))))
	// 	exit(1);
	ft_strcpy(info, path);
	ft_strcat(info, "/");
	ft_strcat(info, np);
	return (info);
}