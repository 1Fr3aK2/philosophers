#include "../includes/philo.h"

static void	handle_mutex_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (code == INIT || code == LOCK || code == UNLOCK
			|| code == DESTROY))
		return (error_exit
			("Invalid mutex or operation on an uninitialized mutex."));
	if (status == EDEADLK)
		return (error_exit("Deadlock condition detected."));
	if (status == EPERM)
		return (error_exit
			("Thread does not own the mutex or lacks permission."));
	if (status == ENOMEM)
		return (error_exit
			("Not enough memory available to create/initialize the mutex."));
	if (status == EBUSY)
		return (error_exit("The mutex is already locked."));
}

void	safe_mutex_handle(t_mtx *mutex, t_code code)
{
	if (!mutex)
		return (error_exit("Invalid mutex pointer."));
	if (code == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), code);
	else if (code == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), code);
	else if (code == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), code);
	else if (code == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), code);
	else
		return (error_exit("Invalid mutex operation code."));
}

static void	handle_thread_error(int status, t_code code)
{
	if (status == 0)
		return ;
	if (status == EDEADLK)
		return (error_exit("Deadlock condition detected."));
	if (status == EINVAL && code == CREATE)
		return (error_exit
			("Invalid attributes specified for thread creation."));
	if (status == EINVAL && (code == JOIN || code == DETACH))
		return (error_exit("Thread not joinable or invalid operation."));
	if (status == EPERM)
		return (error_exit("Caller lacks permissions."));
	if (status == EAGAIN)
		return (error_exit("Insufficient resources to create another thread."));
	if (status == ESRCH)
		return (error_exit("Thread not found with the given thread ID."));
}

void	safe_thread_handle(pthread_t *thread, void *(*f)(void *), void *data,
		t_code code)
{
	if (!thread)
		return (error_exit("Invalid thread pointer."));
	if (code == CREATE)
		handle_thread_error(pthread_create(thread, NULL, f, data), code);
	else if (code == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), code);
	else if (code == DETACH)
		handle_thread_error(pthread_detach(*thread), code);
	else
		return (error_exit("Invalid thread operation code."));
}
