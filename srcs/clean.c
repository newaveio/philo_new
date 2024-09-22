/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:42:36 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 15:01:33 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	cleanup_philos_mutexes(t_data *data, int index)
{
	int		i;
	t_philo	*philo;

	i = index;
	while (i-- > 0)
	{
		philo = data->philos + i;
		safe_mutex(&philo->full_mutex, DESTROY);
		safe_mutex(&philo->first_fork, DESTROY);
	}
}

void	exit_sim(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
		i++;
	}
}

void	exit_cleanly(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		safe_mutex(&data->philos[i].first_fork, DESTROY);
		safe_mutex(&data->philos[i].full_mutex, DESTROY);
		i++;
	}
	safe_mutex(&data->write_lock, DESTROY);
	safe_mutex(&data->dead_lock, DESTROY);
	safe_mutex(&data->meal_check, DESTROY);
	free(data->philos);
}
