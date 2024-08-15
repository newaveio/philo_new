#include "philo.h"

static inline int	is_digit(char c)
{
	if (c >= 49 && c <= 57)
		return (1);
	else
		return (0);
}

static int	is_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

// check for negative
// cheef if number and not letters etc 
// check if > INT MAX by checking the length first
// Then check if it is not greater then INT MAX
static char	*valid_input(char *str)
{
	int		i;
	int		len;
	char	*number;

	i = 0;
	len = 0;
	while (is_space(str[i]))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
		err_exit("Only positive values are accepted");
	if (!is_digit(str[i]))
		err_exit("The input must be a correct digit (0-9)");
	number = &str[i];
	while (is_digit(str[i]))
	{
		i++;
		len++;
	}
	if (len > 10)
		err_exit("The value provided is too big. INT_MAX is the limit");
	return (number);
}

static long	ft_atol(char *str)
{
	int		i;
	long	num;

	i = 0;
	num = 0;
	str = valid_input(str);
	while (is_digit(str[i]))
	{
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	if (num > INT_MAX)
		err_exit("The value provided is too big. INT_MAX is the limit");
	return (num);
}

void	parsing(t_data *data, char **av)
{
	data->philo_num = ft_atol(av[1]);
    data->time_to_die = ft_atol(av[2]) * 1e3;
	data->time_to_eat = ft_atol(av[3]) * 1e3;
	data->time_to_sleep = ft_atol(av[4]) * 1e3;
	if (av[5])
		data->num_meals_limit = ft_atol(av[5]);
	else
		data->num_meals_limit = -1;
}
