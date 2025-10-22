#include "../../include/utils.h"
#include <stdlib.h>

void	error_exit(const char *msg)
{
    ft_printf("Error : ");
    if (msg)
        ft_printf("%s\n", msg);
    exit(1);
}