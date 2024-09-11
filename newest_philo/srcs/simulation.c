#include "philo_new.h"

void    wait_for_threads(t_data *data)
{
    while(get_int(&data->start_mutex, &data->threads_ready))
        ;
}

void    *dinner_simulation(void *args)
{
    t_philo *philo;

    philo = (t_philo *)args;
    wait_for_all_threads(philo->data);
}

void    start_simulation(t_data *data)
{
    int i;

    i = 0;
    if (data->number_of_meals == 0)
        return ;
    else if (data->num_philos == 1)
    {
        printf("SPECIAL CASE DO THE LOGIC LATER\n");
    }
    else
    {
        while (i < data->num_philos)
        {
            pthread_create(&data->philos[i].th_id, NULL, dinner_simulation, &data->philos[i]);
            i++;
        }
    }
}