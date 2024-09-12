#include "philo_new.h"

void wait_for_threads(t_data *data)
{
    printf("ENTERED THE FUNCTION\n");
    while (get_int(&data->data_mutex, &data->threads_ready) != 1)
    {
        printf("Still in spinlock, threads_ready = %d\n", data->threads_ready);
        usleep(100000);
    }
    printf("EXITING THE FUNCTION\n");
}
