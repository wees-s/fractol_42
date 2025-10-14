/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:18:14 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/14 18:31:48 by wedos-sa         ###   ########.fr       */
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
			ft_printf("Wrong parameter, try any of these coordinates:\n\n");
			ft_printf("./fractol julia <x> <y>\n");
			ft_printf("-0.70176 -0.3842\n-0.1011 0.9563\n");
			ft_printf("0.355 0.355\n-0.7269 0.1889\n");
			exit(EXIT_FAILURE);
		}
		return (2);
	}
	ft_printf("Fract-ol\n\nWrong parameter. Try:\n");
	ft_printf("./fractol mandelbrot\n./fractol julia x.xx y.yy");
	exit(EXIT_FAILURE);
	return (0);
}

void	input_to_julia(char **argv, t_access *access)
{
	double	x;
	double	y;

	x = ft_atof(argv[2]);
	access->ca = x;
	y = ft_atof(argv[3]);
	access->cb = y;
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

int	handle_keypress(int keycode, t_access *access)
{
	if (keycode == 65307 || keycode == 53)
		close_window(access);
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

	access.fractal = user_input(argc, argv);
	access.zoom = 1.0;
	access.max_iter = 50;
	access.offset_x = 0.0;
	access.offset_y = 0.0;
	access.mlx_connection = mlx_init();
	access.mlx_window = mlx_new_window(access.mlx_connection,
			WIDTH, HEIGHT, "Fract-ol");
	create_image(&access);
	if (access.fractal == 1)
	{
		put_image(&access);
		mlx_mouse_hook(access.mlx_window, mouse_hook, &access);
	}
	else if (access.fractal == 2)
	{
		input_to_julia(argv, &access);
		put_image_julia(&access);
		mlx_mouse_hook(access.mlx_window, mouse_hook_julia, &access);
	}
	mlx_hook(access.mlx_window, 17, 0, close_window, &access);
	mlx_hook(access.mlx_window, 2, 1L << 0, handle_keypress, &access);
	mlx_loop(access.mlx_connection);
	return (0);
}
