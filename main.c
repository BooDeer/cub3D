/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/01/28 18:09:36 by hboudhir         ###   ########.fr       */
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
int		playerX = 0, playerY = 0;
void	*mlx_ptr;
void	*win_ptr;
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
				draw_square(i * TILE_SIZE,j * TILE_SIZE, TILE_SIZE, 0xff);
			}
			else if (!map[j][i])
				draw_square(i * TILE_SIZE,j * TILE_SIZE, TILE_SIZE, 0xff00);
			else if (!check++)
			{
				x = (i * TILE_SIZE) + TILE_SIZE / 2;
				y = (j * TILE_SIZE) + TILE_SIZE / 2;
				pl->x = x;
				pl->y = y;
				put_pixel(x, y, 0xffffff, color_buffer_texture);
				printf("%d\n%d\n", x, y);
			}
			
		}
	}
}
int 	move_player(int key, point *pl)
{
	if (key == 126)
	{
		pl->y -= TILE_SIZE / 4;
	}
	else if (key == 125)
		pl->y += TILE_SIZE / 4;
	else if (key == 124)
		pl->x += TILE_SIZE / 4;
	else if (key == 123)
		pl->x -= TILE_SIZE / 4;
	mlx_destroy_image(mlx_ptr, color_buffer_texture);
	color_buffer_texture = mlx_new_image(mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	mlx_clear_window(mlx_ptr, win_ptr);
	draw_map(pl);
	put_pixel(pl->x, pl->y, 0xffffff, color_buffer_texture);
	mlx_put_image_to_window(mlx_ptr, win_ptr, color_buffer_texture, 0, 0);
	return 0;
}

int		move_p(point *pl)
{
	mlx_hook(win_ptr, 2, 0, move_player,pl);
	printf("ppppp\n");
	return 0;
}

int		main()
{


	int		a;
	point pl;

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr,WINDOW_WIDTH, WINDOW_HEIGHT,"bruh");
	color_buffer_texture = mlx_new_image(mlx_ptr, WINDOW_WIDTH,WINDOW_HEIGHT);
	data = (int*)mlx_get_data_addr(color_buffer_texture, &a,&a,&a);
	draw_map(&pl);
	// mlx_hook(win_ptr, 2, 0, move_player,&pl);
	mlx_loop_hook(mlx_ptr, move_p, &pl);
	// mlx_loop_hook(mlx_ptr, playermove, &a);
	mlx_put_image_to_window(mlx_ptr,win_ptr,color_buffer_texture,0,0);
	mlx_loop(mlx_ptr);
}