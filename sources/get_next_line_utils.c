/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <saseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 18:53:44 by saseo             #+#    #+#             */
/*   Updated: 2022/11/29 21:47:05 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_lst	*lstnew(t_lst **head, int fd, int is_head)
{
	t_lst	*node;
	t_lst	*tmp;

	node = (t_lst *) malloc(sizeof (t_lst));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->next = NULL;
	node->backup = NULL;
	if (is_head)
		return (node);
	node->backup = (char *) malloc(sizeof (char));
	if (!node->backup)
	{
		free(node);
		return (NULL);
	}
	*(node->backup) = 0;
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
	return (node);
}

t_lst	*lst_fd(t_lst **head, int fd)
{
	t_lst	*tmp;

	if (!head)
		return (NULL);
	tmp = (*head)->next;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = lstnew(head, fd, 0);
	if (tmp && (fd < 0 || (read(fd, NULL, 0) == -1)))
	{
		lst_delete(head, tmp);
		tmp = NULL;
	}
	return (tmp);
}

void	lst_delete(t_lst **head, t_lst *node)
{
	t_lst	*prev;
	t_lst	*tmp;
	int		size;

	tmp = *head;
	size = 0;
	while (tmp->next)
	{
		if (tmp->next == node)
			prev = tmp;
		tmp = tmp->next;
		size++;
	}
	prev->next = node->next;
	free(node->backup);
	free(node);
	if (size == 1)
	{
		free(*head);
		*head = NULL;
	}
}

char	*ft_strchr(const char *s)
{
	while (*s)
	{
		if (*s == '\n')
			return ((char *) s);
		s++;
	}
	return (NULL);
}

size_t	strlen(const char *s)
{
	int	cnt;

	cnt = 0;
	if (!s)
		return (0);
	while (*s)
	{
		cnt++;
		s++;
	}
	return (cnt);
}
