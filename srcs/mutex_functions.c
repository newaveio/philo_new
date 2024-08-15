#include "philo.h"

static void lock_handler(int status)
{
	if (status == EAGAIN)
		err_exit("The  mutex  could  not be acquired because the maximum number of \
              recursive locks for mutex has been exceeded.");
	else if (status == EINVAL)
		err_exit("The mutex was created with the  protocol  attribute  having  the \
              value  PTHREAD_PRIO_PROTECT and the calling thread's priority is \
              higher than the mutex's current priority ceiling.");
	else if (status == ENOTRECOVERABLE)
		err_exit("The state protected by the mutex is not recoverable.");
	else if (status == EOWNERDEAD)
		err_exit("The mutex is a robust mutex and the process containing the  pre‐ \
              vious owning thread terminated while holding the mutex lock. The \
              mutex lock shall be acquired by the calling thread and it is  up \
              to the new owner to make the state consistent.");
	else if (status == EDEADLK)
		err_exit("The  mutex  type  is  PTHREAD_MUTEX_ERRORCHECK  and  the current \
              thread already owns the mutex.");
}

static void unlock_handler(int status)
{
	if (status == EPERM)
		err_exit("The  mutex  type is PTHREAD_MUTEX_ERRORCHECK or PTHREAD_MUTEX_RECURSIVE,\
			or the mutex is a robust mutex, and the current thread does not own the mutex.");
}

static void init_handler(int status)
{
	if (status == EAGAIN)
		err_exit("The system lacked the necessary resources (other than memory) to initialize another mutex.");
	else if (status == ENOMEM)
		err_exit("Insufficient memory exists to initialize the mutex.");
	else if (status == EPERM)
		err_exit("The caller does not have the privilege to perform the operation.");
	else if (status == EINVAL)
		err_exit("The attributes object referenced by attr has the robust mutex  attribute  set  without  the  process- \
              shared attribute being set.");
}

static void destroy_handler(int status)
{
	if (status == EBUSY)
		err_exit("The implementation has detected an attempt to destroy the object referenced by mutex while it is locked or referenced (for example,\
			while being used in a pthread_cond_timedwait() or pthread_cond_wait()) by another thread.");
    else if (status == EINVAL)
        err_exit("The value specified by mutex is invalid.");
}

void	mutex_err_handler(int status, t_opcode opcode)
{
	if (status == 0)
		return ; // EVERYTHING GOOD
	if (opcode == LOCK)
		lock_handler(status);
	else if (opcode == UNLOCK)
		unlock_handler(status);
	else if (opcode == INIT)
		init_handler(status);
	else if (opcode == DESTROY)
		destroy_handler(status);
}
