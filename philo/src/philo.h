#ifndef PHILO_H
# define PHILO_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mtx;
typedef struct s_table	t_table;

typedef enum s_time
{
	SECONDS,
	MILISECONDES,
	MIRCOSECONDS,
}						t_time;

typedef enum s_status
{
	EATING,
	SLEEPING,
	THINKING,
	DIED,
	FIRST_FORK,
	SECOND_FORK,
}						t_status;

typedef enum s_code
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}						t_code;

typedef struct s_fork
{
	t_mtx				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philo
{
	int					id;
	long				meals_counter;
	bool				full;
	long				last_meal_time;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mtx				philo_mutex;
	t_table				*table;

}						t_philo;

typedef struct s_table
{
	long				philo_nbr;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				nbr_limits_meals;
	long				start_simulation;
	bool				end_simulation;
	bool				all_threads_ready;
	t_mtx				write_mutex;
	t_mtx				table_mutex;
	t_fork				*forks;
	t_philo				*philos;
}						t_table;

// utils
void					error_exit(const char *error);
bool					is_space(char c);
bool					is_digit(char c);
bool					check_inputs(char *argv[]);
char					*check_input(const char *str);
bool					parse(t_table *table, char **argv);
void					safe_thread_handle(pthread_t *thread,
							void *(*f)(void *), void *data, t_code code);
void					safe_mutex_handle(t_mtx *mutex, t_code code);
void					data_init(t_table *table);
void					*dinner_simulation(void *data);

void					set_bool(t_mtx *mutex, bool *dest, bool value);
bool					get_bool(t_mtx *mutex, bool *value);
long					get_long(t_mtx *mutex, long *value);
void					set_long(t_mtx *mutex, long *dest, long value);
bool					simulation_finish(t_table *table);
void					wait_all_threads(t_table *table);
long					gettime(t_time time);
void					my_usleep(long usec, t_table *table);
void					write_status(t_status status, t_philo *philo);
void					dinner_start(t_table *table);

#endif
