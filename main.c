/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/25 13:30:33 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>


struct	rays
{
	float	rayAngle;
	float	wallHitX;
	float	wallHitY;
	float	distance;
	int		wasHitVertical;
	int		isRayFacingUp;
	int		isRayFacingRight;
	int		isRayFacingDown;
	int		isRayFacingLeft;
	int		wallHitContent;
	
}	ray[NUM_RAYS];


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



int		Collision(int x, int y)
{
	int		indexX;
	int		indexY;

	indexX = x;
	indexY = y;
	if (indexX < 0 || indexX > WINDOW_WIDTH || indexY < 0 || indexY > WINDOW_HEIGHT)
		return (1);
	indexX = floor(indexX / TILE_SIZE);	
	indexY = floor(indexY / TILE_SIZE);	
	return (map[indexY][indexX] != 0 && map[indexY][indexX] != 5);
}

float	normalizeAngle(float angle)
{
	angle = remainder(angle , 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);

}

float	distanceBetweenPoints(float x1, float y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void 	draw_map(point *pl)
{
	int x, y;
	static int check;
		for (int i = 0; i < MAP_NUM_COLS; i++)
	{
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

				// draw_line(pl, pl->x + cos(pl->rotationAngle) * 50, pl->y + sin(pl->rotationAngle) * 50);
	}
					castallRays(pl);
	renderRays(pl);
}

void	renderRays(point *pl)
{
	for (int i = 0; i < NUM_RAYS; i++)
		draw_line(pl, ray[i].wallHitX, ray[i].wallHitY );
}
void	castRayy(float rayAngle, int id, point *pl)
{
	rayAngle = normalizeAngle(rayAngle);

	int		isRayFacingDown = rayAngle > 0 && rayAngle < M_PI;
	int		isRayFacingUp = !isRayFacingDown;
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
	ystep *= isRayFacingUp ? -1 : 1;

	xstep = TILE_SIZE / tan(rayAngle);
	xstep *= (isRayFacingLeft && xstep > 0) ? -1 : 1;
	xstep *= (isRayFacingRight && xstep < 0) ? -1 : 1;
	
	float nextHorzTouchX = xintercept;
	float nextHorzTouchY = yintercept;

	while (nextHorzTouchX >= 0 && nextHorzTouchX <= WINDOW_WIDTH && nextHorzTouchY >= 0 && nextHorzTouchY <= WINDOW_HEIGHT)
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (Collision(xToCheck, yToCheck))
		{
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundHorzWallHit = 1;
			break;
		}
		else
		{
			nextHorzTouchX += xstep;
			nextHorzTouchY += ystep;
		}
	
	}
	// put_pixel(horzWallHitX, horzWallHitY, 0xff0000, pl->color_buffer_texture);
	// printf("=======|%d|=======\n", NUM_RAYS);
	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////
	//////////////////////////////////////////////////////

	int		foundVertWallHit = 0;
	float	VertWallHitX = 0;
	float	VertWallHitY = 0;
	int		VertWallContent = 0;

	xintercept = floor(pl->x / TILE_SIZE) * TILE_SIZE;
	xintercept += isRayFacingRight ? TILE_SIZE : 0;

	yintercept = pl->y + (xintercept - pl->x) * tan(rayAngle);
	
	xstep = TILE_SIZE;
	xstep *= isRayFacingLeft ? -1 : 1;

	ystep = TILE_SIZE * tan(rayAngle);
	ystep *= (isRayFacingUp && xstep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && xstep < 0) ? -1 : 1;
	
	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	while (nextVertTouchX >= 0 && nextVertTouchX <= WINDOW_WIDTH && nextVertTouchY >= 0 && nextVertTouchY <= WINDOW_HEIGHT)
	{
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (Collision(xToCheck, yToCheck))
		{
			VertWallHitX = nextVertTouchX;
			VertWallHitY = nextVertTouchY;
			VertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
			foundVertWallHit = 1;
			break;
		}
		else
		{
			nextVertTouchX += xstep;
			nextVertTouchY += ystep;
		}
	
	}

	float horzHitDistance = foundHorzWallHit ? distanceBetweenPoints(pl->x, pl->y, horzWallHitX, horzWallHitY) : INT_MAX;
	float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(pl->x, pl->y, VertWallContent, VertWallHitY) : INT_MAX;
	if (vertHitDistance < horzHitDistance)
	{
		ray[id].distance = vertHitDistance;
		ray[id].wallHitX = VertWallHitX; 
		ray[id].wallHitY = VertWallHitY;
		ray[id].wallHitContent = VertWallContent;
		ray[id].wasHitVertical = 1;
	}
	else
	{
		ray[id].distance = horzHitDistance;
		ray[id].wallHitX = horzWallHitX; 
		ray[id].wallHitY = horzWallHitY;
		ray[id].wallHitContent = horzWallContent;
		ray[id].wasHitVertical = 0;		
	}
	ray[id].rayAngle = rayAngle;
	ray[id].isRayFacingDown = isRayFacingDown;
	ray[id].isRayFacingUp = isRayFacingUp;
	ray[id].isRayFacingRight = isRayFacingRight;
	ray[id].isRayFacingLeft = isRayFacingLeft;
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
	pl->y = pl->y + sin(pl->rotationAngle) * moveStep;
	if (Collision(pl->x, pl->y))
	{
		pl->x = oldPlayerx;
		pl->y = oldPlayery;
	}
	mlx_destroy_image(pl->mlx_ptr, pl->color_buffer_texture);
	pl->color_buffer_texture = mlx_new_image(pl->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	// mlx_clear_window(pl->mlx_ptr, pl->win_ptr);
	draw_map(pl);
	// castallRays(pl);
	// renderRays(pl);
	put_pixel(pl->x + cos(pl->rotationAngle), pl->y + sin(pl->rotationAngle), 0xffffff, pl->color_buffer_texture);
	mlx_put_image_to_window(pl->mlx_ptr, pl->win_ptr, pl->color_buffer_texture, 0, 0);
	return 0;
}

int	close_window(int key)
{
	exit(1);
	return (key);
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
	// void *img;

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