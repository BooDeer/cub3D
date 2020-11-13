/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/13 11:55:46 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>


double	f_mod(double a, double b)
{
	return (a - (floor(a/b) * b));
}


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

int		Collision_player(int x, int y)
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
	return (MAP[indexY][indexX] == '1' || MAP[indexY][indexX] == '2');
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

void	 sort_sprites(void)
{
	int		i;
	int		j;
	float	tmp_dist;
	float	tmp_x;
	float	tmp_y;

	i = -1;
	while (++i < S_COUNT)
	{
		j = -1;
		while (++j < S_COUNT - i)
		if (SPRITES[j].dist < SPRITES[j + 1].dist)
		{
			tmp_dist = SPRITES[j].dist;
			tmp_x = SPRITES[j].x;
			tmp_y = SPRITES[j].y;
			SPRITES[j].dist = SPRITES[j + 1].dist;
			SPRITES[j].x = SPRITES[j + 1].x;
			SPRITES[j].y = SPRITES[j + 1].y;
			SPRITES[j + 1].dist = tmp_dist;
			SPRITES[j + 1].x = tmp_x;
			SPRITES[j + 1].y = tmp_y;
		}
	}
}

void	generate_sprites(int id, point *pl)
{
	int		i;
	int		j;
	int		c;
	float	size;
	int 	k;
	int		*tmp = (int *)mlx_get_data_addr(pl->color_buffer_texture, &k, &k, &k);
	i = -1;
	size = SPRITES[id].size;
	while (++i < size - 1)
	{
		if (SPRITES[id].x_off + i <= 0 || SPRITES[id].x_off + i >= WIDTH)
			continue ;
		if ((int)g_rays[(int)SPRITES[id].x_off + i].distance <= SPRITES[id].dist)
			continue ;
		j = -1;
		while (++j < size - 1)
		{
			if (SPRITES[id].y_off + j <= 0 || SPRITES[id].y_off + j >= HEIGHT)
				continue ;
			c = SPRITES->sdata[(int)((TILE_SIZE) * (TILE_SIZE * j / (int)size) + (TILE_SIZE * i / (int)size))];
			// printf("I don't know what's this but whatever: %d\n", SPRITES->sdata[(int)((TILE_SIZE) * (TILE_SIZE * j / (int)size) + (TILE_SIZE * i / (int)size))]);
			if (c != SPRITES->sdata[0])
				tmp[(int)((j + SPRITES[id].y_off) *
				WIDTH + (i + SPRITES[id].x_off))] = c;
		}
	}
}

void	 draw_sprite(point *pl)
{
	float	angle;
	int		k;

	k = -1;
	sort_sprites();
	while (++k < S_COUNT)
	{
		SPRITES[k].dist = sqrtf(((SPRITES[k].x) - pl->x) * ((SPRITES[k].x) - pl->x) + ((SPRITES[k].y) - pl->y) * ((SPRITES[k].y) - pl->y));
		angle = atan2f(SPRITES[k].y - pl->y, SPRITES[k].x - pl->x);
		while (angle - pl->rotationAngle > M_PI)
			angle -= 2 * M_PI;
		while (angle - pl->rotationAngle < -M_PI)
			angle += 2 * M_PI;
		if (HEIGHT > WIDTH)
			SPRITES[k].size = (HEIGHT / SPRITES[k].dist) * TILE_SIZE;
		else
			SPRITES[k].size = (WIDTH / SPRITES[k].dist) * TILE_SIZE;
		SPRITES[k].y_off = HEIGHT / 2 - (int)SPRITES[k].size / 2;
		SPRITES[k].x_off = ((DEG(angle) - DEG(pl->rotationAngle)) * WIDTH)
		/ (float)TILE_SIZE + ((WIDTH / 2) - (int)SPRITES[k].size / 2);
		// printf("The sprite's size: %f\n", SPRITES[k].x_off);
		// ((angle * (M_PI / 180)) - (pl->rotationAngle * (M_PI / 180)) * WIDTH)
		// 					/ (float)TILE_SIZE + ((WIDTH / 2) - (int)SPRITES[k].size / 2);
		generate_sprites(k, pl);
			
	}
}

void 	 draw_map(point *pl)
{


	castallRays(pl);
	generate3dwalls(pl);
	pl->rotationAngle = fmod(pl->rotationAngle, 2 * M_PI);
	if (pl->rotationAngle < 0)
		pl->rotationAngle += 2 * M_PI;
	draw_sprite(pl);

}

void    ft_player_initial_pov(point *pl, int c)
{
    if (c == 'N')
        pl->rotationAngle = -90 * (M_PI / 180);
    if (c == 'E')
        pl->rotationAngle = 0 * (M_PI / 180);
    if (c == 'W')
        pl->rotationAngle = 180 * (M_PI / 180);
    if (c == 'S')
        pl->rotationAngle = 90 * (M_PI / 180);
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
                ft_player_initial_pov(pl, MAP[j][i]);
                break ;
			}
	}
}

void            ft_which_texture(int *txt, int i)
{
    if (g_rays[i].isRayFacingUp && !g_rays[i].wasHitVertical)
        *txt = 0;
    else if (g_rays[i].isRayFacingDown && !g_rays[i].wasHitVertical)
        *txt = 1;
    else if (g_rays[i].isRayFacingLeft&& g_rays[i].wasHitVertical)
        *txt = 2;
    else if (g_rays[i].isRayFacingRight&& g_rays[i].wasHitVertical)
        *txt = 3;
}
void			generate3dwalls(point *pl)
{
	int		*tmp;
	int		k;
	tmp = (int *)mlx_get_data_addr(pl->color_buffer_texture, &k, &k, &k);
	int		textureOffsetX, textureOffsetY;
    int     txt;
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
            tmp[i + (WIDTH * y)] = CEILING_COLOR;
		
        //// check achmen texture
        ft_which_texture(&txt, i);
        if (g_rays[i].wasHitVertical)
			textureOffsetX = f_mod(g_rays[i].wallHitY, TILE_SIZE) * (TXT_W[txt] / TILE_SIZE);
		else
			textureOffsetX = f_mod(g_rays[i].wallHitX, TILE_SIZE)  * (TXT_W[txt] / TILE_SIZE);

        
		for (int y = wallTopPixel; y < wallBottomPixel; y++)
		{
			int		distanceFromTop = y +  (wallStripHeight / 2) - (HEIGHT / 2);
			
			textureOffsetY = distanceFromTop * ((float)TXT_H[txt]/ wallStripHeight);

			tmp[i + ((WIDTH) * y)] = TXT[txt][textureOffsetX + (textureOffsetY * TXT_W[txt])]; // ray_up && vertical , ray_up && horizontal, ray_down && vertical hit, ray_down && horiz

		}
		for (int y = wallBottomPixel; y < HEIGHT; y++)
			tmp[i + (WIDTH * y)] = FLOOR_COLOR;
	}
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

	while (nextHorzTouchX > 0 && nextHorzTouchX / TILE_SIZE < MAP_ROWS && nextHorzTouchY > 0 && nextHorzTouchY / TILE_SIZE < MAP_COLUMNS)
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

	while (nextVertTouchX > 0 && nextVertTouchX / TILE_SIZE < MAP_ROWS && nextVertTouchY > 0 && nextVertTouchY / TILE_SIZE < MAP_COLUMNS)
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
	if (key == 13)
		pl->walkDirection = 1;
	if (key == 1)
		pl->walkDirection = -1;
	if (key == 53)
		exit(1);
		if (key == 124)
			pl->rotationAngle += normalizeAngle(M_PI / 50);
		if (key == 123)
			pl->rotationAngle -= normalizeAngle(M_PI / 50);

	float	moveStep, oldPlayerx, oldPlayery;
	oldPlayerx = pl->x;
	oldPlayery = pl->y;
	moveStep = pl->walkDirection * pl->moveSpeed;
	pl->x = pl->x + (cos(pl->rotationAngle) * moveStep);
	pl->y = pl->y + (sin(pl->rotationAngle) * moveStep);
	if (Collision_player(pl->x, oldPlayery))
		pl->x = oldPlayerx;
	if (Collision_player(oldPlayerx, pl->y))
    	pl->y = oldPlayery;

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
	mlx_destroy_image(pl->mlx_ptr, pl->color_buffer_texture);
	pl->color_buffer_texture = mlx_new_image(pl->mlx_ptr, WIDTH, HEIGHT);
	draw_map(pl);
	mlx_put_image_to_window(pl->mlx_ptr, pl->win_ptr, pl->color_buffer_texture, 0, 0);

	
	return 0;
}

void    ft_fill_textures(point *pl)
{
    int i;
	int 	useless;

    i = -1;
    //printf("%s=====\n%s======\n", NO, SO);
    TXTP[0] = mlx_xpm_file_to_image(pl->mlx_ptr, NO, &TXT_W[0], &TXT_H[0]);
    TXTP[1] = mlx_xpm_file_to_image(pl->mlx_ptr, SO, &TXT_W[1], &TXT_H[1]);
    TXTP[2] = mlx_xpm_file_to_image(pl->mlx_ptr, WE, &TXT_W[2], &TXT_H[2]);
    TXTP[3] = mlx_xpm_file_to_image(pl->mlx_ptr, EA, &TXT_W[3], &TXT_H[3]);
    while (++i < 4)
        TXT[i] = (int *)mlx_get_data_addr(TXTP[i],&useless, &useless, &useless); 
}

void	init_sprit(point *pl)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	k = 0;
	if (!(SPRITES = malloc(sizeof(t_sprite) * (S_COUNT + 1))))
		error_message("Error\nFailed to allocate memory");
	SPRITES->simg = mlx_xpm_file_to_image(pl->mlx_ptr, SP, &S_WIDTH, &S_HEIGHT);
	SPRITES->sdata = (int *)mlx_get_data_addr(SPRITES->simg,&SPRITES->useless, &SPRITES->useless, &SPRITES->useless);
	while (MAP[++i] != 0 && (j = -1) && (k < S_COUNT))
		while (MAP[i][++j] && (k < S_COUNT))
			if (MAP[i][j] == '2')
			{
				SPRITES[k].x = (j + 0.5) * TILE_SIZE;
				SPRITES[k].y = (i + 0.5) * TILE_SIZE;
				SPRITES[k].dist = sqrtf(((SPRITES[k].x) - pl->x) * ((SPRITES[k].x) - pl->x) +
				((SPRITES[k].y) - pl->y) * ((SPRITES[k].y) - pl->y));
				k++;
			}
}

int		main()
{

	point pl;
	mapinfo = malloc(sizeof(t_mapdata));
	if (!mapinfo)
		return (-1);
	ft_init(mapinfo);
	if (reading_file(mapinfo))
        return (-1);
    g_rays = (t_ray *)malloc(sizeof(t_ray) * WIDTH);
    pl.mlx_ptr = mlx_init();
    pl.win_ptr = mlx_new_window(pl.mlx_ptr,WIDTH, HEIGHT,"bruh");
    pl.color_buffer_texture = mlx_new_image(pl.mlx_ptr, WIDTH,HEIGHT);
    struct_init(&pl);
    ft_fill_textures(&pl);
	init_sprit(&pl);
    draw_map(&pl);
    mlx_loop_hook(pl.mlx_ptr, move_p, &pl);
    mlx_put_image_to_window(pl.mlx_ptr,pl.win_ptr,pl.color_buffer_texture,0,0);
    mlx_loop(pl.mlx_ptr);
    free(mapinfo);
    free(g_rays);
}