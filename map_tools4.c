/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 16:42:52 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/24 18:49:28 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		check_colors(char *line, char **arr)
{
	int		i;

	i = -1;
	if (arr_size(arr) != 3)
		error_message("Error.\nwrong number of arguments.\n");
	while (arr[++i])
	{
		if (check_color_parametre(arr[i]))
			error_message("Error.\nColor parametre contains non-numeric\
			characters\n");
		else if (fill_color_values(arr[i], line[0], i))
		{
			while (arr[i])
				free(arr[i--]);
			free(arr);
			exit(1);
		}
	}
}

int			ft_color_value(char *line)
{
	char	**arr;
	int		i;

	i = -1;
	if ((line[0] == 'F' || line[0] == 'C') && line[1] != ' ')
		error_message("Error.\nNo space after the color parametre.\n");
	else
	{
		arr = ft_split(&line[1], ',');
		check_colors(line, arr);
		i = -1;
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
	FLOOR_COLOR = ft_rgb_to_hex(F[0], F[1], F[2]);
	CEILING_COLOR = ft_rgb_to_hex(C[0], C[1], C[2]);
	return (0);
}

void		ft_check_map_norm(int i, int j)
{
	if (MAP[i][j] == '0' || MAP[i][j] == '2' || MAP[i][j] == 'N' || MAP[i][j]
	== 'E' || MAP[i][j] == 'W' || MAP[i][j] == 'S')
	{
		if (MAP[i][j] == '2')
			S_COUNT++;
		if ((!ft_strchr("120NEWS", MAP[i - 1][j]) || !ft_strchr("120NEWS"
		, MAP[i + 1][j]) || !ft_strchr("120NEWS", MAP[i][j - 1]) ||
		!ft_strchr("120NEWS", MAP[i][j + 1])))
			error_message("Error\nthe map is not closed or it includes\
			a wrong character\n");
		if (((int)ft_strlen(MAP[i - 1]) - 1 < j) || (int)ft_strlen(MAP[i + 1])
		- 1 < j)
			error_message("Error\nthe map is not closed\n");
		if (ft_isalpha(MAP[i][j]))
			CP = 1;
	}
}

int			ft_check_map(void)
{
	int		i;
	int		j;

	i = -1;
	while (MAP[++i])
	{
		j = 0;
		while (MAP[i][j])
		{
			if (CP && ft_strchr("NEWS", MAP[i][j]))
				error_message("Error\nThere's more than one player in the\
				map\n");
			if (i == 0)
				if (MAP[i][j] != ' ' && MAP[i][j] != '1')
					error_message("Error\nmap not closed\n");
			ft_check_map_norm(i, j);
			j++;
		}
	}
	if (!CP)
		error_message("Error\nThere's no player in the map\n");
	return (0);
}

int			ft_fill_map(void)
{
	MAP = ft_split(MAP_R, '\n');
	free(MAP_R);
	if (ft_check_map())
		return (1);
	ft_fill_mapsp();
	return (0);
}
