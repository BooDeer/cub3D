/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:55:00 by hboudhir          #+#    #+#             */
/*   Updated: 2020/10/30 01:25:47 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>
#include <limits.h>
#include "../cub3D/GNL/get_next_line.h"
#include "../cub3D/LIBFT/libft.h"


#define MINIMAP_SCALE 0.25
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 16
#define TILE_SIZE 64
#define WINDOW_WIDTH (TILE_SIZE * MAP_NUM_COLS)
#define WINDOW_HEIGHT (TILE_SIZE * MAP_NUM_ROWS)
#define FOV_ANGLE (60 * (M_PI / 180))
#define	WALL_WIDTH 1
#define NUM_RAYS (WINDOW_WIDTH * WALL_WIDTH)
#define WIDTH mapinfo->width
#define HEIGHT mapinfo->height
#define NO mapinfo->north_texture
#define SO mapinfo->south_texture
#define WE mapinfo->west_texture
#define EA mapinfo->east_texture
#define SP mapinfo->sprite_texture
#define F mapinfo->floor_color
#define C mapinfo->ceilling_color
#define	MAP_R mapinfo->map_reader
#define MAP mapinfo->map
#define	MFR mapinfo->map_first_read
#define	CP mapinfo->check_player
#define MAP_ROWS mapinfo->map_rows
#define MAP_COLUMNS mapinfo->map_columns
#define KEY_UP 13
#define KEY_DOWN 1
#define KEY_RIGHT 2
#define KEY_LEFT 0

typedef struct	s_list
{
	int		width;
	int		height;
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	char	*sprite_texture;
	int		floor_color[3];
	int		ceilling_color[3];
	char	*map_reader;
	char	**map;
	int		map_first_read;
	int		check_player;
    int     map_rows;
    int     map_columns;
}				t_mapdata;
typedef struct	s_rays
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
	
}	t_ray;

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
	void		*xpm_picture;
	int			*texture_buffer;
	int			texture_width;
	int			texture_height;
}	point;

void	    put_pixel(int x, int y, int color, void *img, t_mapdata *mapinfo);
void		reading_file(t_mapdata *mapinfo);
void	    struct_init(point *pl, t_mapdata *mapinfo);
void	draw_square(int x, int y,int width,int height,int color, point *pl, t_mapdata *mapinfo);
void	    draw_line(point *pl, int x1,int y1, t_mapdata *mapinfo);
int			reset_player(int key, point *pl);
void		castallRays(point *pl, t_mapdata *mapinfo);
void		castRayy(float rayAngle, int id, point *pl, t_mapdata *mapinfo);
void	    renderRays(point *pl, t_mapdata *mapinfo);
void		generate3dwalls(point *pl, t_mapdata *mapinfo);
void	    find_player(point *pl, t_mapdata *mapinfo);
int			arr_size(char **arr);
int 	    move_player(int key, point *pl, t_mapdata *mapinfo);
void		ft_init(t_mapdata *mapinfo);
t_ray       *g_rays;