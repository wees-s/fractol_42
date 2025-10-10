/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 13:48:52 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/10 17:07:05 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx-linux/mlx.h"
#include <stdio.h>
#include "fractol.h"


double transformar_em_real(int x)
{
	return  -2.0 + ((double)x / 500.0) * 4.0;
}

double transformar_em_imaginario(int y)
{
	return  -2.0 + ((double)y / 500.0) * 4.0;
}

void o_complex_faz_parte_do_fractal(double x, double y, int max_iter, void *mlx_connection, void *mlx_window, t_complex access)
{
    double a = 0.0; // parte real de z
    double b = 0.0; // parte imaginária de z
    int i = 0;
	int	c = 0;
	int j = 0;
    while (i < max_iter && (a * a + b * b <= 4.0))
    {
        double temp = a * a - b * b + x; // novo a
        b = 2 * a * b + y;               // novo b
        a = temp;
        i++;
		c++;
    }
    if (i == max_iter)
	{
		mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0xFFFFFF);
    //    return 1; // pertence ao fractal
	}
    else
	{
		if (c < 5)
			mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0xFFFFFF);
		else if (c < 8)
			mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0xFFFFFF);
		else if (c < 10)
			mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0x7A00F5);
		else if (c < 15)
			mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0x0025F5);
		else if (c < 20)
			mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0xF500AF);
		else if (c < 42)
			mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0xA352F5);
	}
      //  return 0; // não pertence
}

int main()
{
	void	*mlx_connection; //iniciando a maquina grafica
	void	*mlx_window;
	t_complex access;
	mlx_connection = mlx_init(); //iniciamos.
	mlx_window = mlx_new_window(mlx_connection, 500, 500, "janela"); //janela abrida
	int x;
	int y;

	x = 0;
	y = 0;
	while (y <= 499)
	{
		while (x <= 499) //percorrendo tudo***************************
		{
			access.px_x = x;
			access.px_y = y;
			access.re = transformar_em_real(x);
			access.im = transformar_em_imaginario(y);
			o_complex_faz_parte_do_fractal(access.re, access.im, 42, mlx_connection, mlx_window, access);
			//if (o_complex_faz_parte_do_fractal(access.re, access.im, 10) == 1)
			//{
			//	mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0xFFFFFF);
			//}
			//else
			//{
			//	mlx_pixel_put(mlx_connection, mlx_window, access.px_x, access.px_y, 0);
			//}
			x++;
		}
		x = 0;
		y++;
	}
	mlx_loop(mlx_connection);
}
