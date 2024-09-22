/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:12:15 by mbest             #+#    #+#             */
/*   Updated: 2024/09/22 14:50:12 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	mutex_err_handler(int status)
{
	if (status == 0)
		return (0);
	else
	{
		err_exit("Problem occured with the mutex functions");
		return (1);
	}
}

int	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		return (mutex_err_handler(pthread_mutex_lock(mutex)));
	else if (opcode == UNLOCK)
		return (mutex_err_handler(pthread_mutex_unlock(mutex)));
	else if (opcode == INIT)
		return (mutex_err_handler(pthread_mutex_init(mutex, NULL)));
	else if (opcode == DESTROY)
		return (mutex_err_handler(pthread_mutex_destroy(mutex)));
	else
		return (err_exit("Wrong op-code for the mutex functions"), 1);
}

static int	thread_err_handler(int status)
{
	if (status == 0)
		return (0);
	else
	{
		err_exit("Problem occured with the thread functions");
		return (1);
	}
}

int	safe_thread(pthread_t *thread, void *(*foo)(void *), void *args,
		t_opcode opcode)
{
	if (opcode == CREATE)
		return (thread_err_handler(pthread_create(thread, NULL, foo, args)));
	else if (opcode == JOIN)
		return (thread_err_handler(pthread_join(*thread, NULL)));
	else
		return (err_exit("Wrong op-code for the thread functions"), 1);
}
