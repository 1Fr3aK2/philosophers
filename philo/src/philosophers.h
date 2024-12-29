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
}						t_code;

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
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread_id;
	t_table				*table;
}						t_philos;

struct					s_table
{
	long				number;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_simulation;
	bool				end_simulation;
	t_philos			*philos;
	t_fork				*forks;
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

// safe_funtions
void					mutex_handle(t_mutex *mutex, t_code code);

#endif