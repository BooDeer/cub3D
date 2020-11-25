/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 17:03:57 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/25 11:22:34 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		fill_rays(t_raynorm *ray, t_point *pl, int id, float ray_angle)
{
	ray->horzhitdistance = ray->found_horzwallhit ? distance_between_points(
	pl->x, pl->y, ray->horz_wallhitx, ray->horzwallhity) : INT_MAX;
	ray->verthitdistance = ray->foundvertwallhit ? distance_between_points(
	pl->x, pl->y, ray->vertwallhitx, ray->vertwallhity) : INT_MAX;
	if (ray->verthitdistance < ray->horzhitdistance)
	{
		g_rays[id].distance = ray->verthitdistance;
		g_rays[id].wall_hitx = ray->vertwallhitx;
		g_rays[id].wall_hity = ray->vertwallhity;
		g_rays[id].wallhitcontent = ray->vertwallcontent;
		g_rays[id].washitvertical = 1;
	}
	else
	{
		g_rays[id].distance = ray->horzhitdistance;
		g_rays[id].wall_hitx = ray->horz_wallhitx;
		g_rays[id].wall_hity = ray->horzwallhity;
		g_rays[id].wallhitcontent = ray->horzwallcontent;
		g_rays[id].washitvertical = 0;
	}
	g_rays[id].ray_angle = ray_angle;
	g_rays[id].israyfacingdown = ray->is_rayfacingdown;
	g_rays[id].israyfacingup = ray->is_rayfacingup;
	g_rays[id].israyfacingright = ray->is_rayfacingright;
	g_rays[id].israyfacingleft = ray->is_rayfacingleft;
}
