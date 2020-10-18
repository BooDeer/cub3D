/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:08:03 by hboudhir          #+#    #+#             */
/*   Updated: 2020/10/16 02:49:32 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "GNL/get_next_line.h"

void		ft_init(t_mapdata *mapinfo)
{
	WIDTH = 0;
	HEIGHT = 0;
	SO = NULL;
	EA = NULL;
	WE = NULL;
	NO = NULL;
	SP = NULL;
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
		printf("=======%s\n=======", arr[i]);
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
				return (-1);
			SO = ft_strdup(arr[1]);
		}
		if (line[0] == 'W')
		{
			if (WE != NULL)
				return (-1);
			WE = ft_strdup(arr[1]);
		}
		if (line[0] == 'E')
		{
			if (EA != NULL)
				return (-1);
			EA = ft_strdup(arr[1]);
		}
		if (line[0] == 'N')
		{
			if (NO != NULL)
				return (-1);
			NO = ft_strdup(arr[1]);
		}
		if (line[0] == 'S')
		{
			if (SP != NULL)
				return (-1);
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

// int			ft_color_value(char *line, t_mapdata *mapinfo)
// {
// 	char	**arr;
// 	int		i;
	
// 	i = -1;
// 	if ((line[0] == 'F' || line [0] == 'C') && line[1] != ' ')
// 	{
// 		perror("Error.\nNo space after the color parametre.\n");
// 		return (-1);
// 	}
// 	else
// 	{
// 		arr = ft_split(&line[1], ',');
// 		while (arr[++i])
// 		{
// 			if (check_color_parametre(arr[i]))

// 		}
// 	}
// 	return (0);
// }

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
		// if (line[i] == 'F' && line[i + 1] == ' ')
		// 	(ft_color_value(&line[i], mapinfo))? free_struct(mapinfo, line) : 0;
		if (ret == 0)
			break ;
	}
	free(line);
	close(fd);
}
