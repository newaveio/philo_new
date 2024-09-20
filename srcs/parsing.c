/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:12:32 by mbest             #+#    #+#             */
/*   Updated: 2024/09/20 16:15:55 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

static char	*valid_input(char *str)
{
	int		len;
	char	*number;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		err_exit("Only positive numbers");
	if (!is_digit(*str))
		err_exit("The input is not a digit");
	number = str;
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (len > 10)
		err_exit("The value is too big. The limit is INT_MAX");
	return (number);
}

static long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	if (num > INT_MAX)
		err_exit("The value is too big. The limit is INT_MAX");
	return (num);
}

void	parsing(t_data *data, char **av)
{
	data->number_of_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->number_of_meals = ft_atol(av[5]);
	else
		data->number_of_meals = -1;
}
