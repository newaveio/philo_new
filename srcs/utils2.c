#include "philo.h"

long gettime(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        err_exit("gettimeofday() failed.");
    return (tv.tv_sec * 1e3 + (tv.tv_usec / 1e3));
    // return (tv.tv_sec * 1e6 + tv.tv_usec);
}

void ft_usleep(t_data *data, long usec)
{
    long start_time = gettime();
    while ((gettime() - start_time) < usec)
    {
        if (is_sim_finished(data))
            break;
        usleep(100); // Sleep for a short interval to avoid busy-waiting
    }
}


// void    ft_usleep(t_data *data, long usec)
// {
//     long start;
//     long elapsed;
//     long remaining;

//     start = gettime();
//     while(gettime() - start < usec)
//     {
//         if (is_sim_finished(data))
//             break;
//         elapsed = gettime() - start;
//         remaining = usec - elapsed;
//         if (remaining > 1e3)
//             usleep(remaining);
//             // usleep(usec / 2);
//             // usleep(remaining / 2);
//         else
//         {
//             // SpInLoCk
//             while(gettime() - start < usec)
//                 ;
//         }
//     }
// }
