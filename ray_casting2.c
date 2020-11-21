/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:03:57 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/20 17:31:12 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void		fill_rays(t_raynorm *ray, point *pl, int id, float ray_angle)
{
	ray->horzHitDistance = ray->found_horzwallhit ? distance_between_points(
	pl->x, pl->y, ray->horz_wallhitx, ray->horzwallhity) : INT_MAX;
	ray->vertHitDistance = ray->foundvertwallhit ? distance_between_points(
	pl->x, pl->y, ray->vertwallhitx, ray->vertwallhity) : INT_MAX;
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
