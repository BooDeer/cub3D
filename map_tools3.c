/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 18:39:29 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/23 16:42:11 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int		check_resolution(void)
{
	if (WIDTH == 0 || HEIGHT == 0)
		return (error_message("Error\nImpossible resolution\n"));
	(WIDTH >= 2860) ? WIDTH = 2860 : WIDTH;
	(HEIGHT >= 1620) ? HEIGHT = 1620 : WIDTH;
	(WIDTH < 10) ? WIDTH = 10 : WIDTH;
	(HEIGHT < 10) ? HEIGHT = 10 : HEIGHT;
	return (0);
}

int		ft_resolution(char *line, t_mapdata *mapinfo)
{
	char	**arr;
	int		i;

	i = -1;
	arr = ft_split(line, ' ');
	if (arr_size(arr) != 3)
		return (error_message("Error.\nwrong number of arguments.\n"));
	if (line[1] != ' ' && line)
		return (error_message("Error.\nno space after the parametre.\n"));
	if (!str_isdigit(arr[1]) || !str_isdigit(arr[2]))
		return (error_message("Error.\nthe arguments should only contain \
		positive numbers.\n"));
	if (WIDTH != -1 || HEIGHT != -1)
		return (error_message("Error\nan argument is duplicated\n"));
	else
	{
		WIDTH = ft_atoi(arr[1]);
		HEIGHT = ft_atoi(arr[2]);
	}
	free(arr[0]);
	free(arr[1]);
	free(arr[2]);
	free(arr);
	return (check_resolution());
}

void	texture_path(char *line, char **arr)
{
	if (line[0] == 'S' && line[1] == 'O')
	{
		if (SO != NULL)
			error_message("Error\nan argument is duplicated\n");
		SO = ft_strdup(arr[1]);
	}
	if (line[0] == 'W')
	{
		if (WE != NULL)
			error_message("Error\nan argument is duplicated\n");
		WE = ft_strdup(arr[1]);
	}
	if (line[0] == 'E')
	{
		if (EA != NULL)
			error_message("Error\nan argument is duplicated\n");
		EA = ft_strdup(arr[1]);
	}
	if (line[0] == 'N')
	{
		if (NO != NULL)
			error_message("Error\nan argument is duplicated\n");
		NO = ft_strdup(arr[1]);
	}
}

int		ft_texture(char *line, t_mapdata *mapinfo)
{
	char	**arr;
	int		i;

	arr = ft_split(line, ' ');
	i = -1;
	if (arr_size(arr) != 2)
		error_message("Error.\nwrong number of arguments");
	if (line[2] != ' ' && *arr[0] != 'S')
		error_message("Error.\nno space after the parametre.\n");
	if (open(arr[1], O_RDONLY) == -1)
		error_message("Error.\ntexture file not found");
	else
	{
		texture_path(line, arr);
		if (line[0] == 'S' && line[1] != 'O')
		{
			if (SP != NULL)
				error_message("Error\nan argument is duplicated\n");
			SP = ft_strdup(arr[1]);
		}
	}
	while (arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}

int		ft_read_map(char *line, t_mapdata *mapinfo)
{
	char *tmp;

	if (!MFR)
		MFR = 1;
	if (line[ft_strlen2(line) - 1] != '1' && line[ft_strlen2(line) - 1] != ' ')
		error_message("Error\nmap is not closed\n");
	tmp = MAP_R;
	MAP_R = ft_strjoin(MAP_R, line);
	free(tmp);
	tmp = MAP_R;
	MAP_R = ft_strjoin(MAP_R, "\n");
	free(tmp);
	return (0);
}
