/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:29:36 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/10 07:17:23 by hboudhir         ###   ########.fr       */
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
	int i = 0, j;
	while(i < width)
	{
		j = -1;
		while(++j < width)
			put_pixel((j + x), (i + y), color, pl->color_buffer_texture);
		i++;
	}		
}

void	draw_line(point *pl)
{
		int x1 = (int)floor(pl->x + cos(pl->rotationAngle) * 50);
	int y1 = (int)floor(pl->y + sin(pl->rotationAngle) * 50);
	int x0 = (int)floor(pl->x);
	int y0 = (int)floor(pl->y); 
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 

  for (;;){  /* loop */
    put_pixel(x0,y0, 0xffffff, pl->color_buffer_texture);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
  }
}

