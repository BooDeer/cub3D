/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:55:00 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/20 17:41:32 by hboudhir         ###   ########.fr       */
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
#define SCREEN g_mapinfo->screen_shot
#define	BUFFER buffer
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
	int				s_count;
	int				screen_shot;
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

typedef struct s_raynorm
{
	int		is_rayfacingdown;
	int		is_rayfacingup;
	int		is_rayfacingright;
	int		is_rayfacingleft;
	float	xintercept;
	float	yintercept;
	float	xstep;
	float	ystep;
	int		found_horzwallhit;
	float	horz_wallhitx;
	float	horzwallhity;
	int		horzwallcontent;
	float	nexthorztouchx;
	float 	nexthorztouchy;
	float 	xtocheck;
	float 	ytocheck;
	int		foundvertwallhit;
	float	vertwallhitx;
	float	vertwallhity;
	int		vertwallcontent;
	float 	nextVertTouchX;
	float 	nextVertTouchY;
	float 	horzHitDistance;
	float 	vertHitDistance;
}		t_raynorm;
typedef	struct	s_bmp_header
{
	char		bftype[3];
	u_int32_t	bfsize;
	u_int16_t	bfreserved1;
	u_int16_t	bfreserved2;
	u_int32_t	bfoffbits;
	u_int32_t	bisize;
	int32_t		biwidth;
	int32_t		biheight;
	u_int16_t	biplanes;
	u_int16_t	bibitcount;
	u_int32_t	bicompression;
	u_int32_t	bisizeimage;
	int32_t		bixpermeter;
	int32_t		biypermeter;
	u_int32_t	biclrused;
	u_int32_t	biclrimportant;
}				t_bmp_file;

typedef struct s_walls
{
	int		i;
	int		j;
	int		offsetx;
	int		offsety;
    int     txt;
	float 	perp_distance;
	float 	distance_projplane;
	float 	projected_wall_height;
	int		wall_stripheight;
	int 	wall_top_pixel;
	int 	wall_bottompixel;
	int		distance_fromtop;
}			t_walls;

typedef struct s_var
{
	int		i;
	int		j;
	int		c;
	float	size;
}			t_var;

void			put_pixel(int x, int y, int color);
int				reading_file(char *file);
void			struct_init(point *pl);
int				ft_init(t_mapdata *mapinfo, char *extension);
void			draw_square(int x, int y,int width,int color, point *pl);
int				reset_player(int key, point *pl);
void			castall_rays(point *pl);
void			cast_rayy(float ray_angle, int id, point *pl);
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
void			take_screenshot(void);
int				collision(int x, int y);
int				collision_player(int x, int y);
float			normalize_angle(float angle);
float			distance_between_points(float x1, float y1, float x2, float y2);
void			draw_sprite(point *pl);
void			ft_player_initial_pov(point *pl, int c);
void			draw_map(point *pl);
void			find_player(point *pl);
int				move_player(int key, point *pl);
void			fill_rays(t_raynorm *ray, point *pl, int id, float ray_angle);
void			update_player(point *pl);
t_mapdata 	*g_mapinfo;
t_ray       *g_rays;
int			*buffer;





