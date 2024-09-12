#include "philo_new.h"


// void    write_status(t_philo *philo, t_philo_status status)
// {
//     long elapsed_time;

//     elapsed_time = gettime() - philo->data->start_time;
//     safe_mutex(&philo->data->write_mutex, LOCK);
//     if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" has taken a fork\n", elapsed_time, philo->id);
//     else if (status == EATING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is eating\n", elapsed_time, philo->id);
//     else if (status == SLEEPING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is sleeping\n", elapsed_time, philo->id);
//     else if (status == THINKING && !is_sim_finished(philo->data))
//         printf(BLU"%ld"GRE" %d"RST" is thinking\n", elapsed_time, philo->id);
//     else if (status == DIED && !is_sim_finished(philo->data))
//         printf(RED"%ld"GRE" %d"RST" died\n", elapsed_time, philo->id);
//     safe_mutex(&philo->data->write_mutex, UNLOCK);
// }

void    ecrire_console(t_philo *philo)
{
    safe_mutex(&philo->philo_mutex, LOCK);
    printf("This is philo number %d\n", philo->id);
    safe_mutex(&philo->philo_mutex, UNLOCK);
}

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    wait_for_threads(philo->data);
    printf("This msg should not be printed out\n");
    return(NULL);
}

void    start_simulation(t_data *data)
{
    int i;

    i = 0;
    if (data->number_of_meals == 0)
        return ;
    else if (data->num_philos == 1)
    {
        printf("SPECIAL CASE\n");
    }
    else
    {
        while(i < data->num_philos)
        {
            printf("Creating threads %d\n", i +1);
            safe_thread(&data->philos[i].th_id, philo_routine, &data->philos[i], CREATE);
            i++;
        }
    }
    sleep(10);
}
