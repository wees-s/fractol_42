/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:18:14 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/11 18:49:55 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double transformar_em_real(int x)
{
	return ((double)x / (WIDTH - 1)) * 5.0 - 2.0;
}

double transformar_em_imaginario(int y)
{
	return -((double)y / (HEIGHT - 1)) * 5.0 + 2.0;
}

int o_complex_faz_parte_do_fractal(double x, double y, int max_iter)
{
    double  a = 0.0;
    double  b = 0.0;
    int     i = 0;
    double  temp;

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

void	put_one_pixel(t_access *access)
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
			cmpx.re = transformar_em_real(x);
			cmpx.im = transformar_em_imaginario(y);
			if (o_complex_faz_parte_do_fractal(cmpx.re, cmpx.im, 42) == 1)
				color_func(access, x, y, 0x000000);
			else
				color_func(access, x, y, 0xFFFFFF);
			x++;
		}
		y++;
	}
}

void	create_image(t_access *access)
{
	/*imagem criada*/
	access->img = mlx_new_image(
			access->mlx_connection,
			WIDTH,
			HEIGHT);
	/*valores da imagem*/
	/*principal ponto é que é o primeiro item da lista*/
	access->img_pointer = mlx_get_data_addr(
			access->img,
			&access->bits_per_pixel,
			&access->line_len,
			&access->endian);
}

int	main(void)
{
	t_access	access;

	access.mlx_connection = mlx_init();

	access.mlx_window = mlx_new_window(
			access.mlx_connection,
			WIDTH,
			HEIGHT,
			"Fract-ol - Wedos-sa");

	create_image(&access);

	put_one_pixel(&access);
	mlx_put_image_to_window(
			access.mlx_connection,
			access.mlx_window,
			access.img,
			0,
			0);

	mlx_loop(access.mlx_connection);
	
	return (0);
}
