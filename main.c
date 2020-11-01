/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/01 18:52:20 by hboudhir         ###   ########.fr       */
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
double	f_mod(double a, double b)
{
	return (a - (floor(a/b) * b));
}

int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
			{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};



int		Collision(int x, int y)
{
	int		indexX;
	int		indexY;

	indexX = x;
	indexY = y;
	if (indexX < 0 || indexX / TILE_SIZE > MAP_ROWS || indexY < 0 || indexY / TILE_SIZE > MAP_COLUMNS)
		return (1);
	indexX = floor(indexX / TILE_SIZE);	
	indexY = floor(indexY / TILE_SIZE);
	// printf("%d============%d\n", indexX, indexY);
	return (MAP[indexY][indexX] == '1');
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

void 	 draw_map(point *pl)
{

	int x, y;
	static int check;

	castallRays(pl);
	generate3dwalls(pl);

	for (int i = 0; i < MAP_ROWS; i++)
	{
		for (int j = 0; j < MAP_COLUMNS; j++)
		{
			if(MAP[j][i] == '1')
				draw_square(i * TILE_SIZE * MINIMAP_SCALE, j * TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, 0xffff, pl);
            else if (MAP[j][i] == '0')
				draw_square(i * TILE_SIZE * MINIMAP_SCALE,j * TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, 0x000000, pl);
			else if (ft_strchr("NEWS", MAP[j][i]))
			{
				draw_square(i * TILE_SIZE * MINIMAP_SCALE , j * TILE_SIZE * MINIMAP_SCALE, TILE_SIZE * MINIMAP_SCALE, 0x000000, pl);
				
				if (!check++)
				{
					x = (i * TILE_SIZE) + TILE_SIZE / 2;
					y = (j * TILE_SIZE) + TILE_SIZE / 2;
					pl->x = x;
					pl->y = y;
					put_pixel(MINIMAP_SCALE * x + cos(pl->rotationAngle),MINIMAP_SCALE * y, 0xff0000 + cos(pl->rotationAngle), pl->color_buffer_texture);
				}
			}
			
		}

		draw_line(pl, (pl->x * MINIMAP_SCALE) + cos(pl->rotationAngle) * 50, (pl->y * MINIMAP_SCALE) + sin(pl->rotationAngle) * 50);
	}

	renderRays(pl);
}

void	find_player(point *pl)
{
	int		i;
	int		j;

	i = -1;
	while (++i < MAP_ROWS)
	{
		j = -1;
		while (++j < MAP_COLUMNS)
			if (ft_strchr("NEWS", MAP[j][i]))
			{
				pl->x = (i * TILE_SIZE) + TILE_SIZE / 2;
				pl->y = (j * TILE_SIZE) + TILE_SIZE / 2;
			// printf("%d <====================> %d\n", i, j);
			}
	}
}
void			generate3dwalls(point *pl)
{
	int		*tmp;
	int		k;
	tmp = (int *)mlx_get_data_addr(pl->color_buffer_texture, &k, &k, &k);
	int		textureOffsetX, textureOffsetY;

	for (int i = 0; i < WIDTH; i++)
	{
		float perpDistance = g_rays[i].distance * cos(g_rays[i].rayAngle - pl->rotationAngle);
		float distanceProjPlane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
		float projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

		int		wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;

		for (int y = 0; y < wallTopPixel; y++)
			tmp[i + (WIDTH * y)] = 0x0000FF;
			if (g_rays[i].wasHitVertical)
				textureOffsetX = f_mod(g_rays[i].wallHitY, TILE_SIZE) * (pl->texture_width / TILE_SIZE);
		else
			textureOffsetX = f_mod(g_rays[i].wallHitX, TILE_SIZE)  * (pl->texture_width / TILE_SIZE);
			
		float		test;
		float	step;
		test = 0;
		step = pl->texture_height / HEIGHT;
		for (int y = wallTopPixel; y < wallBottomPixel; y++)
		{
			int		distanceFromTop = y +  (wallStripHeight / 2) - (HEIGHT / 2);
			
			textureOffsetY = distanceFromTop * ((float)pl->texture_height / wallStripHeight);

			tmp[i + ((WIDTH) * y)] = pl->texture_buffer[textureOffsetX + (textureOffsetY * pl->texture_width)];

		}
		for (int y = wallBottomPixel; y < HEIGHT; y++)
			tmp[i + (WIDTH * y)] = 0x00000E;
	}
}
void	renderRays(point *pl)
{
	for (int i = 0; i < WIDTH; i++)
		draw_line(pl, MINIMAP_SCALE * g_rays[i].wallHitX, MINIMAP_SCALE * g_rays[i].wallHitY);
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

	while (nextHorzTouchX >= 0 && nextHorzTouchX / TILE_SIZE <= MAP_ROWS && nextHorzTouchY >= 0 && nextHorzTouchY / TILE_SIZE <= MAP_COLUMNS)
	{
		float xToCheck = nextHorzTouchX;
		float yToCheck = nextHorzTouchY + (isRayFacingUp ? -1 : 0);

		if (Collision(xToCheck, yToCheck))
		{
			horzWallHitX = nextHorzTouchX;
			horzWallHitY = nextHorzTouchY;
			// horzWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
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
	ystep *= (isRayFacingUp && ystep > 0) ? -1 : 1;
	ystep *= (isRayFacingDown && ystep < 0) ? -1 : 1;
	
	float nextVertTouchX = xintercept;
	float nextVertTouchY = yintercept;

	while (nextVertTouchX >= 0 && nextVertTouchX / TILE_SIZE <= MAP_ROWS && nextVertTouchY >= 0 && nextVertTouchY / TILE_SIZE <= MAP_COLUMNS)
	{
		float xToCheck = nextVertTouchX + (isRayFacingLeft ? -1 : 0);
		float yToCheck = nextVertTouchY;

		if (Collision(xToCheck, yToCheck))
		{
			VertWallHitX = nextVertTouchX;
			VertWallHitY = nextVertTouchY;
			// VertWallContent = map[(int)floor(yToCheck / TILE_SIZE)][(int)floor(xToCheck / TILE_SIZE)];
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
	float vertHitDistance = foundVertWallHit ? distanceBetweenPoints(pl->x, pl->y, VertWallHitX, VertWallHitY) : INT_MAX;
	if (vertHitDistance < horzHitDistance)
	{
		g_rays[id].distance = vertHitDistance;
		g_rays[id].wallHitX = VertWallHitX; 
		g_rays[id].wallHitY = VertWallHitY;
		g_rays[id].wallHitContent = VertWallContent;
		g_rays[id].wasHitVertical = 1;
	}
	else
	{
		g_rays[id].distance = horzHitDistance;
		g_rays[id].wallHitX = horzWallHitX; 
		g_rays[id].wallHitY = horzWallHitY;
		g_rays[id].wallHitContent = horzWallContent;
		g_rays[id].wasHitVertical = 0;		
	}
	g_rays[id].rayAngle = rayAngle;
	g_rays[id].isRayFacingDown = isRayFacingDown;
	g_rays[id].isRayFacingUp = isRayFacingUp;
	g_rays[id].isRayFacingRight = isRayFacingRight;
	g_rays[id].isRayFacingLeft = isRayFacingLeft;	
}


int 	move_player(int key, point *pl)
{
	float	moveStep, oldPlayerx, oldPlayery;
	oldPlayerx = pl->x;
	oldPlayery = pl->y;
	// printf("====ddddddd==== %d\n", key);
	if (key == 13)
	{
		pl->walkDirection = 1;
	}
	if (key == 1)
	{
		pl->walkDirection = -1;
	}
	if (key == 2)
	{
		pl->turnDirection = 1;
	}
	if (key == 0)
	{
		pl->turnDirection = -1;
	}
	if (key == 53)
		exit(1);
	if (key == 124)
		pl->rotationAngle += M_PI / 20;
	if (key == 123)
		pl->rotationAngle -= M_PI / 20;

	// pl->rotationAngle += pl->turnDirection * pl->turnSpeed;
	moveStep = pl->walkDirection * pl->moveSpeed;
	
	pl->x = pl->x + cos(pl->rotationAngle) * moveStep;
	pl->y = pl->y + sin(pl->rotationAngle) * moveStep;
	if (Collision(pl->x, pl->y))
	{
		pl->x = oldPlayerx;
		pl->y = oldPlayery;
	}
	mlx_destroy_image(pl->mlx_ptr, pl->color_buffer_texture);
	pl->color_buffer_texture = mlx_new_image(pl->mlx_ptr, WIDTH, HEIGHT);
	// mlx_clear_window(pl->mlx_ptr, pl->win_ptr);	
	draw_map(pl);
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
	mlx_hook(pl->win_ptr, 2, 0, move_player, pl);
	mlx_hook(pl->win_ptr, 3, 0, reset_player, pl);
	mlx_hook(pl->win_ptr, 17, 0, close_window, pl);
	return 0;
}


int		main()
{

	point pl;
	int 	useless;
	mapinfo = malloc(sizeof(t_mapdata));
	if (!mapinfo)
		return (-1);
	ft_init(mapinfo);
	reading_file(mapinfo);
    pl.mlx_ptr = mlx_init();
    pl.win_ptr = mlx_new_window(pl.mlx_ptr,WIDTH, HEIGHT,"bruh");
    pl.color_buffer_texture = mlx_new_image(pl.mlx_ptr, WIDTH,HEIGHT);
    struct_init(&pl);
    pl.xpm_picture = mlx_xpm_file_to_image(pl.mlx_ptr, "picture_3.xpm", &pl.texture_width, &pl.texture_height);
    printf("%d===========%d\n", pl.texture_width, pl.texture_height);
    pl.texture_buffer = (int *)mlx_get_data_addr(pl.xpm_picture, &useless, &useless, &useless);
    draw_map(&pl);
    mlx_loop_hook(pl.mlx_ptr, move_p, &pl);
    mlx_put_image_to_window(pl.mlx_ptr,pl.win_ptr,pl.color_buffer_texture,0,0);
    mlx_loop(pl.mlx_ptr);
}