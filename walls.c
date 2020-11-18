/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 17:13:06 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/18 17:16:32 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

double	f_mod(double a, double b)
{
	return (a - (floor(a/b) * b));
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
	int		textureOffsetX;
	int		textureOffsetY;
    int     txt;
	float perpDistance;
	float distanceProjPlane;
	float projectedWallHeight;
	for (int i = 0; i < WIDTH; i++)
	{
		perpDistance = g_rays[i].distance * cos(g_rays[i].rayAngle - pl->rotationAngle);
		distanceProjPlane = (WIDTH / 2) / tan(FOV_ANGLE / 2);
		projectedWallHeight = (TILE_SIZE / perpDistance) * distanceProjPlane;

		int		wallStripHeight = (int)projectedWallHeight;

		int wallTopPixel = (HEIGHT / 2) - (wallStripHeight / 2);
		wallTopPixel = wallTopPixel < 0 ? 0 : wallTopPixel;

		int wallBottomPixel = (HEIGHT / 2) + (wallStripHeight / 2);
		wallBottomPixel = wallBottomPixel > HEIGHT ? HEIGHT : wallBottomPixel;

		for (int y = 0; y < wallTopPixel; y++)
            BUFFER[i + (WIDTH * y)] = CEILING_COLOR;
		
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

			BUFFER[i + ((WIDTH) * y)] = TXT[txt][textureOffsetX + (textureOffsetY * TXT_W[txt])];

		}
		for (int y = wallBottomPixel; y < HEIGHT; y++)
			BUFFER[i + (WIDTH * y)] = FLOOR_COLOR;
	}
}