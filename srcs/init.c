/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:01:04 by mbest             #+#    #+#             */
/*   Updated: 2024/09/19 19:08:33 by mbest            ###   ########.fr       */
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
		pthread_mutex_init(&philo->full_mutex, NULL);
		pthread_mutex_init(&philo->first_fork, NULL);
		i++;
	}
}

void	init(t_data *data)
{
	data->min_meals = 0;
	data->all_ate = 0;
	data->died = 0;
	data->philos = (t_philo *)safe_malloc((sizeof(t_philo)
				* data->number_of_philos), data);
	safe_mutex(&data->write_lock, INIT);
	safe_mutex(&data->meal_check, INIT);
	safe_mutex(&data->dead_lock, INIT);
	safe_mutex(&data->ready_lock, INIT); //! not using for now / put in place
	safe_mutex(&data->meal_check, INIT);
	init_philos(data);
	assign_second_fork(data);
}
