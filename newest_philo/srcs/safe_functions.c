#include "philo_new.h"

void    *safe_malloc(size_t bytes, t_data *data)
{
    void    *ret;

    ret = malloc(bytes);
    if (ret == NULL)
        err_exit("Malloc failed");
    add_to_free_list(data, ret);
    return (ret);
}

void	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		mutex_err_handler(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		mutex_err_handler(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		mutex_err_handler(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		mutex_err_handler(pthread_mutex_destroy(mutex), opcode);
	else
		err_exit("Wrong opcode for safe_mutex().");
}

void safe_thread(pthread_t *thread, void *(*foo)(void *), void *args, t_opcode opcode)
{
    if (opcode == CREATE)
        thread_err_handler(pthread_create(thread, NULL, foo, args), opcode);
    else if (opcode == JOIN)
        thread_err_handler(pthread_join(*thread, NULL), opcode);
    else
        err_exit("Wrong opcode for safe_thread().");
}
