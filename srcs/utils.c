#include "philo.h"


void    write_status(t_philo *philo, t_mtx *mutex, t_philo_status status)
{
    long time;

    time = gettime() - philo->data->start_time;
    if (!get_int(&philo->data->dead_lock, &philo->data->died))
    {
        safe_mutex(mutex, LOCK);
        if((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
            printf("%-6ld %d has taken a fork\n", time, philo->id);
        else if (status == EATING)
            printf("%-6ld %d is eating\n", time, philo->id);
        else if (status == SLEEPING)
            printf("%-6ld %d is sleeping\n", time, philo->id);
        else if (status == THINKING)
            printf("%-6ld %d is thinking\n", time, philo->id);
        else if (status == DIED)
            printf("%-6ld %d died\n", time, philo->id);
        safe_mutex(mutex, UNLOCK);
    }
}

void    err_exit(char *str)
{
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

