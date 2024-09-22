/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:49:10 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 14:56:24 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	is_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	increase_long(t_mtx *mutex, long *dest)
{
	pthread_mutex_lock(mutex);
	(*dest)++;
	pthread_mutex_unlock(mutex);
}

void	increase_int(t_mtx *mutex, int *dest)
{
	pthread_mutex_lock(mutex);
	(*dest)++;
	pthread_mutex_unlock(mutex);
}

int	ft_alloc(t_data *data)
{
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->number_of_philos);
	if (!data->philos)
		return (1);
	return (0);
}
