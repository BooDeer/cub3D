/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:54:20 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/18 18:07:31 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		sort_sprites(void)
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

void		generate_sprites(int id)
{
	t_var	v;

	v.i = -1;
	v.size = SPRITES[id].size;
	while (++v.i < v.size - 1)
	{
		if (SPRITES[id].x_off + v.i <= 0 || SPRITES[id].x_off + v.i >= WIDTH)
			continue ;
		if ((int)g_rays[(int)SPRITES[id].x_off +
		v.i].distance <= SPRITES[id].dist)
			continue ;
		v.j = -1;
		while (++v.j < v.size - 1)
		{
			if (SPRITES[id].y_off + v.j <= 0 || SPRITES[id].y_off
			+ v.j >= HEIGHT)
				continue ;
			v.c = SPRITES->sdata[(int)((TILE_SIZE) * (TILE_SIZE * v.j /
			(int)v.size) + (TILE_SIZE * v.i / (int)v.size))];
			if (v.c != SPRITES->sdata[0])
				BUFFER[(int)((v.j + SPRITES[id].y_off) *
				WIDTH + (v.i + SPRITES[id].x_off))] = v.c;
		}
	}
}

void		draw_sprite(point *pl)
{
	float	angle;
	int		k;

	k = -1;
	sort_sprites();
	while (++k < S_COUNT)
	{
		SPRITES[k].dist = sqrtf(((SPRITES[k].x) - pl->x) * ((SPRITES[k].x) -
		pl->x) + ((SPRITES[k].y) - pl->y) * ((SPRITES[k].y) - pl->y));
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
		generate_sprites(k);
	}
}

void		init_sprit(point *pl)
{
	int			i;
	int			j;
	int			k;

	i = -1;
	k = 0;
	if (!(SPRITES = malloc(sizeof(t_sprite) * (S_COUNT + 1))))
		error_message("Error\nFailed to allocate memory");
	SPRITES->simg = mlx_xpm_file_to_image(pl->mlx_ptr, SP, &S_WIDTH, &S_HEIGHT);
	free(SP);
	SPRITES->sdata = (int *)mlx_get_data_addr(SPRITES->simg, &SPRITES->useless,
	&SPRITES->useless, &SPRITES->useless);
	while (MAP[++i] != 0 && (j = -1) && (k < S_COUNT))
		while (MAP[i][++j] && (k < S_COUNT))
			if (MAP[i][j] == '2')
			{
				SPRITES[k].x = (j + 0.5) * TILE_SIZE;
				SPRITES[k].y = (i + 0.5) * TILE_SIZE;
				SPRITES[k].dist = sqrtf(((SPRITES[k].x) - pl->x) * (
				(SPRITES[k].x) - pl->x) + ((SPRITES[k].y) - pl->y) *
				((SPRITES[k].y) - pl->y));
				k++;
			}
}
