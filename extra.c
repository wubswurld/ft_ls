/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jawatter <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/08 07:48:59 by jawatter          #+#    #+#             */
/*   Updated: 2019/06/08 09:11:53 by jawatter         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char	*createpath(char *path, char *np)
{
	char	*info;

	info = (char *)malloc(sizeof(char) * (ft_strlen(path) + ft_strlen(np) + 1));
	ft_strcpy(info, path);
	ft_strcat(info, "/");
	ft_strcat(info, np);
	return (info);
}
