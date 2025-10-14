/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 10:31:34 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/14 14:53:37 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	julia_calc(double x, double y, t_access *access)
{
    double a = x;
    double b = y;
    int i = 0;
    double temp;

    while (i < access->max_iter && (a * a + b * b <= 4.0))
    {
        temp = a * a - b * b + access->ca;
        b = 2 * a * b + access->cb;
        a = temp;
        i++;
    }

    return (i);
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
