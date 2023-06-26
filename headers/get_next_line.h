/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:53:55 by saseo             #+#    #+#             */
/*   Updated: 2023/06/26 15:02:04 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_lst {
	int				fd;
	char			*backup;
	struct s_lst	*next;
}				t_lst;

char	*get_next_line(int fd);
char	*read_line(t_lst **head, t_lst *node, char *buffer);
char	*ft_strjoin(char *backup, char *buffer);
void	*memmove(void *dst, const void *src, size_t len);
char	*substr(ssize_t read_byte, char *backup, size_t len);

t_lst	*lstnew(t_lst **head, int fd, int is_head);
t_lst	*lst_fd(t_lst **head, int fd);
void	lst_delete(t_lst **head, t_lst *node);
char	*ft_strchr(const char *s);
size_t	strlen(const char *s);

#endif
