#include "philo.h"

void    print_philos(t_data *data)
{
    int i;
    t_philo *philo;

    i = 0;
    while (i < data->number_of_philos)
    {
        philo = &data->philos[i];
        printf("Philo %d:\n", philo->id);
        printf("  Meals: %d\n", philo->meals);
        printf("  Full: %d\n", philo->full);
        printf("  Last meal: %ld\n", philo->last_meal);
        printf("  Write mutex: %s\n", philo->write_mutex != NULL ? "Initialized" : "Not initialized");

        // Check first fork mutex initialization
        if (pthread_mutex_lock(&philo->first_fork) == 0) {
            printf("  First fork mutex: Initialized\n");
            pthread_mutex_unlock(&philo->first_fork);
        } else {
            printf("  First fork mutex: Not initialized\n");
        }

        // Check second fork mutex initialization
        if (pthread_mutex_lock(philo->second_fork) == 0) {
            printf("  Second fork mutex: Initialized\n");
            pthread_mutex_unlock(philo->second_fork);
        } else {
            printf("  Second fork mutex: Not initialized\n");
        }

        i++;
    }
}

void    print_data(t_data *data)
{
    printf("Number of philos:\t%ld\n", data->number_of_philos);
    printf("Time to die:\t\t%ld\n", data->time_to_die);
    printf("Time to eat:\t\t%ld\n", data->time_to_eat);
    printf("Time to sleep:\t\t%ld\n", data->time_to_sleep);
    printf("Number of meals:\t%ld\n", data->number_of_meals);
    printf("Data -> end: %d\n", data->end);
}

void    exit_cleanly(t_data *data)
{
    int i;

    i = 0;
    while(i < data->number_of_philos)
    {
        safe_mutex(&data->philos[i].first_fork, DESTROY);
        i++;
    }
    safe_mutex(&data->p_f_mutex, DESTROY);
    safe_mutex(&data->write_lock, DESTROY);
    safe_mutex(&data->end_mutex, DESTROY);
    free(data->philos);
}

int main(int ac, char **av)
{
    t_data data;

    if(ac == 5 || ac == 6)
    {
        parsing(&data, av);
        init(&data);
        // return (0);
        // print_data(&data);
        // print_philos(&data);
        start_simulation(&data);
        exit_cleanly(&data);
        // printf("END\n");
    }
    return (0);
}