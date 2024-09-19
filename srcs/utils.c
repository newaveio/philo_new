/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:49:10 by mbest             #+#    #+#             */
/*   Updated: 2024/09/19 18:58:56 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increase_long(t_mtx *mutex, long *dest)
{
	safe_mutex(mutex, LOCK);
	(*dest)++;
	safe_mutex(mutex, UNLOCK);
}

void	increase_int(t_mtx *mutex, int *dest)
{
	safe_mutex(mutex, LOCK);
	(*dest)++;
	safe_mutex(mutex, UNLOCK);
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
