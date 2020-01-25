/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/01/25 15:42:16 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
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
// void	*create_block()
// {
			
// }

void draw_square(int x, int y,int width,int color)
{
	int i = 0, j;
	while(i < width)
	{
		j = 0;
		while(j < width)
		{
			data[((i + y) * WINDOW_WIDTH)	+(j + x)] = color;
			j++;
		}
		i++;
	}		
}

int		main()
{

	void	*mlx_ptr;
	void	*win_ptr;
	int		a;
	
	

	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr,WINDOW_WIDTH, WINDOW_HEIGHT,"bruh1");
	color_buffer_texture = mlx_new_image(mlx_ptr, WINDOW_WIDTH,WINDOW_HEIGHT);
	data = (int*)mlx_get_data_addr(color_buffer_texture, &a,&a,&a);
	//mlx_put_image_to_window(mlx_ptr,win_ptr,color_buffer_texture,0,0);
		
	for (int i = 0; i < MAP_NUM_COLS; i++)
	{
		int j = 0;
		for (int j = 0; j < MAP_NUM_ROWS; j++)
		{
			if(map[j][i] == 1)
			{
				//printf("%d;%d\n",i,j);
				draw_square(i * TILE_SIZE,j * TILE_SIZE, TILE_SIZE, 0xff);
			}
			//else
			//	draw_square(i * TILE_SIZE,j * TILE_SIZE, 10, 0xff00ff);
			//printf("%d;%d\n",i,j);
			// else
				//draw_square(i * TILE_SIZE,j * TILE_SIZE, TILE_SIZE, 0);
	// 		map[i][j] == 1 ? 
	// 		mlx_pixel_put(mlx_ptr, mlx_win, i * WINDOW_WIDTH/MAP_NUM_ROWS, j * WINDOW_WIDTH/MAP_NUM_COLS, 255255255) 
	// 		: mlx_pixel_put(mlx_ptr, mlx_win, i * WINDOW_WIDTH/MAP_NUM_ROWS, j * WINDOW_WIDTH/MAP_NUM_COLS, 255);
		}
	}
	//draw_square(100,100,100,0x99ffff);	
	mlx_put_image_to_window(mlx_ptr,win_ptr,color_buffer_texture,0,0);
	// mlx_pixel_put(mlx_ptr, mlx_win, 0, 0, 0xFFFFFF);
	// mlx_new_image(mlx_ptr, 100, 100);
	mlx_loop(mlx_ptr);
}