#include "philo.h"

void    eat(t_philo *philo)
{
    if (philo->id % 2 == 0)
    {
        safe_mutex(philo->second_fork, LOCK);
        write_status(philo, philo->write_mutex, TAKE_SECOND_FORK, DEBUG);
        safe_mutex(&philo->first_fork, LOCK);
        write_status(philo, philo->write_mutex, TAKE_FIRST_FORK, DEBUG);
        set_long(&philo->last_meal_mutex, &philo->last_meal, gettime());
        write_status(philo, philo->write_mutex, EATING, DEBUG);
        philo->meals++;
    }
    else
    {
        safe_mutex(&philo->first_fork, LOCK);
        write_status(philo, philo->write_mutex, TAKE_FIRST_FORK, DEBUG);
        safe_mutex(philo->second_fork, LOCK);
        write_status(philo, philo->write_mutex, TAKE_SECOND_FORK, DEBUG);
        set_long(&philo->last_meal_mutex, &philo->last_meal, gettime());
        write_status(philo, philo->write_mutex, EATING, DEBUG);
        philo->meals++;
    }
    if (philo->meals == philo->data->number_of_meals)
    {
        increase_long(&philo->data->p_f_mutex, &philo->data->philo_finished);
        philo->full = 1;
    }
    ft_usleep(philo->data->time_to_eat);
    safe_mutex(&philo->first_fork, UNLOCK);
    safe_mutex(philo->second_fork, UNLOCK);
}

void    sleep_philo(t_philo *philo)
{
    write_status(philo, philo->write_mutex, SLEEPING, DEBUG);
    ft_usleep(philo->data->time_to_sleep);
}

void    think(t_philo *philo)
{
    write_status(philo, philo->write_mutex, THINKING, DEBUG);
}

void    iam_full(t_philo *philo)
{
    increase_long(&philo->data->philo_full_mut, &philo->data->philo_full);
}

void    wait_for_all_threads(t_data *data)
{
    while(!get_int(&data->ready_mutex, &data->all_threads_ready))
    {
        usleep(100);
    }
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;


    wait_for_all_threads(philo->data);
    set_long(&philo->last_meal_mutex, &philo->last_meal, get_long(&philo->data->start_mutex, &philo->data->start_time));
    // printf("last meal for philo %d is %ld\n", philo->id, philo->last_meal);
    if (philo->id % 2 == 0)
        ft_usleep(100);

    while(!is_simulation_finished(philo->data))
    {
        if(philo->full)
        {
            iam_full(philo);
            break;
        }
        eat(philo);
        sleep_philo(philo);
        think(philo);
    }
    return (NULL);
}

void    *monitor_routine(void *args)
{
    int i;
    long current_time;
    long last_meal_time;
    t_data *data;

    data = (t_data *)args;
    usleep(100);
    while(!is_simulation_finished(data))
    {
        i = 0;
        while (i < data->number_of_philos)
        {
            // if (get_int(&data->philos[i].full_mutex, &data->philos[i].full))
            //     return (NULL);
            current_time = gettime();
            last_meal_time = get_long(&data->philos[i].last_meal_mutex, &data->philos[i].last_meal);
            // printf("[%d] current_time = %ld - last_meal = %ld\n", data->philos[i].id, current_time, last_meal_time);
            // printf("[%d] Time since last meal: %ld\n", data->philos[i].id, current_time - last_meal_time);
            if (current_time - last_meal_time > data->time_to_die)
            {
                set_int(&data->end_mutex, &data->end, 1);
                write_status(&data->philos[i], &data->write_lock, DIED, DEBUG);
                return (NULL);
            }
            i++;
        }
        usleep(100);
    }
    return (NULL);
}

void    start_simulation(t_data *data)
{
    int i;

    i = 0;
    if (data->number_of_meals == 0) 
        return ; //! We are finished
    else if (data->number_of_philos == 1) { //! DO LATER
        // printf("SPECIAL CASE - DO LATER\n");
        return ;
    }
    else
    {
        while(i < data->number_of_philos)
        {
            safe_thread(&data->philos[i].thread_id, philo_routine, &data->philos[i], CREATE);
            i++;
        }
        set_long(&data->start_mutex, &data->start_time, gettime());
        set_int(&data->ready_mutex, &data->all_threads_ready, 1);
        safe_thread(&data->monitor, monitor_routine, data, CREATE);
        i = 0;
        while(i < data->number_of_philos)
        {
            safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
            i++;
        }
        safe_thread(&data->monitor, NULL, NULL, JOIN);
    }
}
