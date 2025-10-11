/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 13:21:25 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/11 18:06:58 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include "minilibx-linux/mlx.h"

# define WIDTH 1000
# define HEIGHT 1000

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

typedef struct s_access
{
	/*connection*/
	void	*mlx_connection;
	/*window*/
	void	*mlx_window;
	/*img*/
	void	*img;
	/*img pointer*/
	char	*img_pointer;
	/*bits per pixel*/
	int		bits_per_pixel;
	/*line*/
	int		line_len;
	/*endian*/
	int		endian;
}	t_access;

# endif
