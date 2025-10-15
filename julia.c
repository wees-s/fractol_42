/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:31:34 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/15 16:26:18 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_calc(double x, double y, t_access *access)
{
	double	a;
	double	b;
	int		i;
	double	temp;

	a = x;
	b = y;
	i = 0;
	temp = 0.0;
	while (i < access->max_iter && (a * a + b * b <= 4.0))
	{
		temp = a * a - b * b + access->ca;
		b = 2 * a * b + access->cb;
		a = temp;
		i++;
	}
	if (i == access->max_iter)
		return (-1);
	else
		return (i);
}

int	mouse_hook_julia(int button, int x, int y, void *param)
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
	put_image_julia(access);
	return (0);
}

int	key_press_julia(int keycode, void *param)
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
	put_image_julia(access);
	return (0);
}

void	put_image_julia(t_access *access)
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
			i = julia_calc(cmpx.re, cmpx.im, access);
			color_func(access, x, y, i);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(access->mlx_connection,
		access->mlx_window, access->img, 0, 0);
}
