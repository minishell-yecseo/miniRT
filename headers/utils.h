#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include "vector.h"

int			ft_atoi_stat(char *str, int *stat);
double		ft_atof_stat(const char *str, int *status);
t_vector	ft_atovec_stat(char *str, int *status);
int			ft_atoi(const char *str);
int         ft_ctype(char c);

char		**ft_split(char const *s, char c);
void		free_split(char **split);
int			ft_strlen(char *str);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			len_max(char *str1, char *str2);
void		*ft_memset(void *b, int c, size_t len);
int			split_len(char **split);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);

#endif
