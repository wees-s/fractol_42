/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:18:14 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/16 14:30:45 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	input_error(t_access *access)
{
	ft_printf("Fract-ol\n\nWrong parameter. Try:\n");
	ft_printf("./fractol mandelbrot\n./fractol julia x.xx y.yy\n");
	close_window(access);
}

int	user_input(int argc, char **argv)
{
	if (argc < 2)
		;
	else if (ft_strncmp(argv[1], "mandelbrot", 11) == 0)
		return (1);
	else if (ft_strncmp("julia", argv[1], 7) == 0)
	{
		if (argc > 4 || argc < 4)
		{
			ft_printf("Wrong parameter, try any of these coordinates:\n\n");
			ft_printf("./fractol julia <x> <y>\n");
			ft_printf("-0.70176 -0.3842\n-0.355 0.1\n");
			ft_printf("0.355 0.355\n-0.7269 0.1889\n");
			exit(EXIT_FAILURE);
		}
		return (2);
	}
	ft_printf("Fract-ol\n\nWrong parameter. Try:\n");
	ft_printf("./fractol mandelbrot\n./fractol julia x.xx y.yy\n");
	exit(EXIT_FAILURE);
	return (0);
}

void	input_to_julia(char **argv, t_access *access)
{
	double	x;
	double	y;

	if (!ft_isdigit(argv[2][0]) || !ft_isdigit(argv[3][0]))
		input_error(access);
	if (ft_isdouble(argv[2]))
	{
		x = ft_atof(argv[2]);
		access->ca = x;
	}
	else
		input_error(access);
	if (ft_isdouble(argv[3]))
	{
		y = ft_atof(argv[3]);
		access->cb = y;
	}
	else
		input_error(access);
}

int	close_window(t_access *access)
{
	if (access->img)
		mlx_destroy_image(access->mlx_connection, access->img);
	if (access->mlx_window)
		mlx_destroy_window(access->mlx_connection, access->mlx_window);
	if (access->mlx_connection)
	{
		mlx_destroy_display(access->mlx_connection);
		free(access->mlx_connection);
	}
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_access	access;

	init_access(&access, argc, argv);
	if (access.fractal == 1)
	{
		if (argc > 2)
			input_error(&access);
		put_image(&access);
		mlx_mouse_hook(access.mlx_window, mouse_hook, &access);
		mlx_key_hook(access.mlx_window, key_press_mandelbrot, &access);
	}
	else if (access.fractal == 2)
	{
		input_to_julia(argv, &access);
		put_image_julia(&access);
		mlx_mouse_hook(access.mlx_window, mouse_hook_julia, &access);
		mlx_key_hook(access.mlx_window, key_press_julia, &access);
	}
	mlx_hook(access.mlx_window, 17, 0, close_window, &access);
	mlx_loop(access.mlx_connection);
	return (0);
}
