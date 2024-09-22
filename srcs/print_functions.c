/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:42:51 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 13:06:11 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	err_exit(char *str)
{
	printf("%s\n", str);
}

void	print_death(t_philo *philo, t_mtx *mutex)
{
	long	time;

	time = gettime() - philo->data->start_time;
	safe_mutex(mutex, LOCK);
	printf("%-6ld %d died\n", time, philo->id);
	safe_mutex(mutex, UNLOCK);
}

void	write_status(t_philo *philo, t_mtx *mutex, t_philo_status status)
{
	long	time;

	time = gettime() - philo->data->start_time;
	safe_mutex(mutex, LOCK);
	if (!get_int(&philo->data->dead_lock, &philo->data->died))
	{
		if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
			&& !get_int(&philo->data->dead_lock, &philo->data->died))
			printf("%-6ld %d has taken a fork\n", time, philo->id);
		else if (status == EATING && !get_int(&philo->data->dead_lock,
				&philo->data->died))
			printf("%-6ld %d is eating\n", time, philo->id);
		else if (status == SLEEPING && !get_int(&philo->data->dead_lock,
				&philo->data->died))
			printf("%-6ld %d is sleeping\n", time, philo->id);
		else if (status == THINKING && !get_int(&philo->data->dead_lock,
				&philo->data->died))
			printf("%-6ld %d is thinking\n", time, philo->id);
		else if (status == DIED)
			printf("%-6ld %d died\n", time, philo->id);
	}
	safe_mutex(mutex, UNLOCK);
}
