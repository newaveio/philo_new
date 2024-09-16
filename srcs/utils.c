#include "philo.h"

int is_simulation_finished(t_data *data)
{
    long all_full;
    int finished;

    all_full = get_long(&data->p_f_mutex, &data->philo_finished);
    finished = get_int(&data->end_mutex, &data->end);
    // printf("all full = %ld\nfinished = %d\n", all_full, finished);

    if (all_full == data->number_of_philos || finished)
    {
        // printf("all_full = %ld\nfinished = %d\n", all_full, finished);
        return (1);
    }
    else
        return (0);
    // return(get_int(&data->end_mutex, &data->end));
}

void    write_status_debug(t_philo_status status, t_philo *philo, long time)
{
    if(status == TAKE_FIRST_FORK)
        printf("%-6ld %d has taken fork [1]\n", time, philo->id);
    else if(status == TAKE_SECOND_FORK)
        printf("%-6ld %d has taken fork [2]\n", time, philo->id);
    else if (status == EATING)
        printf("%-6ld %d is eating\n", time, philo->id);
    else if (status == SLEEPING)
        printf("%-6ld %d is sleeping\n", time, philo->id);
    else if (status == THINKING)
        printf("%-6ld %d is thinking\n", time, philo->id);
    else if (status == DIED)
        printf("%-6ld %d died\n", time, philo->id);
}

void    write_status(t_philo *philo, t_mtx *mutex, t_philo_status status, bool debug)
{
    long time;

    time = gettime() - philo->data->start_time;
    // if philo full return
    // check that no philo died before -> can put this in the if OCEANO

    // lock the writing mutex that they all share
    if (debug)
        write_status_debug(status, philo, time);
    else
    {
        safe_mutex(mutex, LOCK);
        if((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK) && !is_simulation_finished(philo->data))
            printf("%-6ld %d has taken a fork\n", time, philo->id);
        else if (status == EATING  && !is_simulation_finished(philo->data))
            printf("%-6ld %d is eating\n", time, philo->id);
        else if (status == SLEEPING  && !is_simulation_finished(philo->data))
            printf("%-6ld %d is sleeping\n", time, philo->id);
        else if (status == THINKING  && !is_simulation_finished(philo->data))
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

