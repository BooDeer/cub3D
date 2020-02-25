/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 11:53:05 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/25 16:14:55 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	struct_init(point *pl)
{
	pl->x = 0;
	pl->y = 0;
	pl->radius = 3;
	pl->turnDirection = 0;
	pl->walkDirection = 0 ;
	pl->rotationAngle = 0;
	pl->moveSpeed = TILE_SIZE / 8;
	pl->rotationSpeed = 2 * (M_PI  / 180);
	pl->turnDirection = 45 * (M_PI / 180);
}

int	reset_player(int key, point *pl)
{
	if (key == 13)
	{
		pl->walkDirection = 0;
	}
	else if (key == 1)
	{
		pl->walkDirection = 0;
	}
	else if (key == 2)
	{
		pl->turnDirection =0;
	}
	else if (key == 0)
	{
		pl->turnDirection = 0;
	}
	return(0);
}