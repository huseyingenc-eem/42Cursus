#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h> // malloc ve free için
# include <unistd.h> // read için

// BUFFER_SIZE tanımlı değilse, varsayılan bir değer ata
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line_bonus(int fd);

// get_next_line_utils_bonus.c'deki yardımcı fonksiyonlar
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif