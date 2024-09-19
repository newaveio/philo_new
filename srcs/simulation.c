#include "philo.h"


void    sleep_philo(t_philo *philo)
{
    write_status(philo, &philo->data->write_lock, SLEEPING);
    ft_usleep(philo->data->time_to_sleep);
}

void    think(t_philo *philo)
{
    write_status(philo, &philo->data->write_lock, THINKING);
    if (philo->data->number_of_philos % 2 == 0)
        ft_usleep(philo->data->time_to_eat - philo->data->time_to_sleep);
    else
        ft_usleep(philo->data->time_to_eat * 2 - philo->data->time_to_sleep);
}

void    wait_for_all_threads(t_data *data)
{
    while(!get_int(&data->ready_lock, &data->all_threads_ready))
    {
        usleep(100);
    }
}

// void    eat(t_philo *philo)
// {
//     if (philo->id % 2 == 0)
//     {
//         safe_mutex(philo->second_fork, LOCK);
//         write_status(philo, &philo->data->write_lock, TAKE_SECOND_FORK);
//         safe_mutex(&philo->first_fork, LOCK);
//         write_status(philo, &philo->data->write_lock, TAKE_FIRST_FORK);
//         write_status(philo, &philo->data->write_lock, EATING);
//         set_long(&philo->data->meal_check, &philo->last_meal, gettime());
//         ft_usleep(philo->data->time_to_eat);
//         // increase_int()
//         philo->meals++;
//         if (philo->meals == philo->data->number_of_meals)
//             set_int(&philo->full_mutex, &philo->full, 1);
//         safe_mutex(philo->second_fork, UNLOCK);
//         safe_mutex(&philo->first_fork, UNLOCK);
//     }
//     else
//     {
//         safe_mutex(&philo->first_fork, LOCK);
//         write_status(philo, &philo->data->write_lock, TAKE_FIRST_FORK);
//         safe_mutex(philo->second_fork, LOCK);
//         write_status(philo, &philo->data->write_lock, TAKE_SECOND_FORK);
//         write_status(philo, &philo->data->write_lock, EATING);
//         set_long(&philo->data->meal_check, &philo->last_meal, gettime());
//         ft_usleep(philo->data->time_to_eat);
//         philo->meals++;
//         if (philo->meals == philo->data->number_of_meals)
//             set_int(&philo->full_mutex, &philo->full, 1);
//         safe_mutex(&philo->first_fork, UNLOCK);
//         safe_mutex(philo->second_fork, UNLOCK);
//     }
// }

// void    eat(t_philo *philo)
// {
//         safe_mutex(philo->second_fork, LOCK);
//         write_status(philo, &philo->data->write_lock, TAKE_SECOND_FORK);
//         safe_mutex(&philo->first_fork, LOCK);
//         write_status(philo, &philo->data->write_lock, TAKE_FIRST_FORK);
//         write_status(philo, &philo->data->write_lock, EATING);
//         set_long(&philo->data->meal_check, &philo->last_meal, gettime());
//         ft_usleep(philo->data->time_to_eat);
//         philo->meals++;
//         if (philo->meals == philo->data->number_of_meals)
//             set_int(&philo->full_mutex, &philo->full, 1);
//         safe_mutex(philo->second_fork, UNLOCK);
//         safe_mutex(&philo->first_fork, UNLOCK);
// }

void    eat(t_philo *philo)
{
    // safe_mutex(&philo->data->eating, LOCK);
    if (philo->id == philo->data->number_of_philos)
    {
        safe_mutex(philo->second_fork, LOCK);
        write_status(philo, &philo->data->write_lock, TAKE_SECOND_FORK);
        safe_mutex(&philo->first_fork, LOCK);
        write_status(philo, &philo->data->write_lock, TAKE_FIRST_FORK);
        write_status(philo, &philo->data->write_lock, EATING);
        set_long(&philo->data->meal_check, &philo->last_meal, gettime());
        ft_usleep(philo->data->time_to_eat);
        increase_int(&philo->meal_check, &philo->meals);
        // philo->meals++;
        if (philo->meals == philo->data->number_of_meals)
            set_int(&philo->full_mutex, &philo->full, 1);
        safe_mutex(philo->second_fork, UNLOCK);
        safe_mutex(&philo->first_fork, UNLOCK);
    }
    else
    {
        safe_mutex(&philo->first_fork, LOCK);
        write_status(philo, &philo->data->write_lock, TAKE_FIRST_FORK);
        safe_mutex(philo->second_fork, LOCK);
        write_status(philo, &philo->data->write_lock, TAKE_SECOND_FORK);
        write_status(philo, &philo->data->write_lock, EATING);
        set_long(&philo->data->meal_check, &philo->last_meal, gettime());
        ft_usleep(philo->data->time_to_eat);
        increase_int(&philo->meal_check, &philo->meals);
        // philo->meals++;
        if (philo->meals == philo->data->number_of_meals)
            set_int(&philo->full_mutex, &philo->full, 1);
        safe_mutex(&philo->first_fork, UNLOCK);
        safe_mutex(philo->second_fork, UNLOCK);
    }
    // safe_mutex(&philo->data->eating, UNLOCK);
}


void    *philo_routine(void *arg)
{
    t_philo *philo;
    t_data *data;

    philo = (t_philo *)arg;
    data = philo->data;
    // wait_for_all_threads(data);
    // set_long(&data->meal_check, &philo->last_meal, gettime());
    usleep(100);
    if (philo->id % 2)
        usleep(data->time_to_eat * 500);
        // usleep(100);
    while(!get_int(&data->dead_lock, &data->died))
    {   
        eat(philo);    
        sleep_philo(philo);
        think(philo);
        if (get_int(&philo->full_mutex, &philo->full))
            break;
    }
    return (NULL);
}

        // while(philo->meals > get_int(&philo->data->min_meals_mut, &philo->data->min_meals) || \
        //         find_philo_to_eat(data) != philo->id)
        // {
        //     if (get_int(&data->dead_lock, &data->died))
        //         return (NULL);
        //     usleep(100);
        // }
        // printf("Philosopher %d: Min meals = %d, My meals = %d\n", philo->id, get_int(&philo->data->min_meals_mut, &philo->data->min_meals), philo->meals);        

        // safe_mutex(&philo->data->min_meals_mut, LOCK);
        // if (philo->meals < get_int(&philo->data->min_meals_mut, &philo->data->min_meals))
        //     set_int(&philo->data->min_meals_mut, &philo->data->min_meals, philo->meals);

void    print_death(t_philo *philo, t_mtx *mutex)
{
    long time;

    time = gettime() - philo->data->start_time;
    safe_mutex(mutex, LOCK);
    printf("%-6ld %d died\n", time, philo->id);
    safe_mutex(mutex, UNLOCK);
}

void    death_checker(t_data *data)
{
    int i;
    // int min;
    // int current_meals;

    while (data->all_ate == 0)
    {
        i = 0;
        while(i < data->number_of_philos && !data->died)
        {
            if (!get_int(&data->philos[i].full_mutex, &data->philos[i].full) \
                && gettime() - get_long(&data->meal_check, &data->philos[i].last_meal) > data->time_to_die)
            {
                set_int(&data->dead_lock, &data->died, 1);
                print_death(&data->philos[i], &data->write_lock);                write_status(&data->philos[i], &data->write_lock, DIED);
            }
            i++;
        }
        if (get_int(&data->dead_lock, &data->died))
            break;
        i = 0;
        if (data->number_of_meals != -1)
        {
            while(i < data->number_of_philos && get_int(&data->philos[i].full_mutex, &data->philos[i].full))
                i++;
            if (i == data->number_of_philos)
                data->all_ate = 1;
        }
        usleep(100);
    }
}
        // i = 0;
        // min = get_int(&data->philos[0].meal_check, &data->philos[0].meals);
        // while (i < data->number_of_philos)
        // {
        //     current_meals = get_int(&data->philos[i].meal_check, &data->philos[i].meals);
        //     if (current_meals < min)
        //         min = current_meals;
        //     i++;
        // }
        // set_int(&data->min_meals_mut, &data->min_meals, min);

void exit_sim(t_data *data)
{
    int i;
    
    i = 0;
    while (i < data->number_of_philos)
    {
        safe_thread(&data->philos[i].thread_id, NULL, NULL, JOIN);
        i++;
    }
}

void    exit_cleanly(t_data *data)
{
    int i;

    i = 0;
    while(i < data->number_of_philos)
    {
        safe_mutex(&data->philos[i].first_fork, DESTROY);
        safe_mutex(&data->philos[i].full_mutex, DESTROY);
        i++;
    }
    safe_mutex(&data->write_lock, DESTROY);
    safe_mutex(&data->dead_lock, DESTROY);
    safe_mutex(&data->meal_check, DESTROY);
    free(data->philos);
}

void    start_simulation(t_data *data)
{
    int i;
    t_philo *phi;

    i =  0;
    phi = data->philos;
    data->start_time = gettime();
    while(i < data->number_of_philos)
    {
        set_long(&data->meal_check, &phi[i].last_meal, gettime());
        safe_thread(&phi[i].thread_id, philo_routine, &phi[i], CREATE);
        i++;
    }
    death_checker(data);
    exit_sim(data);
    exit_cleanly(data);
}

