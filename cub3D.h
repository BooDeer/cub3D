/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:55:00 by hboudhir          #+#    #+#             */
/*   Updated: 2020/03/07 21:22:15 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <limits.h>

#define MINIMAP_SCALE 0.25
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define TILE_SIZE (64 * 2)
#define WINDOW_WIDTH (TILE_SIZE * MAP_NUM_COLS)
#define WINDOW_HEIGHT (TILE_SIZE * MAP_NUM_ROWS)
#define FOV_ANGLE (60 * (M_PI / 180))
#define	WALL_WIDTH 1
#define NUM_RAYS (WINDOW_WIDTH * WALL_WIDTH)

typedef struct	s_list
{
	int width;
	int height;
}				t_mapdata;

#define WIDTH mapinfo->width
#define HEIGHT mapinfo->height

typedef struct player
{
	float		x;
	float		y;
	float		radius;
	int			turnDirection;
	int			walkDirection;
	float		rotationAngle;
	float		moveSpeed;
	float		rotationSpeed;
	float		turnSpeed;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*color_buffer_texture;
}	point;

void		put_pixel(int x, int y, int color, void *img);
void		reading_file(int fd);
void		struct_init(point *pl);
void		draw_square(int x, int y,int width,int color, point *pl);
void		draw_line(point *pl, int x1, int y1);
int			reset_player(int key, point *pl);
void		castallRays(point *pl);
void		castRayy(float rayAngle, int id, point *pl);
void		renderRays(point *pl);
void		generate3dwalls(point *pl);
void		find_player(point *pl);



