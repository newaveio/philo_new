#include "philo.h"

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
