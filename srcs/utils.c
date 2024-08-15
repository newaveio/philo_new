#include "philo.h"

void    err_exit(char *msg)
{
    printf(RED"%s\n"RST, msg);
    exit(EXIT_FAILURE);
}

void    set_int(t_mtx *mutex, int *dest, int value)
{
    safe_mutex(mutex, LOCK);
    *dest = value;
    safe_mutex(mutex, UNLOCK);
}

int     get_int(t_mtx *mutex, int *value)
{
    int ret;

    safe_mutex(mutex, LOCK);
    ret = *value;
    safe_mutex(mutex, UNLOCK);
    return (ret);
}

void    set_long(t_mtx *mutex, long *dest, long value)
{
    safe_mutex(mutex, LOCK);
    *dest = value;
    safe_mutex(mutex, UNLOCK);
}

long    get_long(t_mtx *mutex, long *value)
{
    long ret;

    safe_mutex(mutex, LOCK);
    ret = *value;
    safe_mutex(mutex, UNLOCK);
    return (ret);
}

int     is_sim_finished(t_data *data)
{
    return (get_int(&data->data_mutex, data->end_simulation));
}
