#include "philo.h"

long gettime(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        err_exit("gettimeofday() failed.");
    return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

void ft_usleep(long milli_sec)
{
    long start_time;

    start_time = gettime();
    while ((gettime() - start_time) < milli_sec)
    {
        usleep(100);
    }
}

void    clean_exit(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    while(i < data->philo_num)
    {
        philo = data->philos + i;
        safe_mutex(&philo->philo_mutex, DESTROY);
        i++;
    }
    safe_mutex(&data->data_mutex, DESTROY);
    safe_mutex(&data->write_mutex, DESTROY);
    free(data->forks);
    free(data->philos);
}
