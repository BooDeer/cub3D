/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:31:13 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/20 13:59:17 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		find_player(point *pl)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MAP_ROWS)
	{
		j = -1;
		while (++j < MAP_COLUMNS)
			if (ft_strchr("NEWS", MAP[j][i]))
			{
				pl->x = (i * TILE_SIZE) + TILE_SIZE / 2;
				pl->y = (j * TILE_SIZE) + TILE_SIZE / 2;
				ft_player_initial_pov(pl, MAP[j][i]);
				break ;
			}
	}
}

int			move_player(int key, point *pl)
{
	if (key == 13)
		pl->walkDirection = 1;
	if (key == 1)
		pl->walkDirection = -1;
	if (key == 2)
		pl->turnDirection = 1;
	if (key == 0)
		pl->turnDirection = -1;
	if (key == 53)
		exit(1);
	if (key == 124)
		pl->rotationSpeed = 1;
	if (key == 123)
		pl->rotationSpeed = -1;
	return (0);
}
