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

void special_case(t_data data)
{
    if (data.number_of_meals == 0)
        return ;
    else
    {
        printf("%-6d 1 has taken a fork\n", 0);
        ft_usleep(data.time_to_die);
        printf("%-6ld 1 died\n", data.time_to_die);
    }
}

int main(int ac, char **av)
{
    t_data data;

    if(ac == 5 || ac == 6)
    {
        parsing(&data, av);
        if (data.number_of_meals == 0 || data.number_of_philos == 1)
        {
            special_case(data);
            return (0);
        }
        init(&data);
        start_simulation(&data);
    }
    return (0);
}
