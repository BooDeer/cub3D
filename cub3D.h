/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:55:00 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/11 13:43:54 by hboudhir         ###   ########.fr       */
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


#define TILE_SIZE 64
#define FOV_ANGLE (60 * (M_PI / 180))
# define DEG(x) ((180 / M_PI) * x)
#define	WALL_WIDTH 1
#define NUM_RAYS (WINDOW_WIDTH * WALL_WIDTH)
#define WIDTH g_mapinfo->width
#define HEIGHT g_mapinfo->height
#define NO g_mapinfo->north_texture
#define SO g_mapinfo->south_texture
#define WE g_mapinfo->west_texture
#define EA g_mapinfo->east_texture
#define SP g_mapinfo->sprite_texture
#define F g_mapinfo->floor_color
#define C g_mapinfo->ceilling_color
#define	MAP_R g_mapinfo->map_reader
#define MAP g_mapinfo->map
#define	MFR g_mapinfo->map_first_read
#define	CP g_mapinfo->check_player
#define MAP_ROWS g_mapinfo->map_rows
#define MAP_COLUMNS g_mapinfo->map_columns
#define mapinfo g_mapinfo
#define TXT g_mapinfo->map_textures 
#define TXTP g_mapinfo->texture_pointers
#define TXT_W g_mapinfo->texture_width
#define TXT_H g_mapinfo->texture_height
#define FLOOR_COLOR g_mapinfo->floor
#define CEILING_COLOR g_mapinfo->ceiling
#define SPRITES g_mapinfo->sprites
#define S_COUNT g_mapinfo->s_count
#define S_HEIGHT g_mapinfo->sprite_height
#define S_WIDTH g_mapinfo->sprite_width
#define KEY_UP 13
#define KEY_DOWN 1
#define KEY_RIGHT 2
#define KEY_LEFT 0

typedef struct s_sprite
{
	float	x;
	float	x_off;
	float	y;
	float	y_off;
	float	dist;
	float	size;
	int		width;
	int		height;
	int		*sdata;
	int		useless;
	void	*simg;
}			t_sprite;

// typedef	struct s_sprite
// {
// 	float	x;
// 	float	y;
// 	float	distance;
// }				t_sprite;

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
	int    *map_textures[4];
	void   *texture_pointers[4];
	int		sprite_width;
	int		sprite_height;
	int    texture_width[4];
	int     texture_height[4];
	unsigned long	floor;
	unsigned long	ceiling;
	t_sprite		*sprites;
	// t_sprite		sprite[500];
	int				s_count;
}				t_mapdata;

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
	
}	        t_ray;

void			put_pixel(int x, int y, int color);
int				reading_file(t_mapdata *mapinfo);
void			struct_init(point *pl);
void			ft_init(t_mapdata *mapinfo);
void			draw_square(int x, int y,int width,int color, point *pl);
int				reset_player(int key, point *pl);
void			castallRays(point *pl);
void			castRayy(float rayAngle, int id, point *pl);
void			renderRays(point *pl);
void			generate3dwalls(point *pl);
void			find_player(point *pl);
int				arr_size(char **arr);
int				move_player(int key, point *pl);
size_t			ft_strlen2(char *s);
int				str_isdigit(char *str);
int				arr_size(char **arr);
int				free_struct(t_mapdata *mapinfo, char *line);
int				check_color_parametre(char *param);
int				error_message(char *error);
int				fill_color_values(char *arr, t_mapdata *mapinfo, int f_or_c, int i);
void			init_sprit(point *pl);
t_mapdata 	*g_mapinfo;
t_ray       *g_rays;
int			*data;
void		*buffer;





