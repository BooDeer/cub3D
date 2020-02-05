/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/05 18:12:58 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
void	*color_buffer_texture;
int		*data;

float		abso(float n)
{
	return ((n > 0) ? n : (n * -1));
}
/*
**
**
**
**
*/
void	struct_init(point *pl)
{
	pl->x = 0;
	pl->y = 0;
	pl->radius = 3;
	pl->turnDirection = 0;
	pl->walkDirection = 0 ;
	pl->rotationAngle = M_PI / 2;
	pl->moveSpeed = 2.0;
	pl->rotationSpeed = 2 * (M_PI  / 180);
	pl->turnDirection = 45 * (M_PI / 180);
}
void		put_pixel(int x, int y, int color, void *img)
{
	int k;
	int *tmp;
	
	tmp = (int *)mlx_get_data_addr(img, &k, &k, &k);
	tmp[x + (y * WINDOW_WIDTH)] = color;
}

void draw_square(int x, int y,int width,int color)
{
	int i = 0, j;
	while(i < width)
	{
		j = 0;
		while(j < width)
		{
			// data[((i + y) * WINDOW_WIDTH) + (j + x)] = color;
			put_pixel((j + x), (i + y), color, color_buffer_texture);
			j++;
		}
		i++;
	}		
}

void	draw_line(point *pl, float x1, float y1)
{
	float dx, dy, step;
	int		i;

	i = -1;
	dx = abso(x1 - pl->x);
	dy = abso(y1 - pl->y);

	if (dx >= dy)
		step = dx;
	else
		step = dy;
	dx /= step;
	dy /= step;
	x1 = pl->x;
	y1 = pl->y;
	while (++i < step)
	{
		put_pixel(x1 * MINIMAP_SCALE, y1 * MINIMAP_SCALE, 0xffffff, color_buffer_texture);
		x1 += dx;
		y1 += dy;
	}
}
void 	draw_map(point *pl)
{
	int x, y;
	static int check;
		for (int i = 0; i < MAP_NUM_COLS; i++)
	{
		int j = 0;
		for (int j = 0; j < MAP_NUM_ROWS; j++)
		{
			if(map[j][i] == 1)
			{
				draw_square(i * TILE_SIZE * MINIMAP_SCALE,j * TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, 0xff);
			}
			else if (!map[j][i])
				draw_square(i * TILE_SIZE * MINIMAP_SCALE,j * TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, 0x000000);
			else if (!check++)
			{
				x = (i * TILE_SIZE) + TILE_SIZE / 2;
				y = (j * TILE_SIZE) + TILE_SIZE / 2;
				pl->x = x;
				pl->y = y;
				put_pixel(x, y, 0xffffff, color_buffer_texture);
				draw_line(pl, 0, 0);
				printf("%d\n%d\n", x, y);
			}
			
		}
	}
}

int 	move_player(int key, point *pl)
{
	float	moveStep, newPlayerx, newPlayery;


	printf("%d\n", key);
	if (key == 13)
	{
		pl->y -= 3;
		pl->walkDirection = 1;
	}
	else if (key == 1)
	{
		pl->y += 3;
		pl->walkDirection = -1;
	}
	else if (key == 2)
	{
		pl->x += 3;
		pl->turnDirection = 1;
	}
	else if (key == 0)
	{
		pl->x -= 3;
		pl->turnDirection = -1;
	}
	else if (key == 53)
		exit(1);
	mlx_destroy_image(pl->mlx_ptr, color_buffer_texture);
	color_buffer_texture = mlx_new_image(pl->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// mlx_clear_window(pl->mlx_ptr, pl->win_ptr);
	draw_map(pl);


	
	pl->rotationAngle += pl->turnDirection * pl->turnSpeed;
	moveStep = pl->walkDirection * pl->moveSpeed;
	newPlayerx = pl->x + cos(pl->rotationAngle) * moveStep;
	newPlayery = pl->y + sin(pl->rotationAngle) * moveStep;



	
	put_pixel(pl->x, pl->y, 0xffffff, color_buffer_texture);
	draw_line(pl, newPlayerx, newPlayery);
	mlx_put_image_to_window(pl->mlx_ptr, pl->win_ptr, color_buffer_texture, 0, 0);
	return 0;
}

void	reset_player(int key, point *pl)
{
	struct_init(pl);
}

int		move_p(point *pl)
{
	mlx_hook(pl->win_ptr, 2, 0, move_player,pl);
	mlx_hook(pl->mlx_ptr, 3, 0, reset_player, pl);
	return 0;
}

int		main()
{


	int		a;
	point pl;
	void *img;

	pl.mlx_ptr = mlx_init();
	pl.win_ptr = mlx_new_window(pl.mlx_ptr,WINDOW_WIDTH, WINDOW_HEIGHT,"bruh");
	color_buffer_texture = mlx_new_image(pl.mlx_ptr, WINDOW_WIDTH,WINDOW_HEIGHT);
	data = (int*)mlx_get_data_addr(color_buffer_texture, &a,&a,&a);
	draw_map(&pl);
	// mlx_hook(pl->win_ptr, 2, 0, move_player,&pl);
	mlx_loop_hook(pl.mlx_ptr, move_p, &pl);


	// img = mlx_xpm_file_to_image(pl->mlx_ptr, "~/Downloads/81621207_667657023772881_3948275671851073536_n.png", &a, &a);

	
	// mlx_loop_hook(pl->mlx_ptr, playermove, &a);
	mlx_put_image_to_window(pl.mlx_ptr,pl.win_ptr,color_buffer_texture,0,0);
	mlx_loop(pl.mlx_ptr);
}