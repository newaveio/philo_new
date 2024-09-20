/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbest <mbest@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 16:12:15 by mbest             #+#    #+#             */
/*   Updated: 2024/09/20 16:13:23 by mbest            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (!ret)
	{
		exit(0);
	}
	return (ret);
}

static void	mutex_err_handler(int status)
{
	if (status == 0)
		return ;
	else
		err_exit("Problem occured with the mutex functions");
}

void	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		mutex_err_handler(pthread_mutex_lock(mutex));
	else if (opcode == UNLOCK)
		mutex_err_handler(pthread_mutex_unlock(mutex));
	else if (opcode == INIT)
		mutex_err_handler(pthread_mutex_init(mutex, NULL));
	else if (opcode == DESTROY)
		mutex_err_handler(pthread_mutex_destroy(mutex));
	else
		err_exit("Wrong op-code for the mutex functions");
}

static void	thread_err_handler(int status)
{
	if (status == 0)
		return ;
	else
		err_exit("Problem occured with the thread functions");
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *), void *args,
		t_opcode opcode)
{
	if (opcode == CREATE)
		thread_err_handler(pthread_create(thread, NULL, foo, args));
	else if (opcode == JOIN)
		thread_err_handler(pthread_join(*thread, NULL));
	else
		err_exit("Wrong op-code for the thread functions");
}
