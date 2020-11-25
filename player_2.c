/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:31:13 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/25 11:09:09 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		find_player(t_point *pl)
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

int			move_player(int key, t_point *pl)
{
	if (key == 13)
		pl->walk_direction = 1;
	if (key == 1)
		pl->walk_direction = -1;
	if (key == 2)
		pl->turn_direction = 1;
	if (key == 0)
		pl->turn_direction = -1;
	if (key == 53)
		exit(1);
	if (key == 124)
		pl->rotation_speed = 1;
	if (key == 123)
		pl->rotation_speed = -1;
	return (0);
}

void		update_player(t_point *pl)
{
	float	move_step;
	float	old_playerx;
	float	old_playery;

	old_playerx = pl->x;
	old_playery = pl->y;
	move_step = pl->walk_direction * pl->move_speed;
	pl->rotation_angle += pl->rotation_speed * pl->turn_speed;
	pl->rotation_angle = normalize_angle(pl->rotation_angle);
	pl->x = pl->x + ((cos(pl->rotation_angle)) * move_step) +
			(pl->turn_direction * ((cos(pl->rotation_angle +
			90 * (M_PI / 180)) * pl->move_speed)));
	pl->y = pl->y + (sin(pl->rotation_angle) * move_step) +
			(pl->turn_direction * ((sin(pl->rotation_angle +
			90 * (M_PI / 180)) * pl->move_speed)));
	if (collision_player(pl->x, old_playery))
		pl->x = old_playerx;
	if (collision_player(old_playerx, pl->y))
		pl->y = old_playery;
	draw_map(pl);
	mlx_put_image_to_window(pl->mlx_ptr, pl->win_ptr,
	pl->color_buffer_texture, 0, 0);
}

int			move_p(t_point *pl)
{
	mlx_hook(pl->win_ptr, 2, 0, move_player, pl);
	mlx_hook(pl->win_ptr, 3, 0, reset_player, pl);
	mlx_hook(pl->win_ptr, 17, 0, close_window, pl);
	update_player(pl);
	return (0);
}
