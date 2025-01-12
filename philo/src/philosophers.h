#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef pthread_mutex_t	t_mutex;
typedef struct s_table	t_table;

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

typedef struct s_fork
{
	t_mutex				fork;
	int					fork_id;
}						t_fork;

typedef struct s_philos
{
	int					id;
	int					meals_counter;
	long				last_meal_time;
	bool				full;
	t_fork				*first_fork;
	t_fork				*second_fork;
	pthread_t			thread_id;
	t_mutex				philo_mutex;
	t_table				*table;
}						t_philos;

struct					s_table
{
	long				number;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long start_simulation; // tempo
	bool end_simulation;   // philo dies or all philos are full
	bool ready;            // syncro philos
	t_mutex table_mutex;   // avoid race from reading the table
	t_mutex				write_mutex;
	t_philos *philos; // array de threads
	t_fork *forks;    // array the mtx
};

// init_data
void					struct_init(t_table *table);

// parse
bool					parse(t_table *table, char *argv[]);
char					*check_input(const char *str);

// utils
void					exit_msg(char *str);
bool					is_space(char c);
bool					is_digit(char c);
bool					check_inputs(char *argv[]);
long					gettime(t_time time);
void					my_usleep(long usec, t_table *table);

// safe_funtions
void					mutex_handle(t_mutex *mutex, t_code code);
void					thread_handle(pthread_t *thread, void *(*f)(void *),
							void *data, t_code code);

// getter_setters
void					set_bool(t_mutex *mutex, bool *dest, bool value);
bool					get_bool(t_mutex *mutex, bool *value);
long					get_long(t_mutex *mutex, long *value);
void					set_long(t_mutex *mutex, long *dest, long value);
bool					simulation_finish(t_table *table);

// synchro_utils
void					wait_threads(t_table *table);

//write
void	write_status(t_status status, t_philos *philo);

//dinner
void	dinner_start(t_table *table);

#endif