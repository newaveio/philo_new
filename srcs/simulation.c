/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:00:49 by mbest             #+#    #+#             */
/*   Updated: 2024/09/20 16:35:38 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)arg;
	data = philo->data;
	usleep(100);
	if (philo->id % 2)
		usleep(data->time_to_eat * 500);
	while (!get_int(&data->dead_lock, &data->died))
	{
		eat(philo);
		sleep_philo(philo);
		think(philo);
		if (get_int(&philo->full_mutex, &philo->full))
			break ;
	}
	return (NULL);
}

static void	full_checker(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos && get_int(&data->philos[i].full_mutex,
			&data->philos[i].full))
		i++;
	if (i == data->number_of_philos)
		data->all_ate = 1;
}

void	death_checker(t_data *data)
{
	int	i;

	while (data->all_ate == 0)
	{
		i = 0;
		while (i < data->number_of_philos && !data->died)
		{
			if (!get_int(&data->philos[i].full_mutex, &data->philos[i].full)
				&& gettime() - get_long(&data->meal_check,
					&data->philos[i].last_meal) > data->time_to_die)
			{
				set_int(&data->dead_lock, &data->died, 1);
				print_death(&data->philos[i], &data->write_lock);
				write_status(&data->philos[i], &data->write_lock, DIED);
			}
			i++;
		}
		if (get_int(&data->dead_lock, &data->died))
			break ;
		if (data->number_of_meals != -1)
			full_checker(data);
		usleep(100);
	}
}

void	start_simulation(t_data *data)
{
	int		i;
	t_philo	*phi;

	i = 0;
	phi = data->philos;
	data->start_time = gettime();
	while (i < data->number_of_philos)
	{
		set_long(&data->meal_check, &phi[i].last_meal, gettime());
		safe_thread(&phi[i].thread_id, philo_routine, &phi[i], CREATE);
		i++;
	}
	death_checker(data);
	exit_sim(data);
	exit_cleanly(data);
}
