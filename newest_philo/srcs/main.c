#include "philo_new.h"

int main(int ac, char **av)
{
    t_data  data;
    // (void)ac;
    (void)av;

    if (ac == 5 || ac == 6)
    {
        // We Good
        printf("Good Parameters\n");
        parsing(&data, av);
        init_data(&data);
        start_simulation(&data);
        exit_cleanly(&data);
    }
    else
    {
        err_exit("Wrong input\n"GRE"Correct is: ./philo 5 800 200 200 [4]"RST);
    }
    return (0);
}
