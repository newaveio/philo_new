#include "philo.h"

static void	fork_assignement(t_philo *philo, t_fork *forks, int philo_position)
{
    int philo_nbr;

    philo_nbr = philo->data->philo_num;
    if (philo->id % 2 == 0)
    {
        philo->first_fork = &forks[philo_position];
        philo->second_fork = &forks[(philo_position + 1) % philo_nbr];
    }
    else
    {
        philo->first_fork = &forks[(philo_position + 1) % philo_nbr];
        philo->second_fork = &forks[philo_position];
    }
}


static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	while (i < data->philo_num)
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

void	init_data(t_data *data)
{
	int	i;

	i = 0;
	data->end_simulation = 0;
    data->are_threads_ready = 0;
	data->threads_running = 0;
	data->philos = safe_malloc(sizeof(t_philo) * data->philo_num);
	data->forks = safe_malloc(sizeof(t_fork) * data->philo_num);
    safe_mutex(&data->data_mutex, INIT);
	safe_mutex(&data->write_mutex, INIT);
	while (i < data->philo_num)
	{
		safe_mutex(&data->forks[i].fork, INIT);
		data->forks[i].id = i; // REMOVE AT THE END THIS IS FOR DEBUGGING
		i++;
	}
	philo_init(data);
}
