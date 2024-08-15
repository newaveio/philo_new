/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:52:09 by mbest             #+#    #+#             */
/*   Updated: 2024/08/15 19:58:48 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *dinner_simulation(void *args)
{
    t_philo *philo;

    philo = (t_philo *)args;
    wait_for_threads(philo->data);


    return (NULL);
}

void    start_simulation(t_data *data)
{
    int i;

    i = 0;
    if (data->num_meals_limit == 0)
        return; 
    else if (data->philo_num == 1)
        ; // SPECIAL CASE
    else
    {
        while(i < data->philo_num)
        {
            safe_thread(&data->philos[i].thread_id, dinner_simulation, &data->philos[i], CREATE);
        }
    }
    // Start of simulation
    

    // threads are ready at this point!!
    set_int(&data->data_mutex, &data->end_simulation, 1);

}