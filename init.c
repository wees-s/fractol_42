/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:47:32 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/15 16:58:34 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_access(t_access *access,  int argc, char **argv)
{
	access->fractal = user_input(argc, argv);
	access->zoom = 1.0;
	access->max_iter = 150;
	access->offset_x = 0.0;
	access->offset_y = 0.0;
	access->ca = 0.0;
	access->cb = 0.0;
	access->mlx_connection = mlx_init();	
	access->mlx_window = mlx_new_window(access->mlx_connection,
			WIDTH, HEIGHT, "Fract-ol");
	create_image(access);
}
