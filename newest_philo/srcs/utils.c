#include "philo_new.h"

void    err_exit(char *msg)
{
    printf(RED"%s\n"RST, msg);
    exit(EXIT_FAILURE);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size && nmemb > INT_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}

long gettime(void)
{
    struct timeval tv;

    if (gettimeofday(&tv, NULL) != 0)
        err_exit("gettimeofday() failed.");
    return (tv.tv_sec * 1000 + (tv.tv_usec / 1000));
}

void ft_usleep(long milli_sec)
{
    long start_time;

    start_time = gettime();
    while ((gettime() - start_time) < milli_sec)
    {
        usleep(100);
    }
}
