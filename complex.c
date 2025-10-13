/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 18:20:12 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/13 18:21:50 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	to_real(int x, t_access *access)
{
	return ((access->offset_x + ((double)x / (WIDTH - 1))
			* (4.0 / access->zoom) - 2.0 / access->zoom));
}

double	to_imaginary(int y, t_access *access)
{
	return ((access->offset_y + (-((double)y / (HEIGHT - 1))
				* (4.0 / access->zoom) + 2.0 / access->zoom)));
}
