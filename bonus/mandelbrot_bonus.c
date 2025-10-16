/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:25:45 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/16 11:07:06 by wedos-sa         ###   ########.fr       */
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

int	mouse_hook(int button, int x, int y, void *param)
{
	t_access	*access;

	access = (t_access *)param;
	access->old_re = to_real(x, access);
	access->old_im = to_imaginary(y, access);
	if (button == 4)
		access->zoom *= 1.05;
	else
		access->zoom /= 1.05;
	access->new_re = to_real(x, access);
	access->new_im = to_imaginary(y, access);
	access->offset_x += (access->old_re - access->new_re);
	access->offset_y += (access->old_im - access->new_im);
	mlx_destroy_image(access->mlx_connection, access->img);
	create_image(access);
	put_image(access);
	return (0);
}

int	key_press_mandelbrot(int keycode, void *param)
{
	t_access	*access;

	access = (t_access *)param;
	if (keycode == 65307)
		close_window(access);
	if (keycode == 65361)
		access->offset_x = access->offset_x - 0.05;
	if (keycode == 65363)
		access->offset_x = access->offset_x + 0.05;
	if (keycode == 65362)
		access->offset_y = access->offset_y + 0.05;
	if (keycode == 65364)
		access->offset_y = access->offset_y - 0.05;
	mlx_destroy_image(access->mlx_connection, access->img);
	create_image(access);
	put_image(access);
	return (0);
}
