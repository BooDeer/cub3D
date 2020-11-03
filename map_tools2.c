/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/03 23:38:44 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/03 23:45:05 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int			error_message(char *error)
{
	perror(error);
	return (-1);
}

int			fill_color_values(char *arr, t_mapdata *mapinfo, int f_or_c, int i)
{
	int		tmp;

	tmp = ft_atoi(arr);
	if (tmp > 255 || tmp < 0)
		error_message("Error\nColor values should be between 0 and 255\n");
	if (f_or_c == 70)
	{
		if (F[2] != -1)
			error_message("Error\nan argument is duplicated\n");
		mapinfo->floor_color[i] = tmp;
	}
	else
	{
		if (C[2] != -1)
			error_message("Error\nan argument is duplicated\n");
		mapinfo->ceilling_color[i] = tmp;
	}
	return (0);
}
