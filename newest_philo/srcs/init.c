#include "philo_new.h"

static void fork_assignement(t_philo *philo, t_fork *forks, int philo_position)
{
    int philo_nbr;

    philo_nbr = philo->data->num_philos;
    philo->first_fork = &forks[philo_position];
    if (philo_position == philo_nbr - 1)
    {
        philo->second_fork = &forks[0];
    }
    else
    {
        philo->second_fork = &forks[philo_position + 1];
    }
}

static void philo_init(t_data *data)
{
    int i;
    // int ret;
    t_philo *philo;

    i = 0;
    while(i < data->num_philos)
    {
        philo = data->philos + i;
        philo->id = i + 1;
        philo->full = 0;
        philo->meals_eaten = 0;
        philo->data = data;
        fork_assignement(philo, data->forks, i);
        i++;
    }
}

void    init_data(t_data *data)
{
    int i;
    int ret;

    i = 0;
    data->free_list = NULL;
    data->philos = (t_philo *)safe_malloc((sizeof(t_philo) * data->num_philos), data);
    data->forks = (t_fork *)safe_malloc((sizeof(t_fork) * data->num_philos), data);
    while (i < data->num_philos)
    {
        ret = pthread_mutex_init(&data->forks[i].fork, NULL);
        if (ret != 0)
        {
            exit_cleanly(data);
        }
        data->forks[i].id = i + 1;
        i++;
    }
    ret = pthread_mutex_init(&data->start_mutex, NULL);
    if (ret != 0)
    {
        exit_cleanly(data);
    }
    philo_init(data);
}
