/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:08:03 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/18 14:01:25 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


//TODO: change every two lines that includes perror and
// 		a return statement by a function to save some space

// Check the extension of the texture files.

int		check_map_extension(char *extension)
{
	if (ft_strncmp(&extension[ft_strlen(extension) - 4], ".cub", 4))
		return (-1);
	return (0);
}
int		ft_init(t_mapdata *mapinfo,char *extension)
{
	if(check_map_extension(extension))
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




int		ft_resolution(char *line, t_mapdata *mapinfo)
{
	char	**arr = ft_split(line, ' ');
	int		i;

	i = -1;
	if (arr_size(arr) != 3)
		error_message("Error.\nwrong number of arguments.\n");
	if (line[1] != ' ' && line)
		error_message("Error.\nno space after the parametre.\n");
	if (!str_isdigit(arr[1]) || !str_isdigit(arr[2]))
		error_message("Error.\nthe arguments should only contain positive numbers.\n");
	if (WIDTH != -1 || HEIGHT != -1)
		error_message("Error\nan argument is duplicated\n");
	else
	{
		WIDTH = ft_atoi(arr[1]);
		HEIGHT = ft_atoi(arr[2]);
	}
	while (arr[++i])
		free(arr[i]);
	free(arr);
    if (WIDTH == 0 || HEIGHT == 0)
			error_message("Error\nImpossible resolution\n");
	(WIDTH >= 2860) ? WIDTH = 2860 : WIDTH;
	(HEIGHT >= 1620) ? HEIGHT = 1620 : WIDTH;
	(WIDTH < 10) ? WIDTH = 10 : WIDTH;
	(HEIGHT < 10) ? HEIGHT = 10 : HEIGHT;
	return (0);
}

int		ft_texture(char *line, t_mapdata *mapinfo)
{
	char	**arr = ft_split(line, ' ');
	int		i;

	i = -1;
	if (arr_size(arr) != 2)
		error_message("Error.\nwrong number of arguments");
	if (line[2] != ' ' && *arr[0] != 'S')
		error_message("Error.\nno space after the parametre.\n");
	if (open(arr[1], O_RDONLY) == -1)
		return(error_message("Error.\ntexture file not found"));
	else
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
		if (line[0] == 'S' && line[1] != 'O')
		{
			if (SP != NULL)
				error_message("Error\nan argument is duplicated\n");
			SP = ft_strdup(arr[1]);
		}
	}
	while(arr[++i])
		free(arr[i]);
	free(arr);
	return (0);
}



//
//	Skip the spaces and check if the parametre
//	contains any: more than one argument,characters,
//	special characters or number below or over
//	the value [0, 255].
//
unsigned long		ft_rgb_to_hex(int r, int g, int b)
{
	return (65536 * r + 256 * g + b);
}

int			ft_color_value(char *line, t_mapdata *mapinfo)
{
	char	**arr;
	int		i;
	
	i = -1;
	if ((line[0] == 'F' || line [0] == 'C') && line[1] != ' ')
		error_message("Error.\nNo space after the color parametre.\n");
	else
	{
		arr = ft_split(&line[1], ',');
		if (arr_size(arr) != 3)
			error_message("Error.\nwrong number of arguments.\n");
		while (arr[++i])
		{
			if (check_color_parametre(arr[i]))
				error_message("Error.\nColor parametre contains non-numeric characters\n");
			else
				if (fill_color_values(arr[i], mapinfo, line[0], i))
				{
					while(arr[i])
						free(arr[i--]);
					free(arr);
					return (-1);
				}
		}
		i = -1;
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
	FLOOR_COLOR = ft_rgb_to_hex(F[0], F[1], F[2]);
	CEILING_COLOR = ft_rgb_to_hex(C[0], C[1], C[2]);
	return (0);
}

int			ft_read_map(char *line, t_mapdata *mapinfo)
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

int			ft_check_map()
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
				error_message("Error\nThere's more than one player in the map\n");;
			if (i == 0)
				if (MAP[i][j] != ' ' && MAP[i][j] != '1')
					error_message("Error\nmap not closed\n");
			if (MAP[i][j] == '0' || MAP[i][j] == '2' || MAP[i][j] == 'N' || MAP[i][j] == 'E' || MAP[i][j] == 'W' ||  MAP[i][j] == 'S' )
			{
				if (MAP[i][j] == '2')
					S_COUNT++;
				if ((!ft_strchr("120NEWS",MAP[i - 1][j]) || !ft_strchr("120NEWS",MAP[i + 1][j]) ||
				!ft_strchr("120NEWS",MAP[i][j - 1])|| !ft_strchr("120NEWS",MAP[i][j + 1])))
					error_message("Error\nthe map is not closed or it includes a wrong character\n");
				if (((int)ft_strlen(MAP[i - 1]) - 1 < j) || (int)ft_strlen(MAP[i + 1]) - 1 < j)
					error_message("Error\nthe map is not closed\n");
				if (ft_isalpha(MAP[i][j]))
					CP = 1;
			}
			j++;
		}
	}
	if (!CP)
		error_message("Error\nThere's no player in the map\n");
	return (0);
}

int         ft_fill_mapsp(t_mapdata *mapinfo)
{
    int     len;
    int     i;
    int     j;
    int     row_len;
    int     col_len;
    char    *tmp;
    i = -1;
    row_len = 0;
    col_len = 0;
    while (MAP[++i])
    {
        len = 0;
        j = -1;
        while (MAP[i][++j])
            len++;
        if (len > row_len)
            row_len = len;
        col_len++;
    }
    i = -1;
    while (MAP[++i])
    {
        j = -1;
        if ((int)ft_strlen(MAP[i]) < row_len)
        {
            tmp = MAP[i];
            MAP[i] = (char *)malloc(sizeof(char) * row_len + 1);
            ft_memset(MAP[i], ' ', row_len);
            ft_memcpy(MAP[i], tmp, ft_strlen(tmp));
            MAP[i][row_len] = '\0';
            free(tmp);
        }
    }
    MAP_ROWS = row_len;
    MAP_COLUMNS = col_len;
    return (0);
}

int			ft_fill_map(t_mapdata *mapinfo)
{
	MAP = ft_split(MAP_R, '\n');
	free(MAP_R);
	if (ft_check_map())
		return (1);
    ft_fill_mapsp(mapinfo);
	return (0);
}

int		reading_file(char *file)
{
	char		*line;
	int			ret;
	int			fd;
	int			i;
	int			param;

	i = 0;
	param = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		perror("This file descriptor doesn't exist\n");
		return (-1);
	}

	while (1)
	{
		if (param == 8)
			param++;
		(ret = get_next_line(fd, &line));
		while(line[i] == ' ' && param != 9)
			i++;
		if (line[i] == 'R' && ++param)
			if (ft_resolution(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (line[i] == 'S' && line[i + 1] == 'O' && ++param)
			if (ft_texture(&line[i], mapinfo))
			return free_struct(mapinfo, line);
		if (line[i] == 'N' && line[i + 1] == 'O' && ++param)
			if (ft_texture(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (line[i] == 'E' && line[i + 1] == 'A' && ++param)
			if (ft_texture(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (line[i] == 'W' && line[i + 1] == 'E' && ++param)
			if (ft_texture(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if (line[i] == 'S' && line[i + 1] == ' ' && ++param)
			if (ft_texture(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if ((line[i] == 'F' || line [i] == 'C')&& line[i + 1] == ' ' && ++param)
			if (ft_color_value(&line[i], mapinfo))
				return free_struct(mapinfo, line);
		if ((line[i] == '1' || line[i] == ' '))
		{
			if (ft_read_map(line, mapinfo))
				return (free_struct(mapinfo, line));
		}
		else if (MFR && param != 9)
			error_message("Error\nthe map should be the last element of the file\n");
		else if (MFR && param != 9)
			error_message("Error\nThe map should be the last element of the file\n");
		else if (MFR && ((ft_strchr("NWSE 02", line[i]) && line[i] != '\0') || (line[0] != ' ' && line[0] != '1')))
			error_message("Error\nempty line after the map\n");
		if (ret == 0)
			break ;
		free(line);
	}
	if (MAP_R == '\0')
		error_message("Error\nThere's no map\n");
	if (ft_fill_map(mapinfo))
		return (-1);
	free(line);
	close(fd);
    return (0);
}
