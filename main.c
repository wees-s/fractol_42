/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:18:14 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/13 12:25:53 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double to_real(int x, t_access *access)
{
	return ((double)x / (WIDTH - 1)) * (4.0 / access->zoom) - (2.0 / access->zoom);
}

double to_imaginary(int y, t_access *access)
{
	return -((double)y / (HEIGHT - 1)) * (4.0 / access->zoom) + (2.0 / access->zoom);
}

int	fractal_calc(double x, double y, int max_iter)
{
	double	a = 0.0;
	double	b = 0.0;
	int		i = 0;
	double	temp;

    while (i < max_iter && (a * a + b * b <= 4.0))
	{
		temp = a * a - b * b + x;
		b = 2 * a * b + y;
		a = temp;
		i++;
	}
	if (i == max_iter)
		return (1);
	else
		return (0);
}

void color_func(t_access *access, int x, int y, int color)
{
	char	*pixel;
	
	pixel = access->img_pointer
		+ (y * access->line_len + x * (access->bits_per_pixel / 8));

	*(unsigned int *)pixel = color;
}

void	put_image(t_access *access)
{
	int		x;
	int		y;
	t_complex	cmpx;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			cmpx.re = to_real(x, access);
			cmpx.im = to_imaginary(y, access);
			if (fractal_calc(cmpx.re, cmpx.im, access->max_iter) == 1)
				color_func(access, x, y, 0x000000);
			else
				color_func(access, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(access->mlx_connection,
			access->mlx_window, access->img, 0, 0);
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

int	mouse_hook(int button, int x, int y, void *param)
{
	t_access *access = (t_access *)param;

	(void)x;
	(void)y;
	if (button == 4)
	{
		access->zoom *= 1.1;
		put_image(access);
	}
	else if (button == 5)
	{
		access->zoom /= 1.1;
		put_image(access);
	}
	return (0);
}

int	main(void)
{
	t_access	access;

	access.zoom = 1.0;
	access.max_iter = 42;
	access.mlx_connection = mlx_init();
	access.mlx_window = mlx_new_window(access.mlx_connection,
			WIDTH, HEIGHT, "Fract-ol");
	create_image(&access);
	put_image(&access);
	mlx_mouse_hook(access.mlx_window, mouse_hook, &access);
	mlx_loop(access.mlx_connection);
		
	return (0);
}
