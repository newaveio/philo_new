#include "philo.h"

static void create_handler(int status)
{
    if (status == EAGAIN)
        err_exit("Insufficient resources to create another thread.");
    else if (status == EINVAL)
        err_exit("Invalid settings in attr.");
    else if (status == EPERM)
        err_exit("No permission to set the scheduling policy and parameters specified in attr.");
}

static void join_handler(int status)
{
    if (status == EDEADLK)
        err_exit("A deadlock was detected (e.g., two threads tried to join with each other); or  thread  specifies  the\
              calling thread.");
    else if (status == EINVAL)
        err_exit("Thread is not a joinable thread.");
    else if (status == ESRCH)
        err_exit("No thread with the ID thread could be found.");
}

static void detach_handler(int status)
{
    if (status == EINVAL)
        err_exit("Thread is not a joinable thread.");
    else if (status == ESRCH)
        err_exit("No thread with the ID thread could be found.");
}

void    thread_err_handler(int status, t_opcode opcode)
{
    if (status == 0)
        return; // EVERYTHING GOOD
    if (opcode == CREATE)
        create_handler(status);
    else if (opcode == JOIN)
        join_handler(status);
    else if (opcode == DETACH)
        detach_handler(status);
}
