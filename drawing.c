/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:29:36 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/20 17:29:19 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		castall_rays(point *pl)
{
	float		ray_angle;
	int			i;

	ray_angle = pl->rotationAngle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < WIDTH)
	{
		cast_rayy(ray_angle, i, pl);
		ray_angle += FOV_ANGLE / WIDTH;
	}
}

void		draw_map(point *pl)
{
	castall_rays(pl);
	generate3dwalls(pl);
	pl->rotationAngle = fmod(pl->rotationAngle, 2 * M_PI);
	if (pl->rotationAngle < 0)
		pl->rotationAngle += 2 * M_PI;
	draw_sprite(pl);
}
