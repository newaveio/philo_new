/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:10:57 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 15:17:06 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data	data;

	if (ac == 5 || ac == 6)
	{
		if (parsing(&data, av))
			return (1);
		if (ft_alloc(&data))
			return (1);
		if (init(&data))
			return (free(data.philos), 1);
		start_simulation(&data);
	}
	return (0);
}
