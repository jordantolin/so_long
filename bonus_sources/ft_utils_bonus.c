#include "../include/so_long_bonus.h"

char *ft_strappend(char **s1, const char *s2)
{
    char *temp;

    temp = ft_strjoin(*s1, s2);
    free(*s1);
    *s1 = temp;
    return (*s1);
}
