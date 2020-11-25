/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:29:36 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/25 11:07:05 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		castall_rays(t_point *pl)
{
	float		ray_angle;
	int			i;

	ray_angle = pl->rotation_angle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < WIDTH)
	{
		cast_rayy(ray_angle, i, pl);
		ray_angle += FOV_ANGLE / WIDTH;
	}
}

void		draw_map(t_point *pl)
{
	castall_rays(pl);
	generate3dwalls(pl);
	pl->rotation_angle = fmod(pl->rotation_angle, 2 * M_PI);
	if (pl->rotation_angle < 0)
		pl->rotation_angle += 2 * M_PI;
	draw_sprite(pl);
}
