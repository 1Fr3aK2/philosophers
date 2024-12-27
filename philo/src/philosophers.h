#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
}			t_philo;

typedef struct s_info
{
	long	number;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;

}			t_info;

typedef struct s_table
{
	t_philo *philo;
	t_info *info;
}			t_table;


//init_data
void struct_init(t_table *table);

//parse
void parse(t_table *table, char *argv[]);

//utils
void exit_msg(char *str);
bool is_space(char c);
bool is_digit(char c);



#endif