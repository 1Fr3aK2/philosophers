#include "philosophers.h"

void exit_msg(char *str)
{
    if(!str)
        printf("Leaving, no msg passed\n");
    else
        printf("%s\n", str); 
}

bool is_space(char c)
{
    return ((c >= 9 && c <= 13 || c == 32));
}

bool is_digit(char c)
{
    return (c >= 48 && c <= 57);
}

bool check_input(const char *str)
{
    if (!str)
        return (NULL);
    while(is_space(*str))
        str++;
    if (*str == '+')
        str++;
    if (*str == '-')
        return (exit_msg("Only positive values can be acepted\n"), false);
    if (!is_digit(*str))
        return (exit_msg("only digits can be acepted\n"), false);
    while(*str)
    {
        if (!is_digit(*str))
            return (exit_msg("Invalid input\n"), false);
        str++;
    }
    return (true);
}

static long ft_atol(const char *str)
{
    /* long nb; */

    if (!str)
        return (-1);
    if (check_input(str) != 1)
        return (-1);
    printf("%s", str);
}

int main()
{
    char *str = "          0123456";
    long nb = ft_atol(str);
}
