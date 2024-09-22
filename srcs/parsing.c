/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:12:32 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 14:52:49 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		return (err_exit("Only positive numbers"), NULL);
	number = str;
	while (is_digit(*str))
	{
		len++;
		str++;
	}
	if (*str)
		return (err_exit("Only digits are accepted."), NULL);
	if (len > 10)
		return (err_exit("The value is too big. The limit is INT_MAX."), NULL);
	return (number);
}

static long	ft_atol(char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if (!str)
		return (-1);
	while (is_digit(*str))
	{
		num = (num * 10) + (*str - 48);
		str++;
	}
	if (num > INT_MAX)
		return (err_exit("The value is too big. The limit is INT_MAX"), -1);
	return (num);
}

int	check_parsing(t_data *data)
{
	if (data->number_of_philos == -1)
		return (1);
	else if (data->time_to_die == -1)
		return (1);
	else if (data->time_to_eat == -1)
		return (1);
	else if (data->time_to_sleep == -1)
		return (1);
	else
		return (0);
}

void	special_case(t_data data)
{
	if (data.number_of_meals == 0)
		return ;
	else
	{
		printf("%-6d 1 has taken a fork\n", 0);
		ft_usleep(data.time_to_die);
		printf("%-6ld 1 died\n", data.time_to_die);
	}
}

int	parsing(t_data *data, char **av)
{
	data->number_of_philos = ft_atol(av[1]);
	data->time_to_die = ft_atol(av[2]);
	data->time_to_eat = ft_atol(av[3]);
	data->time_to_sleep = ft_atol(av[4]);
	if (av[5])
		data->number_of_meals = ft_atol(av[5]);
	else
		data->number_of_meals = -1;
	if (check_parsing(data))
		return (1);
	if (data->number_of_meals == 0 || data->number_of_philos == 1)
	{
		special_case(*data);
		return (1);
	}
	return (0);
}
