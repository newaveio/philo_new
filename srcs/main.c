#include "philo.h"

int main(int ac, char **av)
{
    (void)av;
    t_data data;

    if (ac == 5 || ac == 6)
    {
        // parse the input
        parsing(&data, av);
        // printf("Parsing finished\n");
        // usleep(data.time_to_eat);
        // return (0);

        // init data and philos
        init_data(&data);
        // printf("Initialisation finished\n");

        // simulation
        start_simulation(&data);

        // clean
        clean_exit(&data);
    }
    else
    {
        err_exit("Wrong input\n"GRE"Correct is: ./philo 5 800 200 200 [4]"RST);
    }
}
