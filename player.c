/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:53:05 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/23 17:25:29 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	struct_init(point *pl)
{
	find_player(pl);
	pl->radius = 3;
	pl->turnDirection = 0;
	pl->walkDirection = 0;
	pl->moveSpeed = TILE_SIZE / 9;
	pl->rotationSpeed = 2 * (M_PI / 180);
	pl->rotationSpeed = 0;
	pl->turnSpeed = 4 * (M_PI / 180);
	SCREEN = 0;
}

int		reset_player(int key, point *pl)
{
	if (key == 13 || key == 1)
		pl->walkDirection = 0;
	if (key == 2 || key == 0)
		pl->turnDirection = 0;
	if (key == 124 || key == 123)
		pl->rotationSpeed = 0;
	return (0);
}

int		collision(int x, int y)
{
	int		index_x;
	int		index_y;

	index_x = x;
	index_y = y;
	if (index_x < 0 || index_x / TILE_SIZE > MAP_ROWS || index_y < 0
	|| index_y / TILE_SIZE > MAP_COLUMNS)
		return (1);
	index_x = floor(index_x / TILE_SIZE);
	index_y = floor(index_y / TILE_SIZE);
	return (MAP[index_y][index_x] == '1');
}

int		collision_player(int x, int y)
{
	int		index_x;
	int		index_y;

	index_x = x;
	index_y = y;
	if (index_x < 0 || index_x / TILE_SIZE > MAP_ROWS ||
	index_y < 0 || index_y / TILE_SIZE > MAP_COLUMNS)
		return (1);
	index_x = floor(index_x / TILE_SIZE);
	index_y = floor(index_y / TILE_SIZE);
	return (MAP[index_y][index_x] == '1' || MAP[index_y][index_x] == '2');
}

void	ft_player_initial_pov(point *pl, int c)
{
	if (c == 'N')
		pl->rotationAngle = -90 * (M_PI / 180);
	if (c == 'E')
		pl->rotationAngle = 0 * (M_PI / 180);
	if (c == 'W')
		pl->rotationAngle = 180 * (M_PI / 180);
	if (c == 'S')
		pl->rotationAngle = 90 * (M_PI / 180);
}
