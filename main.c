/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hboudhir <hboudhir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 08:12:18 by hboudhir          #+#    #+#             */
/*   Updated: 2020/11/21 18:04:55 by hboudhir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

int		close_window(int key)
{
	exit(1);
	return (key);
}

int		move_p(point *pl)
{
	mlx_hook(pl->win_ptr, 2, 0, move_player, pl);
	mlx_hook(pl->win_ptr, 3, 0, reset_player, pl);
	mlx_hook(pl->win_ptr, 17, 0, close_window, pl);
	update_player(pl);
	return (0);
}

void	free_textures(void)
{
	free(NO);
	free(SO);
	free(WE);
	free(EA);
}

void	ft_fill_textures(point *pl)
{
	int		i;
	int		useless;

	i = -1;
	TXTP[0] = mlx_xpm_file_to_image(pl->mlx_ptr, NO, &TXT_W[0], &TXT_H[0]);
	TXTP[1] = mlx_xpm_file_to_image(pl->mlx_ptr, SO, &TXT_W[1], &TXT_H[1]);
	TXTP[2] = mlx_xpm_file_to_image(pl->mlx_ptr, WE, &TXT_W[2], &TXT_H[2]);
	TXTP[3] = mlx_xpm_file_to_image(pl->mlx_ptr, EA, &TXT_W[3], &TXT_H[3]);
	free_textures();
	while (++i < 4)
		TXT[i] = (int *)mlx_get_data_addr(TXTP[i], &useless,
	&useless, &useless);
}

int		main(int argc, char **argv)
{
	// point		pl;
	// int			useless;

	if (argc != 2 && argc != 3)
		return (error_message("Error\nWrong number of arguments given to the program\n"));
	if (!(mapinfo = malloc(sizeof(t_mapdata))))
		return (error_message("Error\nError during a memory allocation\n"));
	if(ft_init(mapinfo, argv[1]))
		return(error_message("Error\nWrong file extension\n"));
	if (reading_file(argv[1]))
        return (-1);
	while (1)
		;
    // g_rays = (t_ray *)malloc(sizeof(t_ray) * WIDTH);
    // pl.mlx_ptr = mlx_init();
    // pl.win_ptr = mlx_new_window(pl.mlx_ptr,WIDTH, HEIGHT,"bruh");
    // pl.color_buffer_texture = mlx_new_image(pl.mlx_ptr, WIDTH,HEIGHT);
	// BUFFER = (int *)mlx_get_data_addr(pl.color_buffer_texture, &useless, &useless, &useless);
    // struct_init(&pl);
    // ft_fill_textures(&pl);
	// init_sprit(&pl);
    // draw_map(&pl);
	// if (argc == 3)
	// {
	// 	take_screenshot();
	// 	exit(1);
	// }
    // mlx_loop_hook(pl.mlx_ptr, move_p, &pl);
    // mlx_put_image_to_window(pl.mlx_ptr,pl.win_ptr,pl.color_buffer_texture,0,0);
    // mlx_loop(pl.mlx_ptr);
    // free(mapinfo);
    // free(g_rays);
}
