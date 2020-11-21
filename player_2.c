/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:31:13 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/20 17:58:36 by hboudhir         ###   ########.fr       */
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

void		update_player(point *pl)
{
	float	move_step;
	float	old_playerx;
	float	old_playery;

	old_playerx = pl->x;
	old_playery = pl->y;
	move_step = pl->walkDirection * pl->moveSpeed;
	pl->rotationAngle += pl->rotationSpeed * pl->turnSpeed;
	pl->rotationAngle = normalize_angle(pl->rotationAngle);
	pl->x = pl->x + ((cos(pl->rotationAngle)) * move_step) +
			(pl->turnDirection * ((cos(pl->rotationAngle +
			90 * (M_PI / 180)) * pl->moveSpeed)));
	pl->y = pl->y + (sin(pl->rotationAngle) * move_step) +
			(pl->turnDirection * ((sin(pl->rotationAngle +
			90 * (M_PI / 180)) * pl->moveSpeed)));
	if (collision_player(pl->x, old_playery))
		pl->x = old_playerx;
	if (collision_player(old_playerx, pl->y))
		pl->y = old_playery;
	draw_map(pl);
	mlx_put_image_to_window(pl->mlx_ptr, pl->win_ptr,
	pl->color_buffer_texture, 0, 0);
}
