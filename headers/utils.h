/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:12 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 15:51:47 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "vector.h"

int			ft_atoi_stat(char *str, int *stat);
double		ft_atof_stat(const char *str, int *status);
t_vector	ft_atovec_stat(char *str, int *status);
int			ft_atoi(const char *str);
int			ft_ctype(char c);

char		**ft_split(char *str, char *charset);
void		free_split(char **split);
int			ft_strlen(char *str);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
int			len_max(char *str1, char *str2);
void		*ft_memset(void *b, int c, size_t len);
int			split_len(char **split);
size_t		ft_strlcpy(char *dest, const char *src, size_t dstsize);
void		ft_strncpy(char *dest, char *src, int size);
char		*ft_itoa(int n);

int			check_color_range(t_vector *color);
int			check_norm_range(t_vector *norm);

void		error_print(char *msg);
int			check_file_expand(char *path, char *expand);
int			is_white_line(char *line);
char		*get_whitespaces(char *charset);
int			comma_number(char *str);
int			rt_file_check(char *path);
void		rstrip(char *str);
int			check_contents_flags(int *flags, int len, int *err_line);

#endif
