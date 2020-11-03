/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 22:37:38 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/03 23:38:30 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

size_t			ft_strlen2(char *s)
{
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

int				str_isdigit(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}

int				arr_size(char **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		;
	return (i);
}

int				free_struct(t_mapdata *mapinfo, char *line)
{
	(SO != NULL) ? free(SO) : 0;
	(EA != NULL) ? free(EA) : 0;
	(NO != NULL) ? free(NO) : 0;
	(WE != NULL) ? free(WE) : 0;
	(SP != NULL) ? free(SP) : 0;
	if (!ft_strchr("RNSWEFC 10", *line) || *line != '\0')
		free(line);
	return (-1);
}

int				check_color_parametre(char *param)
{
	int			i;

	i = -1;
	while (param[++i] == ' ')
		i++;
	while (param[++i])
	{
		if (ft_isdigit(param[i]) || param[i] == ' ')
			continue ;
		else
			return (1);
	}
	return (0);
}
