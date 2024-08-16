/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:52:09 by mbest             #+#    #+#             */
/*   Updated: 2024/08/16 19:57:41 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    write_status(t_philo *philo, t_philo_status status)
{
    long elapsed_time;

    elapsed_time = gettime() - philo->data->start_time;
    safe_mutex(&philo->data->write_mutex, LOCK);
    if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" has taken a fork\n", elapsed_time, philo->id);
    else if (status == EATING && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" is eating\n", elapsed_time, philo->id);
    else if (status == SLEEPING && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" is sleeping\n", elapsed_time, philo->id);
    else if (status == THINKING && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" is thinking\n", elapsed_time, philo->id);
    else if (status == DIED && !is_sim_finished(philo->data))
        printf(RED"%ld"GRE" %d"RST" died\n", elapsed_time, philo->id);
    safe_mutex(&philo->data->write_mutex, UNLOCK);
}

void    thinking(t_philo *philo)
{
    write_status(philo, THINKING);
}

void    eat(t_philo *philo)
{
    safe_mutex(&philo->first_fork->fork, LOCK);
    write_status(philo, TAKE_FIRST_FORK);
    safe_mutex(&philo->second_fork->fork, LOCK);
    write_status(philo, TAKE_SECOND_FORK);

    set_long(&philo->philo_mutex, &philo->last_meal, gettime());
    philo->meals_eaten++;
    write_status(philo, EATING);
    // usleep(philo->data->time_to_eat);
    ft_usleep(philo->data, philo->data->time_to_eat * 1000);
    if (philo->data->num_meals_limit > 0 && philo->meals_eaten == philo->data->num_meals_limit)
        set_int(&philo->philo_mutex, &philo->full, 1);
    
    safe_mutex(&philo->first_fork->fork, UNLOCK);
    safe_mutex(&philo->second_fork->fork, UNLOCK);
}

void    *dinner_simulation(void *args)
{
    t_philo *philo;

    philo = (t_philo *)args;
    wait_for_threads(philo->data); // SPINLOCK
    // Set last meal time
    while(!is_sim_finished(philo->data))
    {
        // Am i full ?
        if (philo->full)
            break; // find something else then BREAK
        
        // eat
        eat(philo);

        //sleep
        ft_usleep(philo->data, philo->data->time_to_sleep);

        //think
        thinking(philo);
    }
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
            i++;
        }
    }
    // Start of simulation
    data->start_time = gettime(); 

    // threads are ready at this point!!
    set_int(&data->data_mutex, &data->are_threads_ready, 1);

    // Wait for everyone
    i = 0;
    while (i < data->philo_num)
    {
        safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }
}
