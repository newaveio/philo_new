#include "philo.h"

int main(int ac, char **av)
{
    (void)av;
    t_data data;

    if (ac == 5 || ac == 6)
    {
        // parse the input
        parsing(&data, av);
        printf("Parsing finished\n");
        // init data and philos
        init_data(&data);
        printf("Initialisation finished\n");
        // simulation
        start_simulation(&data);
        // clean
    }
    else
    {
        err_exit("Wrong input\n"GRE"Correct is: ./philo 5 800 200 200 [4]"RST);
    }
}
