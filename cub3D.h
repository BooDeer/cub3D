/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:55:00 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/25 12:52:23 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <mlx.h>
# include <math.h>
# include <limits.h>
# include "get_next_line/get_next_line.h"
# include "my_lifbt/libft.h"
# define TILE_SIZE 64
# define FOV_ANGLE (60 * (M_PI / 180))
# define DEG(x) ((180 / M_PI) * x)
# define WALL_WIDTH 1
# define NUM_RAYS (WINDOW_WIDTH * WALL_WIDTH)
# define WIDTH g_mapinfo->width
# define HEIGHT g_mapinfo->height
# define NO g_mapinfo->north_texture
# define SO g_mapinfo->south_texture
# define WE g_mapinfo->west_texture
# define EA g_mapinfo->east_texture
# define SP g_mapinfo->sprite_texture
# define F g_mapinfo->floor_color
# define C g_mapinfo->ceilling_color
# define MAP_R g_mapinfo->map_reader
# define MAP g_mapinfo->map
# define MFR g_mapinfo->map_first_read
# define CP g_mapinfo->check_player
# define MAP_ROWS g_mapinfo->map_rows
# define MAP_COLUMNS g_mapinfo->map_columns
# define MAPINFO g_mapinfo
# define TXT g_mapinfo->map_textures
# define TXTP g_mapinfo->texture_pointers
# define TXT_W g_mapinfo->texture_width
# define TXT_H g_mapinfo->texture_height
# define FLOOR_COLOR g_mapinfo->floor
# define CEILING_COLOR g_mapinfo->ceiling
# define SPRITES g_mapinfo->sprites
# define S_COUNT g_mapinfo->s_count
# define S_HEIGHT g_mapinfo->sprite_height
# define S_WIDTH g_mapinfo->sprite_width
# define SCREEN g_mapinfo->screen_shot
# define BUFFER g_buffer
# define KEY_UP 13
# define KEY_DOWN 1
# define KEY_RIGHT 2
# define KEY_LEFT 0

typedef struct	s_sprite
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
}				t_sprite;

typedef struct	s_list
{
	int				width;
	int				height;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*sprite_texture;
	int				floor_color[3];
	int				ceilling_color[3];
	char			*map_reader;
	char			**map;
	int				map_first_read;
	int				check_player;
	int				map_rows;
	int				map_columns;
	int				*map_textures[4];
	void			*texture_pointers[4];
	int				sprite_width;
	int				sprite_height;
	int				texture_width[4];
	int				texture_height[4];
	unsigned long	floor;
	unsigned long	ceiling;
	t_sprite		*sprites;
	int				s_count;
	int				screen_shot;
}				t_mapdata;

typedef struct	s_player
{
	float		x;
	float		y;
	float		radius;
	int			turn_direction;
	int			walk_direction;
	float		rotation_angle;
	float		move_speed;
	float		rotation_speed;
	float		turn_speed;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*color_buffer_texture;
	void		*xpm_picture;
	int			*texture_buffer;
	int			texture_width;
	int			texture_height;
}				t_point;

typedef struct	s_rays
{
	float		ray_angle;
	float		wall_hitx;
	float		wall_hity;
	float		distance;
	int			washitvertical;
	int			israyfacingup;
	int			israyfacingright;
	int			israyfacingdown;
	int			israyfacingleft;
	int			wallhitcontent;
}				t_ray;

typedef struct	s_raynorm
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
	float	nexthorztouchy;
	float	xtocheck;
	float	ytocheck;
	int		foundvertwallhit;
	float	vertwallhitx;
	float	vertwallhity;
	int		vertwallcontent;
	float	nextverttouchx;
	float	nextverttouchy;
	float	horzhitdistance;
	float	verthitdistance;
}				t_raynorm;
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

typedef struct	s_walls
{
	int		i;
	int		j;
	int		offsetx;
	int		offsety;
	int		txt;
	float	perp_distance;
	float	distance_projplane;
	float	projected_wall_height;
	int		wall_stripheight;
	int		wall_top_pixel;
	int		wall_bottompixel;
	int		distance_fromtop;
}				t_walls;

typedef struct	s_var
{
	int		i;
	int		j;
	int		c;
	float	size;
}				t_var;

typedef struct	s_fmap
{
	int		len;
	int		i;
	int		j;
	int		row_len;
	int		col_len;
	char	*tmp;
}				t_fmap;

typedef struct	s_map_p
{
	char		*line;
	int			ret;
	int			fd;
	int			i;
	int			param;
}				t_map_p;

int				reading_file(char *file);
void			struct_init(t_point *pl);
int				ft_init(char *extension);
int				reset_player(int key, t_point *pl);
void			castall_rays(t_point *pl);
void			cast_rayy(float ray_angle, int id, t_point *pl);
void			generate3dwalls(t_point *pl);
void			find_player(t_point *pl);
int				arr_size(char **arr);
int				move_player(int key, t_point *pl);
size_t			ft_strlen2(char *s);
int				str_isdigit(char *str);
int				arr_size(char **arr);
int				free_struct(char *line);
int				check_color_parametre(char *param);
int				error_message(char *error);
int				fill_color_values(char *arr, int f_or_c, int i);
void			init_sprit(t_point *pl);
void			take_screenshot(void);
int				collision(int x, int y);
int				collision_player(int x, int y);
float			normalize_angle(float angle);
float			distance_between_points(float x1, float y1, float x2, float y2);
void			draw_sprite(t_point *pl);
void			ft_player_initial_pov(t_point *pl, int c);
void			draw_map(t_point *pl);
void			find_player(t_point *pl);
int				move_player(int key, t_point *pl);
void			fill_rays(t_raynorm *ray, t_point *pl, int id, float ray_angle);
void			update_player(t_point *pl);
int				ft_init(char *extension);
int				ft_resolution(char *line);
unsigned long	ft_rgb_to_hex(int r, int g, int b);
int				ft_texture(char *line);
int				ft_read_map(char *line);
int				ft_color_value(char *line);
int				ft_fill_map(void);
int				ft_fill_mapsp(void);
int				move_p(t_point *pl);
int				close_window(int key);
t_mapdata		*g_mapinfo;
t_ray			*g_rays;
int				*g_buffer;
#endif
