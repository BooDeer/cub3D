/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:08:03 by hboudhir          #+#    #+#             */
/*   Updated: 2020/10/29 18:27:47 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "GNL/get_next_line.h"


//TODO: change every two lines that includes perror and
// 		a return statement by a function to save some space

size_t		ft_strlen2(char *s)
{
	size_t		i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}
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
	MAP_R = ft_strdup("");
	MFR = 0;
	CP = 0;
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

int			fill_color_values(char *arr, t_mapdata *mapinfo, int f_or_c, int i)
{
	int		tmp;


		tmp = ft_atoi(arr);
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
		if (arr_size(arr) != 3)
		{
			perror("Error.\nwrong number of arguments.\n");
			return (-1);		
		}
		while (arr[++i])
		{
			if (check_color_parametre(arr[i]))
				perror("Error.\nColor parametre contains non-numeric characters\n");
			else
				if (fill_color_values(arr[i], mapinfo, line[0], i))
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

int			ft_read_map(char *line, t_mapdata *mapinfo)
{
	char *tmp;
	if (!MFR)
		MFR = 1;
	if (line[ft_strlen2(line) - 1] != '1' && line[ft_strlen2(line) - 1] != ' ')
	{
		perror("Error\nmap is not closed\n");
		return (1);
	}
	tmp = MAP_R;
	MAP_R = ft_strjoin(MAP_R, line);
	free(tmp);
	tmp = MAP_R;
	MAP_R = ft_strjoin(MAP_R, "\n");
	free(tmp);
	return (0);
}

int			ft_check_map(t_mapdata *mapinfo)
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
			{
				perror("Error\nThere's more than one player in the map\n");
				return (1);
			}
			if (i == 0)
				if (MAP[i][j] != ' ' && MAP[i][j] != '1')
				{
					perror("Error\nmap not closed\n");
					return (1);
				}
			if (MAP[i][j] == '0' || MAP[i][j] == '2' || MAP[i][j] == 'N' || MAP[i][j] == 'E' || MAP[i][j] == 'W' ||  MAP[i][j] == 'S' )
			{
				if ((!ft_strchr("120NEWS",MAP[i - 1][j]) || !ft_strchr("120NEWS",MAP[i + 1][j]) ||
				!ft_strchr("120NEWS",MAP[i][j - 1])|| !ft_strchr("120NEWS",MAP[i][j + 1])))
				{
					perror("Error\nthe map is not closed or it includes a wrong character\n");
					return (1);
				}
				if (((int)ft_strlen(MAP[i - 1]) - 1 < j) || (int)ft_strlen(MAP[i + 1]) - 1 < j)
				{
					perror("Error\nthe map is not closed\n");
					return (1);				
				}
				if (ft_isalpha(MAP[i][j]))
					CP = 1;
			}
			j++;
		}
	}

	if (!CP)
	{
		perror("Error\nThere's no player in the map\n");
		return (1);
	}
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
        if (ft_strlen(MAP[i]) < row_len)
        {
            tmp = MAP[i];
            MAP[i] = (char *)malloc(sizeof(char) * row_len + 1);
            // printf("%d====\n", c_len);
            ft_memset(MAP[i], ' ', row_len);
            ft_memcpy(MAP[i], tmp, ft_strlen(tmp));
            MAP[i][row_len] = '\0';
            free(tmp);
        }
            printf("%s\n",MAP[i]);
    }
    MAP_ROWS = row_len;
    MAP_COLUMNS = col_len;
    return (0);
}

int			ft_fill_map(t_mapdata *mapinfo)
{
	MAP = ft_split(MAP_R, '\n');
	if (ft_check_map(mapinfo))
		return (1);
    ft_fill_mapsp(mapinfo);
	return (0);
}

void		reading_file(t_mapdata *mapinfo)
{
	char		*line;
	int			ret;
	int			fd;
	int			i;
	int			param;

	i = 0;
	param = 0;
	fd = open("cube.cub", O_RDONLY);
	if (fd == -1)
	{
		perror("This file descriptor doesn't exist\n");
		return ;
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
		{
			perror("Error\nthe map should be the last element of the file\n");
			return (free_struct(mapinfo, line));
		}
		else if (MFR && param != 9)
		{
			perror("Error\nThe map should be the last element of the file\n");
			return (free_struct(mapinfo, line));
		}
		else if (MFR && ((ft_strchr("NWSE 02", line[i]) && line[i] != '\0') || (line[0] != ' ' && line[0] != '1')))
		{
			perror("Error\nempty line after the map\n");
			return (free_struct(mapinfo, line));
		}
		if (ret == 0)
			break ;
	}
	if (MAP_R == '\0')
	{
		perror("Error\nThere's no map\n");
		return (free_struct(mapinfo, line));
	}
	if (ft_fill_map(mapinfo))
		return (free_struct(mapinfo, line));
	printf("%s\n", MAP[3]);
	// printf("%d\n%d\n%s\n%s\n%s\n%s\n%s\n%d\n%d\n", mapinfo->width, mapinfo->height, mapinfo->north_texture, mapinfo->south_texture, mapinfo->west_texture, mapinfo->east_texture, mapinfo->sprite_texture, mapinfo->ceilling_color[2], mapinfo->floor_color[2]);
	free(line);
	close(fd);
}
