/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:29:36 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/18 17:12:28 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	castall_rays(point *pl)
{
	float		ray_angle;
	int			i;

	ray_angle = pl->rotationAngle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < WIDTH)
	{
		castRayy(ray_angle, i, pl);
		ray_angle += FOV_ANGLE / WIDTH;
	}
}
