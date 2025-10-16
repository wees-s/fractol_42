/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:47:32 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/16 10:43:46 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	init_access(t_access *access, int argc, char **argv)
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

void	create_image(t_access *access)
{
	access->img = mlx_new_image(
			access->mlx_connection,
			WIDTH,
			HEIGHT);
	access->img_pointer = mlx_get_data_addr(
			access->img,
			&access->bits_per_pixel,
			&access->line_len,
			&access->endian);
}

void	color_func(t_access *access, int x, int y, int i)
{
	char	*pixel;
	int		color;
	int		t;

	color = 0;
	t = 0;
	pixel = access->img_pointer
		+ (y * access->line_len + x * (access->bits_per_pixel / 8));
	if (i == -1)
		color = 0x000000;
	else
	{
		t = (i * 256) / access->max_iter;
		color = (t << 16) | ((255 - t) << 8) | 255;
	}
	*(unsigned int *)pixel = color;
}
