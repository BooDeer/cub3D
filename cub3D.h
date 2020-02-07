/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/25 09:55:00 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/05 18:30:54 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mlx.h>
#include <math.h>

#define MINIMAP_SCALE 1.0
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15
#define TILE_SIZE 64
#define WINDOW_WIDTH TILE_SIZE * MAP_NUM_COLS
#define WINDOW_HEIGHT TILE_SIZE * MAP_NUM_ROWS

typedef struct 
{
	float x;
	float y;
	float	radius;
	int turnDirection;
	int walkDirection;
	float rotationAngle;
	float moveSpeed;
	float rotationSpeed;
	float turnSpeed;
	void	*mlx_ptr;
	void	*win_ptr;
	
}	point;

void		put_pixel(int x, int y, int color, void *img);
