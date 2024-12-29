#include "philosophers.h"

static void	handle_return(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL)
	{
		if (code == INIT || code == LOCK || code == UNLOCK || code == DESTROY)
			return (exit_msg("The mutex was created with the protocol attribute"
					"having the value PTHREAD_PRIO_PROTECT and the calling "
					"thread's priority is higher than the mutex's current priority ceiling."));
	}
	if (status == EDEADLK)
		return (exit_msg("A deadlock condition was detected."));
	if (status == EPERM)
		return (exit_msg("The mutex type is PTHREAD_MUTEX_ERRORCHECK or PTHREAD_MUTEX_RECURSIVE,"
				"or the mutex is a robust mutex,"
				"and the current thread does not own the mutex."));
	if (status == ENOMEM)
		return (exit_msg("Not enough memory available to create or initialize the mutex."));
	if (status == EBUSY)
		return (exit_msg("The mutex could not be acquired because it was already locked."));
}

void	mutex_handle(t_mutex *mutex, t_code code)
{
	if (code == LOCK)
		handle_return(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_return(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		handle_return(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		handle_return(pthread_mutex_destroy(mutex), code);
	else
		return (exit_msg("Invalid code!!\n"));
}
