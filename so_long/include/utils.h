#ifndef UTILS_H
# define UTILS_H

#include <stddef.h>

# define TRUE 1
# define FALSE 0
# define BUFFER_SIZE 4096

/* ------------- String Utils ------------- */
size_t	ft_strlen(const char *str);
int		ft_strncmp(const char *str1, const char *str2, size_t n);

/* ------------- Memory Utils ------------- */
void	*ft_memset(void *b, int c, size_t len);

/* ------------- File Utils --------------- */
char	*read_file(const char *path);
char	**split_lines(char *text, size_t *line_count);

/* ------------- Path Utils --------------- */
int		has_ber_extension(const char *path);

/* ------------- Error Exit --------------- */
void	error_exit(const char *message);

/* ------------- Printf Utils ------------- */
int		ft_printf(const char *format, ...);

#endif