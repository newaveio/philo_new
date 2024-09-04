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

