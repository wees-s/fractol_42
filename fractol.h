/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:21:25 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/13 18:31:46 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "minilibx-linux/mlx.h"
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_access
{
	void	*mlx_connection;
	void	*mlx_window;
	void	*img;
	char	*img_pointer;
	int		bits_per_pixel;
	int		line_len;
	int		endian;
	double	zoom;
	double	max_iter;
	double	offset_x;
	double	offset_y;
	double	old_re;
	double	old_im;
	double	new_re;
	double	new_im;
}	t_access;

double	to_real(int x, t_access *access);
double	to_imaginary(int y, t_access *access);
int		mouse_hook(int button, int x, int y, void *param);
void	create_image(t_access *access);
void	put_image(t_access *access);
void	color_func(t_access *access, int x, int y, int i);
int		fractal_calc(double x, double y, int max_iter);
void	user_input(int argc, char **argv);

#endif
