/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wedos-sa <wedos-sa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:21:44 by wedos-sa          #+#    #+#             */
/*   Updated: 2025/10/15 18:15:50 by wedos-sa         ###   ########.fr       */
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
		else if (string[i] == '.' && have_dot == 0)
		{
			if (string[i + 1] == '\0')
				return (0);
			have_dot = 1;
			i++;
		}
		else
			return (0);
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
	while (string[i] && string[i] != '.')
		i++;
	if (string[i] == '.')
	{
		i++;
		while (string[i++] != '\0')
			decimal *= 10;
	}
	return (decimal);
}

void	free_all(char **split, char *string)
{
	int	i;

	i = 0;
	free(string);
	while (split[i])
		free(split[i++]);
	free(split);
}

/* nova função para tratar o sinal */
int	handle_sign(char **string)
{
	int	sign;

	sign = 1;
	if (**string == '-')
	{
		sign = -1;
		(*string)++;
	}
	else if (**string == '+')
		(*string)++;
	return (sign);
}

double	ft_atof(char *string)
{
	int		check;
	int		decimal;
	char	**s_string;
	double	nb;
	int		sign;

	nb = 0.0;
	s_string = NULL;
	decimal = 1;
	sign = handle_sign(&string);
	check = check_string(string);
	if (check == 1)
		return ((double)ft_atoi(string) * sign);
	else if (check == 0)
		return (0);
	else if (check == -1)
	{
		decimal = decimal_count(string);
		s_string = ft_split(string, '.');
		string = ft_strjoin(s_string[0], s_string[1]);
		nb = (double)ft_atoi(string) / decimal;
		free_all(s_string, string);
		return (nb * sign);
	}
	return (0);
}

/*
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

void	free_all(char **split, char *string)
{
	int	i;

	i = 0;
	free(string);
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

double	ft_atof(char *string)
{	
	int		check;
	int		decimal;
	char	**s_string;
	double	nb;

	nb = 0.0;
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
		nb = (double)ft_atoi(string) / decimal;
		free_all(s_string, string);
		return (nb);
	}
	return (0);
}*/
