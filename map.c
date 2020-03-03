/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:08:03 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/28 23:18:13 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include "GNL/get_next_line.h"
#include "LIBFT/libft.h"

void		ft_init(t_mapdata *mapinfo)
{
	WIDTH = 0;
	HEIGHT = 0;
}

int			ft_error(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		write(2, str + i, 1);
		i++;
	}
	exit(EXIT_SUCCESS);
	return (0);
}

void		ft_resolution(char *line, t_mapdata *mapinfo)
{
	int check;
	int owo;
	int uwu;
	int i;

	owo = 1;
	uwu = 1;
	check = 0;
	i = -1;
	while (line[++i])
	{
		if (line[0] == 'R' && line[1] != ' ')
			ft_error("no space after R");
		if ((line[i] == '0' && line[i - 1] == ' ') || line[i] == '-') // TODO: add uwu for HEIGHT and check before height for space
			ft_error("imposible resolution");
		if (ft_isdigit(line[i]) && owo && uwu)
		{
			WIDTH = ft_atoi(line + i);
			check++;
			uwu--;
		}
		if (ft_isdigit(line[i]) && !uwu && owo)
		{
			HEIGHT = ft_atoi(line + i);
			check++;
			owo--;
		}
	}
	(check != 2) ? ft_error("wrong number of parameters") : 0;
	(WIDTH >= 2560) ? WIDTH = 2560 : WIDTH;
	(HEIGHT >= 1440) ? HEIGHT = 1440 : WIDTH;
	printf("%d, %d\n", WIDTH, HEIGHT);
}

void		reading_file(int fd)
{
	char		*line;
	int			ret;
	t_mapdata 	*mapinfo;

	mapinfo = malloc(sizeof(t_mapdata));
	ft_init(mapinfo);
	while (1)
	{
		ret = get_next_line(fd, &line);
		(line[0] == 'R') ? ft_resolution(line, mapinfo) : 0;
		if (ret == 0)
			break ;
	}
}
