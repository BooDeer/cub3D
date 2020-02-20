/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/20 20:27:59 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

int		*data;


float	normalizeAngle(float angle)
{
	angle = remainder(angle , 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);

}

void	castallRays(point *pl)
{
	float		rayAngle;
	int			i;

	rayAngle = pl->rotationAngle - (FOV_ANGLE / 2);
	i = -1;
	while (++i < NUM_RAYS)
	{
		castRay(rayAngle, i, pl);
		rayAngle += FOV_ANGLE / NUM_RAYS;
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
				draw_square(i * TILE_SIZE * MINIMAP_SCALE,j * TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, 0xff, pl);
			}
			else if (!map[j][i])
				draw_square(i * TILE_SIZE * MINIMAP_SCALE,j * TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, 0x000000, pl);
			else if (!check++)
			{
				x = (i * TILE_SIZE) + TILE_SIZE / 2;
				y = (j * TILE_SIZE) + TILE_SIZE / 2;
				pl->x = x;
				pl->y = y;
				put_pixel(x, y, 0xffffff, pl->color_buffer_texture);
			}
			
		}
				draw_square(0,0, TILE_SIZE * MINIMAP_SCALE, 0xff, pl);

				draw_line(pl);
	}
}

void	castRay(float rayAngle, point *pl)
{
	rayAngle = normalizeAngle(rayAngle);

	int		isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	int		isRayFacingnUp = !isRayFacingDown;
	int		isRayFacingRight = rayAngle < 0.5 * M_PI || rayAngle > 1.5 * M_PI;
	int		isRayFacingLeft = !isRayFacingRight;

	float xintercept, yintercept;
	float xstep, ystep;

	int		foundHorzWallHit = 0;
	float	horzWallHitX = 0;
	float	horzWallHitY = 0;
	int		horzWallContent = 0;

	yintercept = floor(pl->y / TILE_SIZE) * TILE_SIZE;
	yintercept += isRayFacingDown ? TILE_SIZE : 0;

	xintercept = pl->x + (yintercept - pl->y) / tan(rayAngle);
	
	ystep = TILE_SIZE;
	ystep *= isRayFacingnUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;
	
	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT)
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingnUp ? -1 : 0);

		if (mapHasWallAt(xToCheck, yToCheck))
		{
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)]
		}
	}
}

int		Collision(point *pl)
{
	int		indexX;
	int		indexY;

	indexX = pl->x;
	indexY = pl->y;
	if (indexX < 0 || indexX > WINDOW_WIDTH || indexY < 0 || indexY > WINDOW_HEIGHT)
		return (1);
	indexX = floor(indexX / TILE_SIZE);	
	indexY = floor(indexY / TILE_SIZE);	
	return (map[indexY][indexX] != 0 && map[indexY][indexX] != 5);
}

int 	move_player(int key, point *pl)
{
	float	moveStep, oldPlayerx, oldPlayery;
	oldPlayerx = pl->x;
	oldPlayery = pl->y;
	if (key == 13)
	{
		pl->walkDirection = 1;
	}
	else if (key == 1)
	{
		pl->walkDirection = -1;
	}
	else if (key == 2)
	{
		pl->turnDirection = 1;
	}
	else if (key == 0)
	{
		pl->turnDirection = -1;
	}
	else if (key == 53)
		exit(1);
	else if (key == 124)
		pl->rotationAngle += M_PI / 20;
	else if (key == 123)
		pl->rotationAngle -= M_PI / 20;

	pl->rotationAngle += pl->turnDirection * pl->turnSpeed;
	moveStep = pl->walkDirection * pl->moveSpeed;
	pl->x = pl->x + cos(pl->rotationAngle) * moveStep;
	printf("|%d| <===================\n", pl->turnDirection);
	pl->y = pl->y + sin(pl->rotationAngle) * moveStep;
	if (Collision(pl))
	{
		pl->x = oldPlayerx;
		pl->y = oldPlayery;
	}
	mlx_destroy_image(pl->mlx_ptr, pl->color_buffer_texture);
	pl->color_buffer_texture = mlx_new_image(pl->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// mlx_clear_window(pl->mlx_ptr, pl->win_ptr);
	draw_map(pl);
	// printf("|%f|,|%f|\n",)
	put_pixel(pl->x + cos(pl->rotationAngle), pl->y + sin(pl->rotationAngle), 0xffffff, pl->color_buffer_texture);
	mlx_put_image_to_window(pl->mlx_ptr, pl->win_ptr, pl->color_buffer_texture, 0, 0);
	return 0;
}

int	close_window(int key, point *pl)
{
	exit(1);
	return (0);
}

int		move_p(point *pl)
{
	mlx_hook(pl->win_ptr, 2, 0, move_player,pl);
	mlx_hook(pl->win_ptr, 3, 0, reset_player, pl);
	mlx_hook(pl->win_ptr, 17, 0, close_window, pl);
	return 0;
}

int		main()
{


	int		a;
	point pl;
	void *img;

	pl.mlx_ptr = mlx_init();
	pl.win_ptr = mlx_new_window(pl.mlx_ptr,WINDOW_WIDTH, WINDOW_HEIGHT,"bruh");
	pl.color_buffer_texture = mlx_new_image(pl.mlx_ptr, WINDOW_WIDTH,WINDOW_HEIGHT);
	data = (int*)mlx_get_data_addr(pl.color_buffer_texture, &a,&a,&a);
	struct_init(&pl);
	draw_map(&pl);
	// mlx_hook(pl->win_ptr, 2, 0, move_player,&pl);
	mlx_loop_hook(pl.mlx_ptr, move_p, &pl);
	mlx_put_image_to_window(pl.mlx_ptr,pl.win_ptr,pl.color_buffer_texture,0,0);
	mlx_loop(pl.mlx_ptr);
}