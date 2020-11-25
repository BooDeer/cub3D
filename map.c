/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 21:08:03 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/25 18:31:58 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_fill_mapsp2(t_fmap *fmap)
{
	if ((int)ft_strlen(MAP[fmap->i]) < fmap->row_len)
	{
		fmap->tmp = MAP[fmap->i];
		MAP[fmap->i] = (char *)malloc(sizeof(char) * fmap->row_len + 1);
		ft_memset(MAP[fmap->i], ' ', fmap->row_len);
		ft_memcpy(MAP[fmap->i], fmap->tmp, ft_strlen(fmap->tmp));
		MAP[fmap->i][fmap->row_len] = '\0';
		free(fmap->tmp);
	}
}

int			ft_fill_mapsp(void)
{
	t_fmap fmap;

	fmap.i = -1;
	fmap.row_len = 0;
	fmap.col_len = 0;
	while (MAP[++fmap.i])
	{
		fmap.len = 0;
		fmap.j = -1;
		while (MAP[fmap.i][++fmap.j])
			fmap.len++;
		if (fmap.len > fmap.row_len)
			fmap.row_len = fmap.len;
		fmap.col_len++;
	}
	fmap.i = -1;
	while (MAP[++fmap.i])
	{
		fmap.j = -1;
		ft_fill_mapsp2(&fmap);
	}
	MAP_ROWS = fmap.row_len;
	MAP_COLUMNS = fmap.col_len;
	return (0);
}

void		check_arg_map(char *line, int *param, int i)
{
	if (MFR && *param != 9)
		error_message("Error\nThe map should be the last element of\
		the file\n");
	else if (MFR && *param < 8)
		error_message("Error\nWrong number of arguments");
	else if ((line[i] == '1' || line[i] == ' '))
		ft_read_map(line);
	else if (MFR && ((ft_strchr("NWSE 02", line[i]) && line[i] != '\0') ||
	(line[0] != ' ' && line[0] != '1')))
		error_message("Error\nempty line or wrong character after the map\n");
}

void		check_argument(char *line, int *param, int i)
{
	if (line[i] == 'R' && ++*param)
		ft_resolution(&line[i]);
	if (line[i] == 'S' && line[i + 1] == 'O' && ++*param)
		ft_texture(&line[i]);
	if (line[i] == 'N' && line[i + 1] == 'O' && ++*param)
		ft_texture(&line[i]);
	if (line[i] == 'E' && line[i + 1] == 'A' && ++*param)
		ft_texture(&line[i]);
	if (line[i] == 'W' && line[i + 1] == 'E' && ++*param)
		ft_texture(&line[i]);
	if (line[i] == 'S' && line[i + 1] == ' ' && ++*param)
		ft_texture(&line[i]);
	if ((line[i] == 'F' || line[i] == 'C') && line[i + 1] == ' ' && ++*param)
		ft_color_value(&line[i]);
	check_arg_map(line, param, i);
}

int			reading_file(char *file)
{
	t_map_p		mapp;

	mapp.i = 0;
	mapp.param = 0;
	mapp.fd = open(file, O_RDONLY);
	if (mapp.fd == -1)
		return (error_message("Error\nThis file descriptor doesn't exist\n"));
	while (1)
	{
		if (mapp.param == 8)
			mapp.param++;
		mapp.ret = get_next_line(mapp.fd, &mapp.line);
		while (mapp.line[mapp.i] == ' ' && mapp.param != 9)
			mapp.i++;
		check_argument(mapp.line, &mapp.param, mapp.i);
		if (mapp.ret == 0)
			break ;
		free(mapp.line);
	}
	if (MAP_R == '\0')
		error_message("Error\nThere's no map\n");
	ft_fill_map();
	free(mapp.line);
	close(mapp.fd);
	return (0);
}
