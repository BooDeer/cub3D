/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 18:29:36 by hboudhir          #+#    #+#             */
/*   Updated: 2020/02/05 18:31:33 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


void		put_pixel(int x, int y, int color, void *img)
{
	int k;
	int *tmp;
	
	tmp = (int *)mlx_get_data_addr(img, &k, &k, &k);
	tmp[x + (y * WINDOW_WIDTH)] = color;
}
