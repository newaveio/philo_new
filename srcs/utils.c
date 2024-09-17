#include "philo.h"

// int is_simulation_finished(t_data *data)
// {
//     int i;
//     long all_full;
//     int finished;

//     i = 0;
//     // printf("all full = %ld\nfinished = %d\n", all_full, finished);

//     if (all_full == data->number_of_philos || finished)
//     {
//         // printf("all_full = %ld\nfinished = %d\n", all_full, finished);
//         return (1);
//     }
//     while (i < data->number_of_philos)
//     {
//         if (!get_int(&data->philos[i].full_mutex, &data->philos[i].full))
//             return (0);
//         i++;
//     }
//     return (1);
// }


void    write_status(t_philo *philo, t_mtx *mutex, t_philo_status status)
{
    long time;

    time = gettime() - philo->data->start_time;
    if (!get_int(&philo->data->dead_lock, &philo->data->died))
    {
        safe_mutex(mutex, LOCK);
        if((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK))
            printf("%-6ld %d has taken a fork\n", time, philo->id);
        else if (status == EATING)
            printf("%-6ld %d is eating\n", time, philo->id);
        else if (status == SLEEPING)
            printf("%-6ld %d is sleeping\n", time, philo->id);
        else if (status == THINKING)
            printf("%-6ld %d is thinking\n", time, philo->id);
        else if (status == DIED)
            printf("%-6ld %d died\n", time, philo->id);
        safe_mutex(mutex, UNLOCK);
    }
}

void    err_exit(char *str)
{
    printf("%s\n", str);
    exit(EXIT_FAILURE);
}

static int is_space(char c)
{
    if (c == 32 || (c >= 9 && c <= 13))
        return (1);
    return(0);
}
static int is_digit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

char *valid_input(char *str)
{
    int len;
    char *number;

    len = 0;
    while (is_space(*str))
        str++;
    if (*str == '+')
        str++;
    else if (*str == '-')
        err_exit("Only positive numbers");
    if (!is_digit(*str))
        err_exit("The input is not a digit");
    number = str;
    while(is_digit(*str))
    {
        len++;
        str++;
    }
    if (len > 10)
        err_exit("The value is too big. The limit is INT_MAX");
    return (number);
}

long ft_atol(char *str)
{
    long num;

    num = 0;
    str = valid_input(str);
    while(is_digit(*str))
    {
        num = (num * 10) + (*str - 48);
        str++;
    }
    if (num > INT_MAX)
        err_exit("The value is too big. The limit is INT_MAX");
    return (num);
}

