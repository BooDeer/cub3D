/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:08:03 by hboudhir          #+#    #+#             */
/*   Updated: 2020/10/19 18:31:04 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "GNL/get_next_line.h"

void		ft_init(t_mapdata *mapinfo)
{
	WIDTH = -1;
	HEIGHT = -1;
	SO = NULL;
	EA = NULL;
	WE = NULL;
	NO = NULL;
	SP = NULL;
	F[2] = -1;
	C[2] = -1;
}

int			str_isdigit(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
		if(!ft_isdigit(str[i]))
			return(0);
	return (1);
}

int			arr_size(char **arr)
{
	int		i;
	i = -1;

	// printf("Test\n");
	while (arr[++i])
		;
	return (i);
}

int		ft_resolution(char *line, t_mapdata *mapinfo)
{
	char	**arr = ft_split(line, ' ');

	if (arr_size(arr) != 3)
	{
		perror("Error.\nwrong number of arguments.\n");
		return (-1);
	}
	if (line[1] != ' ' && line)
	{
		perror("Error.\nno space after the parametre.\n");
		return (-1);
	}
	if (!str_isdigit(arr[1]) || !str_isdigit(arr[2]))
	{
		perror("Error.\nthe arguments should only contain positive numbers.\n");
		return (-1);
	}
	if (WIDTH != -1 || HEIGHT != -1)
	{
		perror("Error\nan argument is duplicated\n");
		return (-1);
	}
	else
	{
		WIDTH = ft_atoi(arr[1]);
		HEIGHT = ft_atoi(arr[2]);
	}
	free(arr);
	(WIDTH >= 2560) ? WIDTH = 2560 : WIDTH;
	(HEIGHT >= 1440) ? HEIGHT = 1440 : WIDTH;
	return (0);
}

int		ft_texture(char *line, t_mapdata *mapinfo)
{
	char	**arr = ft_split(line, ' ');
	int		i;

	i = -1;
	if (arr_size(arr) != 2)
	{
		perror("Error.\nwrong number of arguments");
		return (-1);
	}
	if (line[2] != ' ' && *arr[0] != 'S')
	{
		perror("Error.\nno space after the parametre.\n");
		return (-1);
	}
	if (open(ft_strtrim(arr[1], "\'"), O_RDONLY) == -1)
	{
		perror("Error.\ntexture file");
		return (-1);
	}
	else
	{
		if (line[0] == 'S' && line[1] == 'O')
		{
			if (SO != NULL)
			{
				perror("Error\nan argument is duplicated\n");
				return (-1);
			}
			SO = ft_strdup(arr[1]);
		}
		if (line[0] == 'W')
		{
			if (WE != NULL)
			{
				perror("Error\nan argument is duplicated\n");
				return (-1);
			}
			WE = ft_strdup(arr[1]);
		}
		if (line[0] == 'E')
		{
			if (EA != NULL)
			{
				perror("Error\nan argument is duplicated\n");
				return (-1);
			}
			EA = ft_strdup(arr[1]);
		}
		if (line[0] == 'N')
		{
			if (NO != NULL)
			{
				perror("Error\nan argument is duplicated\n");
				return (-1);
			};
			NO = ft_strdup(arr[1]);
		}
		if (line[0] == 'S' && line[1] != 'O')
		{
			if (SP != NULL)
			{
				perror("Error\nan argument is duplicated\n");
				return (-1);
			}
			SP = ft_strdup(arr[1]);
		}
	}
	// printf("%s\n", arr[1]);
	while(arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}

void		free_struct(t_mapdata *mapinfo, char *line)
{
	(SO != NULL) ? free(SO) : 0;	
	(EA != NULL) ? free(EA) : 0;	
	(NO != NULL) ? free(NO) : 0;	
	(WE != NULL) ? free(WE) : 0;
	(SP != NULL) ? free(SP) : 0;
	if (!ft_strchr("RNSWEFC 10", *line) || *line != '\0')
		free(line);
}

//
//	Skip the spaces and check if the parametre
//	contains any: more than one argument,characters,
//	special characters or number below or over
//	the value [0, 255].
//
int			check_color_parametre(char *param) // F                256qd,   0 0, -250
{
	int		i;

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

int			fill_color_values(char **arr, t_mapdata *mapinfo, int f_or_c)
{
	int		tmp;
	int		i;

	i = -1;
	while (++i < 3)
	{
		tmp = ft_atoi(arr[i]);
		if (tmp > 255 || tmp < 0)
		{
			perror("Error\nColor values should be between 0 and 255\n");
			return (-1);
		}
		if (f_or_c == 70)
		{
			if (F[2] != -1)
			{
				perror("Error\nan argument is duplicated\n");
				return (-1);
			}
			mapinfo->floor_color[i] = tmp;
		}
		else
		{
			if (C[2] != -1)
			{
				perror("Error\nan argument is duplicated\n");
				return (-1);
			}
			mapinfo->ceilling_color[i] = tmp;
		}
	}
	return (0);
}

int			ft_color_value(char *line, t_mapdata *mapinfo)
{
	char	**arr;
	int		i;
	
	i = -1;
	if ((line[0] == 'F' || line [0] == 'C') && line[1] != ' ')
	{
		perror("Error.\nNo space after the color parametre.\n");
		return (-1);
	}
	else
	{
		arr = ft_split(&line[1], ',');
		while (arr[++i])
		{
			if (check_color_parametre(arr[i]))
				perror("Error.\nColor parametre contains non-numeric characters\n");
			else
				if (fill_color_values(arr, mapinfo, line[0]))
				{
					while(i)
						free(arr[i--]);
					free(arr);
					return (-1);
				}
		}
	}
	return (0);
}

void		reading_file(void)
{
	char		*line;
	int			ret;
	int			fd;
	t_mapdata 	*mapinfo;
	int			i;

	i = 0;
	fd = open("cube.cub", O_RDONLY);
	if (fd == -1)
	{
		perror("This file descriptor doesn't exist\n");
		return ;
	}
	mapinfo = malloc(sizeof(t_mapdata));
	if (!mapinfo)
		return ;
	ft_init(mapinfo);
	while ((ret = get_next_line(fd, &line)))
	{
		while(line[i] == ' ')
			i++;
		if (line[i] == 'R')
			if (ft_resolution(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (line[i] == 'S' && line[i + 1] == 'O')
			if (ft_texture(&line[i], mapinfo))
			return free_struct(mapinfo, line);
		if (line[i] == 'N' && line[i + 1] == 'O')
			if (ft_texture(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (line[i] == 'E' && line[i + 1] == 'A')
			if (ft_texture(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (line[i] == 'W' && line[i + 1] == 'E')
			if (ft_texture(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (line[i] == 'S' && line[i + 1] == ' ')
			if (ft_texture(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if ((line[i] == 'F' || line [i] == 'C')&& line[i + 1] == ' ')
			if (ft_color_value(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (ret == 0)
			break ;
	}
	printf("%d\n%d\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n", mapinfo->width, mapinfo->height, mapinfo->north_texture, mapinfo->south_texture, mapinfo->west_texture, mapinfo->east_texture, mapinfo->sprite_texture, mapinfo->ceilling_color[2], mapinfo->floor_color[2]);
	free(line);
	close(fd);
}
