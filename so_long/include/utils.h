#ifndef UTILS_H
# define UTILS_H

# include <stddef.h>
# include <stdbool.h>
# include <stdarg.h>

/* ------------- String Utils ------------- */
size_t  ft_strlen(const char *str);
int     ft_strncmp(const char *str1, const char *str2, size_t n);

/* ------------- File Utils --------------- */
char    *read_file(const char *path);
char    **split_lines(char *text, size_t *line_count);

/* ------------- Path Utils --------------- */
bool    has_ber_extension(const char *path);

/* ------------- Error Exit --------------- */
void    error_exit(const char *message);

/* ------------- Printf Utils ------------- */
int     ft_printf(const char *format, ...);

#endif /* UTILS_H */