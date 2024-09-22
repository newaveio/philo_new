/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 19:10:57 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 13:20:04 by mbest            ###   ########.fr       */
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
		if(init(&data))
		{
			//clean memory
			return (1);
		}
		if(!data.philos)
			err_exit("Malloc failed\n");
		start_simulation(&data);
	}
	return (0);
}

// void	special_case(t_data data)
// {
// 	if (data.number_of_meals == 0)
// 		return ;
// 	else
// 	{
// 		printf("%-6d 1 has taken a fork\n", 0);
// 		ft_usleep(data.time_to_die);
// 		printf("%-6ld 1 died\n", data.time_to_die);
// 	}
// }
