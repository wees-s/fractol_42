/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:25:45 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/15 16:20:21 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	fractal_calc(double x, double y, int max_iter)
{
	double	a;
	double	b;
	int		i;
	double	temp;

	a = 0.0;
	b = 0.0;
	i = 0.0;
	temp = 0.0;
	while (i < max_iter && (a * a + b * b <= 4.0))
	{
		temp = a * a - b * b + x;
		b = 2 * a * b + y;
		a = temp;
		i++;
	}
	if (i == max_iter)
		return (-1);
	else
		return (i);
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

void	put_image(t_access *access)
{
	int			x;
	int			y;
	int			i;
	t_complex	cmpx;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			cmpx.re = to_real(x, access);
			cmpx.im = to_imaginary(y, access);
			i = fractal_calc(cmpx.re, cmpx.im, access->max_iter);
			color_func(access, x, y, i);
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
	t_access	*access;

	access = (t_access *)param;
	access->old_re = to_real(x, access);
	access->old_im = to_imaginary(y, access);
	if (button == 4)
	{
		access->max_iter *= 1.003;
		access->zoom *= 1.05;
	}
	else
	{
		access->max_iter /= 1.003;
		access->zoom /= 1.05;
	}
	access->new_re = to_real(x, access);
	access->new_im = to_imaginary(y, access);
	access->offset_x += (access->old_re - access->new_re);
	access->offset_y += (access->old_im - access->new_im);
	mlx_destroy_image(access->mlx_connection, access->img);
	create_image(access);
	put_image(access);
	return (0);
}
