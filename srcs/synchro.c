#include "philo.h"

/* SPINLOCK while threads are not ready */
void    wait_for_threads(t_data *data)
{
    while(get_int(&data->data_mutex, &data->are_threads_ready) != 1)
        ;
}

