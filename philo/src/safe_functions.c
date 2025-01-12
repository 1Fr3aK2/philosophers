#include "philosophers.h"

static void	handle_mutex(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == INIT || code == LOCK || code == UNLOCK || code == DESTROY))
		return (exit_msg("Invalid mutex or operation on an uninitialized mutex."));
	if (status == EDEADLK)
		return (exit_msg("Deadlock condition detected."));
	if (status == EPERM)
		return (exit_msg("Thread does not own the mutex or lacks permission."));
	if (status == ENOMEM)
		return (exit_msg("Not enough memory available to create/initialize the mutex."));
	if (status == EBUSY)
		return (exit_msg("The mutex is already locked."));
}

void	mutex_handle(t_mutex *mutex, t_code code)
{
	if (!mutex)
		return (exit_msg("Invalid mutex pointer."));
	if (code == LOCK)
		handle_mutex(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_mutex(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		handle_mutex(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		handle_mutex(pthread_mutex_destroy(mutex), code);
	else
		return (exit_msg("Invalid mutex operation code."));
}

static void	handle_thread(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EDEADLK)
		return (exit_msg("Deadlock condition detected."));
	if (status == EINVAL && code == CREATE)
		return (exit_msg("Invalid attributes specified for thread creation."));
	if (status == EINVAL && (code == JOIN || code == DETACH))
		return (exit_msg("Thread not joinable or invalid operation."));
	if (status == EPERM)
		return (exit_msg("Caller lacks permissions."));
	if (status == EAGAIN)
		return (exit_msg("Insufficient resources to create another thread."));
	if (status == ESRCH)
		return (exit_msg("Thread not found with the given thread ID."));
}

void	thread_handle(pthread_t *thread, void *(*f)(void *), void *data, t_code code)
{
	if (!thread)
		return (exit_msg("Invalid thread pointer."));
	if (code == CREATE)
		handle_thread(pthread_create(thread, NULL, f, data), code);
	else if (code == JOIN)
		handle_thread(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		handle_thread(pthread_detach(*thread), code);
	else
		return (exit_msg("Invalid thread operation code."));
}
