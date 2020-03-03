/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:29:36 by hboudhir          #+#    #+#             */
/*   Updated: 2020/03/03 07:49:25 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void	put_pixel(int x, int y, int color, void *img)
{
	int k;
	int *tmp;

	tmp = (int *)mlx_get_data_addr(img, &k, &k, &k);
	tmp[x + (y * WINDOW_WIDTH)] = color;
}

void	draw_square(int x, int y,int width,int color, point *pl)
{
	int i = -1, j;
	while(++i < width)
	{
		j = -1;
		while(++j < width)
			put_pixel((j + x), (i + y), color, pl->color_buffer_texture);
	}		
}

void	draw_line(point *pl, int x1,int y1)
{
	int x0 = MINIMAP_SCALE * (int)floor(pl->x);
	int y0 = MINIMAP_SCALE * (int)floor(pl->y); 
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
	int err = dx + dy, e2;
 
	// int color = rand();
	while (1)
	{
		put_pixel(x0,y0, 0xff0000, pl->color_buffer_texture);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2 * err;
		if (e2 >= dy) 
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

 void	castallRays(point *pl)
{
	float		rayAngle;
	int			i;

	rayAngle = pl->rotationAngle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < NUM_RAYS)
	{
		castRayy(rayAngle, i, pl);
		rayAngle += FOV_ANGLE / NUM_RAYS;
	}
}
