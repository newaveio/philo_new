#include "philo_new.h"

void    exit_cleanly(t_data *data)
{
    ft_lstclear(&(data->free_list), free);
    data->free_list = NULL;
}

void    add_to_free_list(t_data *data, void *ptr)
{
    t_list *new;

    new = ft_lstnew(ptr);
    if (!new)
    {
        free(ptr);
        exit_cleanly(data);
    }
    ft_lstadd_back(&(data->free_list), new);
}

