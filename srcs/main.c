#include "philo.h"


void print_simulation_info(t_data *data)
{
    printf("Number of Philosophers: %ld\n", data->number_of_philos);
    printf("Time to Die: %ld ms\n", data->time_to_die);
    printf("Time to Eat: %ld ms\n", data->time_to_eat);
    printf("Time to Sleep: %ld ms\n", data->time_to_sleep);
    if (data->number_of_meals != -1)
        printf("Number of Meals: %ld\n", data->number_of_meals);
    else
        printf("Number of Meals: Unlimited\n");
}


int main(int ac, char **av)
{
    t_data data;

    if(ac == 5 || ac == 6)
    {
        parsing(&data, av);
        // print_simulation_info(&data);
        init(&data);
        // return (0);
        // print_data(&data);
        // print_philos(&data);
        start_simulation(&data);
        // printf("END\n");
    }
    return (0);
}



    // if (data->number_of_meals == 0) 
    //     return ; //! We are finished
    // else if (data->number_of_philos == 1) { //! DO LATER
    //     // printf("SPECIAL CASE - DO LATER\n");
    //     return ;
    // }