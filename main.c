/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:18:14 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/14 14:56:27 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	user_input(int argc, char **argv)
{
	if (argc < 2)
	{
		ft_printf("Fract-ol\n\nWrong parameter. Try:\n");
		ft_printf("./fractol mandelbrot\n./fractol julia xxx xxx");
	}
	else if (ft_strncmp(argv[1], "mandelbrot", 10) == 0)
		return (1);
	else if (ft_strncmp("julia", argv[1], 6) == 0)
	{
		if (argc > 4 || argc < 4)
		{
			ft_printf("falta uns numeros ai, ou colocou muito\n");
			exit(EXIT_FAILURE);
		}
		return(2);
	}
	ft_printf("Fract-ol\n\nWrong parameter. Try:\n");
	ft_printf("./fractol mandelbrot\n./fractol julia xxx xxx");
	exit(EXIT_FAILURE);
	return (0);
}

void	input_to_julia(char **argv, t_access *access)
{
	double	x;
	double	y;

	x = ft_atof(argv[2]);
	if (x == 0)
	{
		ft_printf("Invalid Value. Try some number 0 > or 0 <\n");
		//exit(EXIT_FAILURE);
	}
	else
		access->ca = x;
	y = ft_atof(argv[3]);
	if (y == 0)
	{
		ft_printf("Invalid Value. Try some number 0 > or 0 <\n");
		//exit(EXIT_FAILURE);
	}
	else
		access->cb = y;
}

int	main(int argc, char **argv)
{
	t_access	access;
	int			fractal;

	fractal = user_input(argc, argv);
	access.zoom = 1.0;
	access.max_iter = 50;
	access.offset_x = 0.0;
	access.offset_y = 0.0;
	access.mlx_connection = mlx_init();
	access.mlx_window = mlx_new_window(access.mlx_connection,
			WIDTH, HEIGHT, "Fract-ol");
	create_image(&access);
	if (fractal == 1)
		put_image(&access);
	else if (fractal == 2)
	{
		input_to_julia(argv, &access);
		put_image_julia(&access);
	}
	mlx_mouse_hook(access.mlx_window, mouse_hook, &access);
	mlx_loop(access.mlx_connection);
	return (0);
}
