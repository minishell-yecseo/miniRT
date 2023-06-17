/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <saseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:53:27 by saseo             #+#    #+#             */
/*   Updated: 2022/11/29 21:57:22 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*ret;
	char			*buffer;
	static t_lst	*head;
	t_lst			*cur;

	if (!head)
		head = lstnew(&head, -1, 1);
	cur = lst_fd(&head, fd);
	if (!cur)
		return (NULL);
	buffer = (char *) malloc(sizeof (char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	*buffer = '\0';
	ret = read_line(&head, cur, buffer);
	free(buffer);
	return (ret);
}

char	*read_line(t_lst **head, t_lst *node, char *buffer)
{
	char	*line;
	char	*lf;
	ssize_t	read_byte;

	lf = ft_strchr((const char *) node->backup);
	read_byte = 1;
	while (!lf)
	{
		read_byte = read(node->fd, buffer, BUFFER_SIZE);
		if (read_byte <= 0)
			break ;
		buffer[read_byte] = '\0';
		node->backup = ft_strjoin(node->backup, buffer);
		if (!node->backup)
			return (NULL);
		lf = ft_strchr((const char *) node->backup);
	}
	line = substr(read_byte, node->backup, \
									strlen(node->backup) - strlen(lf) + 1);
	if (read_byte <= 0)
		lst_delete(head, node);
	if (lf)
		node->backup = memmove(node->backup, (lf + 1), strlen(lf + 1) + 1);
	return (line);
}

char	*substr(ssize_t read_byte, char *backup, size_t len)
{
	char	*ret;

	if (!*backup || (read_byte < 0))
		return (NULL);
	ret = (char *) malloc(sizeof (char) * (len + 1));
	if (!ret)
		return (NULL);
	memmove(ret, backup, len);
	*(ret + len) = '\0';
	return (ret);
}

char	*ft_strjoin(char *backup, char *buffer)
{
	char	*ret;
	int		backup_len;
	int		buffer_len;

	backup_len = strlen(backup);
	buffer_len = strlen(buffer);
	ret = (char *) malloc(sizeof (char) * (backup_len + buffer_len + 1));
	if (!ret)
	{
		free(backup);
		return (NULL);
	}
	memmove(ret, backup, backup_len + 1);
	memmove((ret + backup_len), buffer, buffer_len + 1);
	free(backup);
	return (ret);
}

void	*memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*_dst;
	unsigned char	*_src;
	void			*res;

	if (!dst)
		return (NULL);
	_dst = (unsigned char *) dst;
	_src = (unsigned char *) src;
	res = (void *) _dst;
	if (!len || !src)
		return (res);
	if (_src < _dst)
	{
		while (len)
		{
			*(_dst + len - 1) = *(_src + len - 1);
			len--;
		}
	}
	else
	{
		while (len--)
			*_dst++ = *_src++;
	}
	return (res);
}
