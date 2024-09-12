#include "philo_new.h"

static void fork_assignement(t_philo *philo, t_mtx *forks, int philo_position)
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
    t_philo *philo;

    i = 0;
    while(i < data->num_philos)
    {
        philo = data->philos + i;
        philo->id = i + 1;
        philo->full = 0;
        philo->meals_eaten = 0;
        philo->data = data;
        safe_mutex(&philo->philo_mutex, INIT);
        fork_assignement(philo, data->forks, i);
        i++;
    }
}

void    init_data(t_data *data)
{
    int i;

    i = 0;
    data->free_list = NULL;
    data->threads_ready = 0;
    data->philos = (t_philo *)safe_malloc((sizeof(t_philo) * data->num_philos), data);
    while(i < data->num_philos)
    {
        safe_mutex(&data->forks[i], INIT);
        i++;
    }
    safe_mutex(&data->data_mutex, INIT);
    safe_mutex(&data->write_mutex, INIT);
    philo_init(data);
}
