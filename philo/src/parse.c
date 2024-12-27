#include "philosophers.h"


/* void parse(t_table *table, char *argv[])
{
    table->info->number = ft_atol(argv[1]);
    table->info->time_to_die = ft_atol(argv[2]);
    table->info->time_to_eat = ft_atol(argv[3]);
    table->info->time_to_sleep = ft_atol(argv[4]);
} */


char    *check_input(const char *str)
{
    if (!str)
        return (false);
    while(is_space(*str))
        str++;
    if (*str == '+')
        str++;
    if (*str == '-')
        return (exit_msg("Only positive values can be acepted\n"));
    if (!is_digit(*str))
        return (exit_msg("only digits can be acepted\n"));
    while(*str)
    {
        if (!is_digit(str))
            return (exit_msg("Invalid input\n"));
        str++;
    }
}

static long ft_atol(const char *str)
{
    /* long nb; */

    if (!str)
        return (-1);
    str = check_input(str);
    printf("%s", str);
}

int main()
{
    char *str = "0123456";
    long nb = ft_atol(str);
    printf("%ld", nb);
}


/* bool is_space(char c)
{
    return ((c >= 9 && c <= 13 || c == 32));
} */