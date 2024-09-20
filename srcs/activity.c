/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   activity.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:16:50 by mbest             #+#    #+#             */
/*   Updated: 2024/09/20 16:47:00 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	sleep_philo(t_philo *philo)
{
	write_status(philo, &philo->data->write_lock, SLEEPING);
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	write_status(philo, &philo->data->write_lock, THINKING);
	if (philo->data->number_of_philos % 2 == 0)
		ft_usleep(philo->data->time_to_eat - philo->data->time_to_sleep + 10);
	else
		ft_usleep(philo->data->time_to_eat * 2 - philo->data->time_to_sleep + 10);
}

void	eat_last(t_philo *philo)
{
	safe_mutex(philo->second_fork, LOCK);
	write_status(philo, &philo->data->write_lock, TAKE_SECOND_FORK);
	safe_mutex(&philo->first_fork, LOCK);
	write_status(philo, &philo->data->write_lock, TAKE_FIRST_FORK);
	write_status(philo, &philo->data->write_lock, EATING);
	set_long(&philo->data->meal_check, &philo->last_meal, gettime());
	ft_usleep(philo->data->time_to_eat);
	philo->meals++;
	if (philo->meals == philo->data->number_of_meals)
		set_int(&philo->full_mutex, &philo->full, 1);
	safe_mutex(philo->second_fork, UNLOCK);
	safe_mutex(&philo->first_fork, UNLOCK);
}

void	eat(t_philo *philo)
{
	if (philo->id == philo->data->number_of_philos)
	{
		eat_last(philo);
	}
	else
	{
		safe_mutex(&philo->first_fork, LOCK);
		write_status(philo, &philo->data->write_lock, TAKE_FIRST_FORK);
		safe_mutex(philo->second_fork, LOCK);
		write_status(philo, &philo->data->write_lock, TAKE_SECOND_FORK);
		write_status(philo, &philo->data->write_lock, EATING);
		set_long(&philo->data->meal_check, &philo->last_meal, gettime());
		ft_usleep(philo->data->time_to_eat);
		philo->meals++;
		if (philo->meals == philo->data->number_of_meals)
			set_int(&philo->full_mutex, &philo->full, 1);
		safe_mutex(&philo->first_fork, UNLOCK);
		safe_mutex(philo->second_fork, UNLOCK);
	}
}
