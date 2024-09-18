#include "philo.h"

long gettime(void)
{
    long time;
    struct timeval      tv;

    time = 0;
    if(gettimeofday(&tv, NULL) == -1)
        err_exit("gettimeofday() failed");
    time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
    return (time);
}

void ft_usleep(long time_in_ms)
{
    long start_time;

    start_time = gettime();
    while (gettime() - start_time < time_in_ms)
        usleep(10);
}

