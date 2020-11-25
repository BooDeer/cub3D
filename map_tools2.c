/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:38:44 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/24 18:47:37 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					error_message(char *error)
{
	perror(error);
	return (-1);
}

int					fill_color_values(char *arr, int f_or_c, int i)
{
	int		tmp;

	tmp = ft_atoi(arr);
	if (tmp > 255 || tmp < 0)
		return (error_message("Error\nColor values should be between 0 and\
		255\n"));
	if (f_or_c == 70)
	{
		if (F[2] != -1)
			return (error_message("Error\nan argument is duplicated\n"));
		g_mapinfo->floor_color[i] = tmp;
	}
	else
	{
		if (C[2] != -1)
			return (error_message("Error\nan argument is duplicated\n"));
		g_mapinfo->ceilling_color[i] = tmp;
	}
	return (0);
}

static	int			check_map_extension(char *extension)
{
	if (ft_strncmp(&extension[ft_strlen(extension) - 4], ".cub", 4))
		return (-1);
	return (0);
}

int					ft_init(char *extension)
{
	if (check_map_extension(extension))
		return (-1);
	WIDTH = -1;
	HEIGHT = -1;
	SO = NULL;
	EA = NULL;
	WE = NULL;
	NO = NULL;
	SP = NULL;
	F[2] = -1;
	C[2] = -1;
	MAP_R = ft_strdup("");
	MFR = 0;
	CP = 0;
	S_COUNT = 0;
	return (0);
}

unsigned long		ft_rgb_to_hex(int r, int g, int b)
{
	return (65536 * r + 256 * g + b);
}
