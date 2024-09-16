#include "philo.h"

void    assign_second_fork(t_data *data)
{
    int i;

    i = 0;
    while(i < data->number_of_philos)
    {
        if (i == data->number_of_philos - 1)
            data->philos[i].second_fork = &data->philos[0].first_fork;
        else
            data->philos[i].second_fork = &data->philos[i + 1].first_fork;
        i++;
    }
}

void    init_philos(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    while(i < data->number_of_philos)
    {
        philo = data->philos + i;
        philo->id = i + 1;
        philo->full = 0;
        philo->meals = 0;
        philo->finished = 0;
        philo->data = data;
        philo->write_mutex = &data->write_lock;
        philo->philo_finished_mut = &data->p_f_mutex;
        pthread_mutex_init(&philo->first_fork, NULL);
        pthread_mutex_init(&philo->last_meal_mutex, NULL);
        pthread_mutex_init(&philo->full_mutex, NULL);
        i++;
    }
}

void    init(t_data *data)
{
    data->end = 0;
    data->philo_finished = 0;
    data->all_threads_ready = 0;
    data->start_time = gettime();
    data->philos = (t_philo *)safe_malloc((sizeof(t_philo) * data->number_of_philos), data);
    safe_mutex(&data->write_lock, INIT);
    safe_mutex(&data->end_mutex, INIT);
    // pthread_mutex_init(&data->write_lock, NULL);
    // pthread_mutex_init(&data->end_mutex, NULL);
    safe_mutex(&data->p_f_mutex, INIT);
    safe_mutex(&data->start_mutex, INIT);
    safe_mutex(&data->philo_full_mut, INIT);
    safe_mutex(&data->ready_mutex, INIT);
    init_philos(data);
    assign_second_fork(data);
}
