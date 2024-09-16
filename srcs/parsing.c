#include "philo.h"

void    parsing(t_data *data, char **av)
{
    data->number_of_philos = ft_atol(av[1]);
    data->time_to_die = ft_atol(av[2]);
    data->time_to_eat = ft_atol(av[3]);
    data->time_to_sleep = ft_atol(av[4]);
    if(av[5])
        data->number_of_meals = ft_atol(av[5]);
    else
        data->number_of_meals = -1;
}
