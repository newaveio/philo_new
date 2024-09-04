/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 18:52:09 by mbest             #+#    #+#             */
/*   Updated: 2024/09/04 19:00:23 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void write_status_debug(int status, t_philo *philo, long elapsed)
{
    if (status == TAKE_FIRST_FORK && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" has taken the 1º fork\t\t\tfork nº %d\n", elapsed, philo->id, philo->first_fork->id);
    else if (status == TAKE_SECOND_FORK && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" has taken the 2º fork\t\t\tfork nº %d\n", elapsed, philo->id, philo->second_fork->id);
    else if (status == EATING && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" is eating\t\t\tmeals eaten: %ld\n", elapsed, philo->id, philo->meals_eaten);
    else if (status == SLEEPING && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" is sleeping\n", elapsed, philo->id);
    else if (status == THINKING && !is_sim_finished(philo->data))
        printf(BLU"%ld"GRE" %d"RST" is thinking\n", elapsed, philo->id);
    else if (status == DIED && !is_sim_finished(philo->data))
        printf(RED"%ld"GRE" %d"RST" died\n", elapsed, philo->id); 
}

// void    write_status_debug(int status, t_philo *philo, long elapsed)
// {
//     if (status == TAKE_FIRST_FORK && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" has taken the 1º fork\t\t\tfork nº %d\n", elapsed, philo->id, philo->first_fork->id);
//     else if (status == TAKE_SECOND_FORK && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" has taken the 2º fork\t\t\tfork nº %d\n", elapsed, philo->id, philo->second_fork->id);
//     else if (status == EATING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is eating\n", elapsed, philo->id);
//     else if (status == SLEEPING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is sleeping\n", elapsed, philo->id);
//     else if (status == THINKING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is thinking\n", elapsed, philo->id);
//     else if (status == DIED && !is_sim_finished(philo->data))
//         printf(RED"%ld"GRE" %d"RST" died\n", elapsed, philo->id); 
// }

void    write_status(t_philo *philo, t_philo_status status, bool debug)
{
    long elapsed_time;

    elapsed_time = gettime() - philo->data->start_time;
    if (debug)
        write_status_debug(status, philo, elapsed_time);
    else
    {
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
}

// void    write_status(t_philo *philo, t_philo_status status)
// {
//     long elapsed_time;

//     elapsed_time = gettime() - philo->data->start_time;
//     safe_mutex(&philo->data->write_mutex, LOCK);
//     if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" has taken a fork\n", elapsed_time, philo->id);
//     else if (status == EATING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is eating\n", elapsed_time, philo->id);
//     else if (status == SLEEPING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is sleeping\n", elapsed_time, philo->id);
//     else if (status == THINKING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is thinking\n", elapsed_time, philo->id);
//     else if (status == DIED && !is_sim_finished(philo->data))
//         printf(RED"%ld"GRE" %d"RST" died\n", elapsed_time, philo->id);
//     safe_mutex(&philo->data->write_mutex, UNLOCK);
// }

void    thinking(t_philo *philo)
{
    write_status(philo, THINKING, DEBUG);
}

void    eat(t_philo *philo)
{
    safe_mutex(&philo->first_fork->fork, LOCK);
    write_status(philo, TAKE_FIRST_FORK, DEBUG);
    safe_mutex(&philo->second_fork->fork, LOCK);
    write_status(philo, TAKE_SECOND_FORK, DEBUG);

    set_long(&philo->philo_mutex, &philo->last_meal, gettime());
    // printf("last meal = %ld\n", philo->last_meal);
    
    // Protected the incrementation in a thread safe maner
    increase_long(&philo->philo_mutex, &philo->meals_eaten); // BETTER THIS WAY

    write_status(philo, EATING, DEBUG);
    ft_usleep(philo->data->time_to_eat);
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
    set_long(&philo->philo_mutex, &philo->last_meal, gettime());
    increase_long(&philo->data->data_mutex, &philo->data->threads_running);
    
    // if (philo->id % 2 == 0)
    //     ft_usleep(100);
    while(!is_sim_finished(philo->data))
    {
        if (philo->full)
            break; // find something else then BREAK
        eat(philo);
        write_status(philo, SLEEPING, DEBUG);
        ft_usleep(philo->data->time_to_sleep);
        thinking(philo);
    }
    return (NULL);
}

void *only_one(void *args)
{
    t_philo *philo;

    philo = (t_philo *)args;
    wait_for_threads(philo->data);
    set_long(&philo->philo_mutex, &philo->last_meal, gettime());
    increase_long(&philo->data->data_mutex, &philo->data->threads_running);
    write_status(philo, TAKE_FIRST_FORK, DEBUG);
    while(!is_sim_finished(philo->data))
        usleep(100);
    return (NULL);
}

void    start_simulation(t_data *data)
{
    int i;

    i = 0;
    if (data->num_meals_limit == 0)
        return; 
    else if (data->philo_num == 1)
    {
        // SPECIAL CASE
        safe_thread(&data->philos[0].thread_id, only_one, &data->philos[0], CREATE);
    }
    else
    {
        //! Philo routine set up
        while(i < data->philo_num)
        {
            safe_thread(&data->philos[i].thread_id, dinner_simulation, &data->philos[i], CREATE);
            i++;
        }
    }
    //! Monitor routine set up
    safe_thread(&data->monitor, monitor_routine, data, CREATE);

    
    data->start_time = gettime();  // Not sure if needed, the monitor while check if a philo is dead 
    set_int(&data->data_mutex, &data->are_threads_ready, 1);
    i = 0;
    while (i < data->philo_num)
    {
        safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }
    set_int(&data->data_mutex, &data->end_simulation, 1);
    safe_thread(&data->monitor, NULL, NULL, JOIN);
}
