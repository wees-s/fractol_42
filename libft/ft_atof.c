/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:21:44 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/14 16:15:10 by wedos-sa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_string(const char *string)
{
	int	i;
	int	have_dot;

	have_dot = 0;
	i = 0;
	while (string[i])
	{
		if (ft_isdigit(string[i]))
			i++;
		if (string[i] == '.' && have_dot == 0)
		{
			if (string[i + 1] == '\0')
				return (0);
			have_dot = 1;
			i++;
		}
		if (string[i] == '.' && have_dot == 1)
			return (0);
		i++;
	}
	if (have_dot == 1)
		return (-1);
	return (1);
}

int	decimal_count(const char *string)
{
	int	i;
	int	decimal;

	decimal = 1;
	i = 0;
	while (string[i])
	{
		while (string[i] != '.')
			i++;
		i++;
		while (string[i] != '\0')
		{
			i++;
			decimal = decimal * 10;
		}
	}
	return (decimal);
}

double	ft_atof(const char *string)
{	
	int		check;
	int		decimal;
	char	**s_string;

	s_string = NULL;
	decimal = 1;
	check = check_string(string);
	if (check == 1)
		return ((double)ft_atoi(string));
	else if (check == 0)
		return (0);
	else if (check == -1)
	{
		decimal = decimal_count(string);
		s_string = ft_split(string, '.');
		string = ft_strjoin(s_string[0], s_string[1]);
		return ((double)ft_atoi(string) / decimal);
	}
	return (0);
}
