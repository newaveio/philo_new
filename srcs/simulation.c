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
        philo->full = 1;
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
    increase_long(philo->philo_finished_mut, &philo->data->philo_finished);
}
void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    philo->last_meal = philo->data->start_time;
    // printf("Last meal of philo %d is %ld\n", philo->id, philo->last_meal);
    if (philo->id % 2 == 0)
        ft_usleep(100);
    // printf("[Philo %d] Starting the routine\n", philo->id);
    while(!is_simulation_finished(philo->data))
    {
        if(philo->full)
        {
            iam_full(philo);
            break;
        }

        // EATING
        eat(philo);

        // SLEEPING
        sleep_philo(philo);

        // THINKING
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
    while(!is_simulation_finished(data))
    {
        i = 0;
        while (i < data->number_of_philos)
        {
            current_time = gettime();
            last_meal_time = get_long(&data->philos[i].last_meal_mutex, &data->philos[i].last_meal);
            // printf("Time since last meal: %ld\n", current_time - last_meal_time);
            if (current_time - last_meal_time > data->time_to_die)
            {
                set_int(&data->end_mutex, &data->end, 1);
                write_status(&data->philos[i], &data->write_lock, DIED, DEBUG);
                exit(42); //! Change this to a break to clean the program
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
        printf("SPECIAL CASE - DO LATER\n");
        return ;
    }
    else
    {
        // printf("data->end = %d\n", data->end);
        while(i < data->number_of_philos)
        {
            safe_thread(&data->philos[i].thread_id, philo_routine, &data->philos[i], CREATE);
            i++;
        }
        data->start_time = gettime();
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
