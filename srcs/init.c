/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:04 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 14:49:03 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_second_fork(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (i == data->number_of_philos - 1)
			data->philos[i].second_fork = &data->philos[0].first_fork;
		else
			data->philos[i].second_fork = &data->philos[i + 1].first_fork;
		i++;
	}
}

static void	init_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->number_of_philos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = 0;
		philo->meals = 0;
		philo->data = data;
		philo->second_fork = NULL;
		i++;
	}
}

static int	init_mutex_philos(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->number_of_philos)
	{
		philo = data->philos + i;
		if (safe_mutex(&philo->full_mutex, INIT))
		{
			cleanup_philos_mutexes(data, i);
			return (1);
		}
		if (safe_mutex(&philo->first_fork, INIT))
		{
			safe_mutex(&philo->first_fork, DESTROY);
			cleanup_philos_mutexes(data, i);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	init_mutex_data(t_data *data)
{
	if (safe_mutex(&data->write_lock, INIT))
		return (1);
	if (safe_mutex(&data->meal_check, INIT))
	{
		safe_mutex(&data->write_lock, DESTROY);
		return (1);
	}
	if (safe_mutex(&data->dead_lock, INIT))
	{
		safe_mutex(&data->write_lock, DESTROY);
		safe_mutex(&data->meal_check, DESTROY);
		return (1);
	}
	return (0);
}

int	init(t_data *data)
{
	data->min_meals = 0;
	data->all_ate = 0;
	data->died = 0;
	init_philos(data);
	if (init_mutex_data(data))
		return (1);
	if (init_mutex_philos(data))
	{
		safe_mutex(&data->write_lock, DESTROY);
		safe_mutex(&data->meal_check, DESTROY);
		safe_mutex(&data->dead_lock, DESTROY);
		return (1);
	}
	assign_second_fork(data);
	return (0);
}
