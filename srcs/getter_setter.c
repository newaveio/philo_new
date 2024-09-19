#include "philo.h"

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

void    set_int(t_mtx *mutex, int *dest, int value)
{
    safe_mutex(mutex, LOCK);
    *dest = value;
    safe_mutex(mutex, UNLOCK);
}

int    get_int(t_mtx *mutex, int *value)
{
    int ret;

    safe_mutex(mutex, LOCK);
    ret = *value;
    safe_mutex(mutex, UNLOCK);
    return (ret);
}

void    increase_long(t_mtx *mutex, long *dest)
{
    safe_mutex(mutex, LOCK);
    (*dest)++;
    safe_mutex(mutex, UNLOCK);
}

void    increase_int(t_mtx *mutex, int *dest)
{
    safe_mutex(mutex, LOCK);
    (*dest)++;
    safe_mutex(mutex, UNLOCK);
}
