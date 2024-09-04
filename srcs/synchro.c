#include "philo.h"

/* SPINLOCK while threads are not ready */
void    wait_for_threads(t_data *data)
{
    while(get_int(&data->data_mutex, &data->are_threads_ready) != 1)
        ;
}

int     are_threads_ready(t_mtx *mutex, long *threads, long philo_nbr)
{
    int ret;

    ret = 0;
    safe_mutex(mutex, LOCK);
    if (*threads == philo_nbr)
        ret = 1;
    safe_mutex(mutex, UNLOCK);
    return (ret);
}

void    increase_long(t_mtx *mutex, long *value)
{
    safe_mutex(mutex, LOCK);
    (*value)++;
    safe_mutex(mutex, UNLOCK);
}
