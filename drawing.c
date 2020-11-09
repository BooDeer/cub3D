/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:29:36 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/07 11:14:01 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


 void	castallRays(point *pl)
{
	float		rayAngle;
	int			i;

	rayAngle = pl->rotationAngle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < WIDTH)
	{
		castRayy(rayAngle, i, pl);
		rayAngle += FOV_ANGLE / WIDTH;
	}
}
