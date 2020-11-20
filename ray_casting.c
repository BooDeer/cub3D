/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 11:39:40 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/19 18:24:23 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		rays_hinit(t_raynorm *ray, float ray_angle, point *pl)
{
	ray->is_rayfacingdown = ray_angle > 0 && ray_angle < M_PI;
	ray->is_rayfacingup = !ray->is_rayfacingdown;
	ray->is_rayfacingright = ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI;
	ray->is_rayfacingleft = !ray->is_rayfacingright;

	ray->found_horzwallhit = 0;
	ray->horz_wallhitx = 0;
	ray->horzwallhity = 0;
	ray->horzwallcontent = 0;

	ray->yintercept = floor(pl->y / TILE_SIZE) * TILE_SIZE;
	ray->yintercept += ray->is_rayfacingdown ? TILE_SIZE : 0;

	ray->xintercept = pl->x + (ray->yintercept - pl->y) / tan(ray_angle);
	
	ray->ystep = TILE_SIZE;
	ray->ystep *= ray->is_rayfacingup ? -1 : 1;

	ray->xstep = TILE_SIZE / tan(ray_angle);
	ray->xstep *= (ray->is_rayfacingleft && ray->xstep > 0) ? -1 : 1;
	ray->xstep *= (ray->is_rayfacingright && ray->xstep < 0) ? -1 : 1;
}

void		horizontal_cast(t_raynorm *ray)
{
	ray->nexthorztouchx = ray->xintercept;
	ray->nexthorztouchy = ray->yintercept;

	while (ray->nexthorztouchx > 0 && ray->nexthorztouchx / TILE_SIZE < MAP_ROWS
	&& ray->nexthorztouchy > 0 && ray->nexthorztouchy / TILE_SIZE < MAP_COLUMNS)
	{
		ray->xtocheck = ray->nexthorztouchx;
		ray->ytocheck = ray->nexthorztouchy + (ray->is_rayfacingup ? -1 : 0);

		if (collision(ray->xtocheck, ray->ytocheck))
		{
			ray->horz_wallhitx = ray->nexthorztouchx;
			ray->horzwallhity = ray->nexthorztouchy;
			ray->found_horzwallhit = 1;
			break;
		}
		else
		{
			ray->nexthorztouchx += ray->xstep;
			ray->nexthorztouchy += ray->ystep;
		}
	
	}	
}

void		ray_vinit(t_raynorm *ray, float ray_angle, point *pl)
{
	ray->foundvertwallhit = 0;
	ray->vertwallhitx = 0;
	ray->vertwallhity = 0;
	ray->vertwallcontent = 0;
	ray->xintercept = floor(pl->x / TILE_SIZE) * TILE_SIZE;
	ray->xintercept += ray->is_rayfacingright ? TILE_SIZE : 0;
	ray->yintercept = pl->y + (ray->xintercept - pl->x) * tan(ray_angle);
	ray->xstep = TILE_SIZE;
	ray->xstep *= ray->is_rayfacingleft ? -1 : 1;
	ray->ystep = TILE_SIZE * tan(ray_angle);
	ray->ystep *= (ray->is_rayfacingup && ray->ystep > 0) ? -1 : 1;
	ray->ystep *= (ray->is_rayfacingdown && ray->ystep < 0) ? -1 : 1;

	ray->nextVertTouchX = ray->xintercept;
	ray->nextVertTouchY = ray->yintercept;
}

void		vertical_cast(t_raynorm *ray)
{
	while (ray->nextVertTouchX > 0 && ray->nextVertTouchX / TILE_SIZE < MAP_ROWS
	&& ray->nextVertTouchY > 0 && ray->nextVertTouchY / TILE_SIZE < MAP_COLUMNS)
	{
		ray->xtocheck = ray->nextVertTouchX + (ray->is_rayfacingleft ? -1 : 0);
		ray->ytocheck = ray->nextVertTouchY;

		if (collision(ray->xtocheck, ray->ytocheck))
		{
			ray->vertwallhitx = ray->nextVertTouchX;
			ray->vertwallhity = ray->nextVertTouchY;
			ray->foundvertwallhit = 1;
			break;
		}
		else
		{
			ray->nextVertTouchX += ray->xstep;
			ray->nextVertTouchY += ray->ystep;
		}
	}
}

void		fill_rays(t_raynorm *ray, point *pl, int id, float ray_angle)
{
	ray->horzHitDistance = ray->found_horzwallhit ? distance_between_points(pl->x,
	 pl->y, ray->horz_wallhitx, ray->horzwallhity) : INT_MAX;
	ray->vertHitDistance = ray->foundvertwallhit ? distance_between_points(pl->x,
	 pl->y, ray->vertwallhitx, ray->vertwallhity) : INT_MAX;
	if (ray->vertHitDistance < ray->horzHitDistance)
	{
		g_rays[id].distance = ray->vertHitDistance;
		g_rays[id].wallHitX = ray->vertwallhitx; 
		g_rays[id].wallHitY = ray->vertwallhity;
		g_rays[id].wallHitContent = ray->vertwallcontent;
		g_rays[id].wasHitVertical = 1;
	}
	else
	{
		g_rays[id].distance = ray->horzHitDistance;
		g_rays[id].wallHitX = ray->horz_wallhitx; 
		g_rays[id].wallHitY = ray->horzwallhity;
		g_rays[id].wallHitContent = ray->horzwallcontent;
		g_rays[id].wasHitVertical = 0;		
	}
	g_rays[id].rayAngle = ray_angle;
	g_rays[id].isRayFacingDown = ray->is_rayfacingdown;
	g_rays[id].isRayFacingUp = ray->is_rayfacingup;
	g_rays[id].isRayFacingRight = ray->is_rayfacingright;
	g_rays[id].isRayFacingLeft = ray->is_rayfacingleft;
}

void		castRayy(float ray_angle, int id, point *pl)
{
	ray_angle = normalize_angle(ray_angle);
	t_raynorm ray;
	rays_hinit(&ray, ray_angle, pl);
	horizontal_cast(&ray);
	ray_vinit(&ray, ray_angle, pl);
	vertical_cast(&ray);
	fill_rays(&ray, pl, id, ray_angle);

	
}