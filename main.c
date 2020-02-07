/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/07 06:54:56 by hboudhir         ###   ########.fr       */
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
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};
void	*color_buffer_texture;
int		*data;

float		abso(float n)
{
	return ((n > 0) ? n : (n * -1));
}

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
		j = -1;
		while(++j < width)
			put_pixel((j + x), (i + y), color, color_buffer_texture);
		i++;
	}		
}

/*void	draw_line(point *pl)
{
	float dx, dy, step, x1 ,y1;
	int		i;

	// pl->rotationAngle = pl->turnDirection * pl->rotationSpeed;
	x1 = floor(50 * cos(pl->rotationAngle) + pl->x);
	y1 = floor(50 * sin(pl->rotationAngle) + pl->y);
	printf("%f|%f\n", x1, y1);
	//printf("%f\n",  pl->rotationAngle);
	i = -1;
	dx = x1 - pl->x;
	dy = y1 - pl->y;

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
}*/

void
draw_line(point *pl, int x1, int y1)
{
	int x0 = (int)floor(pl->x);
	int y0 = (int)floor(pl->y); 
  int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
  int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1; 
  int err = dx + dy, e2; /* error value e_xy */
 
  for (;;){  /* loop */
    put_pixel(x0,y0, 0xffffff, color_buffer_texture);
    if (x0 == x1 && y0 == y1) break;
    e2 = 2 * err;
    if (e2 >= dy) { err += dy; x0 += sx; } /* e_xy+e_x > 0 */
    if (e2 <= dx) { err += dx; y0 += sy; } /* e_xy+e_y < 0 */
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
				// printf("%d\n%d\n", x, y);
			}
			
		}
	}
}

int 	move_player(int key, point *pl)
{
	float	moveStep, newPlayerx, newPlayery;


	// printf("%d\n", key);
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
	else if (key == 124)
		pl->rotationAngle += M_PI / 2;
	else if (key == 123)
		pl->rotationAngle -= M_PI / 2;
	mlx_destroy_image(pl->mlx_ptr, color_buffer_texture);
	color_buffer_texture = mlx_new_image(pl->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// mlx_clear_window(pl->mlx_ptr, pl->win_ptr);
	draw_map(pl);

	
	put_pixel(pl->x, pl->y, 0xffffff, color_buffer_texture);
	int x1 = (int)floor(pl->x + cos(pl->rotationAngle) * 50);
	int y1 = (int)floor(pl->y + sin(pl->rotationAngle) * 50);

	draw_line(pl, x1, y1);
	mlx_put_image_to_window(pl->mlx_ptr, pl->win_ptr, color_buffer_texture, 0, 0);
	return 0;
}

int	reset_player(int key, point *pl)
{
	struct_init(pl);
	return(0);
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
	struct_init(&pl);
	draw_map(&pl);
	// mlx_hook(pl->win_ptr, 2, 0, move_player,&pl);
	mlx_loop_hook(pl.mlx_ptr, move_p, &pl);


	// img = mlx_xpm_file_to_image(pl->mlx_ptr, "~/Downloads/81621207_667657023772881_3948275671851073536_n.png", &a, &a);

	
	// mlx_loop_hook(pl->mlx_ptr, playermove, &a);
	mlx_put_image_to_window(pl.mlx_ptr,pl.win_ptr,color_buffer_texture,0,0);
	mlx_loop(pl.mlx_ptr);
}