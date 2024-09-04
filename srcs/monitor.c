#include "philo.h"

int philo_is_dead(t_philo *philo)
{
    long elapsed;
    long time_to_die;

    if (get_int(&philo->philo_mutex, &philo->full))
        return (0);
    elapsed = gettime() - get_long(&philo->philo_mutex, &philo->last_meal);
    time_to_die = philo->data->time_to_die;

    if (elapsed > time_to_die)
    {
        return (1);
    }
    else
        return (0);
}

void *monitor_routine(void *args)
{
    int i;
    t_data *data;
    data = (t_data *)args;

    while (!are_threads_ready(&data->data_mutex, &data->threads_running, data->philo_num)) // Busy wait
        ;

    while(!is_sim_finished(data))
    {
        // printf("BLABLA\n");
        i = 0;
        while (i < data->philo_num && !is_sim_finished(data))
        {
            if (philo_is_dead(data->philos + i))
            {
                write_status(data->philos + i, DIED, DEBUG);
                set_int(&data->data_mutex, &data->end_simulation, 1);
            }
            i++;
        }
    }    
    return (NULL);
}