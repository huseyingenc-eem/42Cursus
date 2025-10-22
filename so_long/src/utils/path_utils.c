#include "../../include/utils.h"

bool	has_ber_extension(const char *path)
{
    size_t	path_length;

    if (!path)
        return (false);
    path_length = ft_strlen(path);
    if (path_length < 4)
        return (false);
    return (ft_strncmp(&path[path_length - 4], ".ber", 4) == 0);
}