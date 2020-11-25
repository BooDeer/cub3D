/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:13:06 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/25 11:19:24 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double				f_mod(double a, double b)
{
	return (a - (floor(a / b) * b));
}

void				ft_which_texture(int *txt, int i)
{
	if (g_rays[i].israyfacingup && !g_rays[i].washitvertical)
		*txt = 0;
	else if (g_rays[i].israyfacingdown && !g_rays[i].washitvertical)
		*txt = 1;
	else if (g_rays[i].israyfacingleft && g_rays[i].washitvertical)
		*txt = 2;
	else if (g_rays[i].israyfacingright && g_rays[i].washitvertical)
		*txt = 3;
}

static void			wall_norm(t_walls *wall, t_point *pl)
{
	wall->perp_distance = g_rays[wall->i].distance
	* cos(g_rays[wall->i].ray_angle - pl->rotation_angle);
	wall->distance_projplane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
	wall->projected_wall_height = (TILE_SIZE / wall->perp_distance)
	* wall->distance_projplane;
	wall->wall_stripheight = (int)wall->projected_wall_height;
	wall->wall_top_pixel = (HEIGHT / 2) - (wall->wall_stripheight / 2);
	wall->wall_top_pixel = wall->wall_top_pixel < 0 ? 0 : wall->wall_top_pixel;
	wall->wall_bottompixel = (HEIGHT / 2) + (wall->wall_stripheight / 2);
	wall->wall_bottompixel = wall->wall_bottompixel > HEIGHT ?
	HEIGHT : wall->wall_bottompixel;
	wall->j = -1;
}

static void			draw_floor(t_walls *wall)
{
	while (++wall->j < wall->wall_bottompixel)
	{
		wall->distance_fromtop = wall->j + (wall->wall_stripheight / 2)
		- (HEIGHT / 2);
		wall->offsety = wall->distance_fromtop * ((float)TXT_H[wall->txt]
		/ wall->wall_stripheight);
		BUFFER[wall->i + ((WIDTH) * wall->j)] = TXT[wall->txt][wall->offsetx
		+ (wall->offsety * TXT_W[wall->txt])];
	}
}

void				generate3dwalls(t_point *pl)
{
	t_walls		wall;

	wall.i = -1;
	while (++wall.i < WIDTH)
	{
		wall_norm(&wall, pl);
		while (++wall.j < wall.wall_top_pixel)
			BUFFER[wall.i + (WIDTH * wall.j)] = CEILING_COLOR;
		ft_which_texture(&wall.txt, wall.i);
		if (g_rays[wall.i].washitvertical)
			wall.offsetx = f_mod(g_rays[wall.i].wall_hity, TILE_SIZE)
			* (TXT_W[wall.txt] / TILE_SIZE);
		else
			wall.offsetx = f_mod(g_rays[wall.i].wall_hitx, TILE_SIZE)
			* (TXT_W[wall.txt] / TILE_SIZE);
		wall.j = wall.wall_top_pixel - 1;
		draw_floor(&wall);
		wall.j = wall.wall_bottompixel - 1;
		while (++wall.j < HEIGHT)
			BUFFER[wall.i + (WIDTH * wall.j)] = FLOOR_COLOR;
	}
}
