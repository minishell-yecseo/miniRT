/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:47 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 15:02:47 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int			ft_ctype(char c);
static void	ft_atoi_util(int sign, char *str, int *res, int *stat);
static int	is_number(char *str);

int	ft_atoi(const char *str)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (ft_ctype(*str) == 3)
		str++;
	if (ft_ctype(*str) == 1 || ft_ctype(*str) == -1)
		sign *= ft_ctype(*str++);
	while (*str)
	{
		if (ft_ctype(*str) == 2)
			res = res * 10 + (*str - '0');
		else
			return (sign * res);
		str++;
	}
	return (sign * res);
}

int	ft_atoi_stat(char *str, int *stat)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (ft_ctype(*str) == 3)
		str++;
	if (ft_ctype(*str) == -1 || ft_ctype(*str) == 1)
		sign *= ft_ctype(*str++);
	ft_atoi_util(sign, str, &res, stat);
	return (res);
}

static void	ft_atoi_util(int sign, char *str, int *res, int *stat)
{
	uint64_t	tmp;

	tmp = 0;
	if (!is_number(str))
	{
		*stat = 0;
		return ;
	}
	while (*str)
	{
		if (ft_ctype(*str) == 2)
			tmp = tmp * 10 + (*str - '0');
		else
		{
			*stat = 0;
			return ;
		}
		str++;
	}
	if ((sign && tmp > UINT_MAX) || (sign < 0 && (tmp - 1 > UINT_MAX)))
	{
		*stat = 0;
		return ;
	}
	*res = sign * (int) tmp;
}

static int	is_number(char *str)
{
	int	len;
	int	idx;
	int	tmp;

	len = ft_strlen(str);
	idx = 0;
	tmp = 1;
	if (len <= 0)
		return (0);
	while (ft_ctype(str[len - tmp]) == 3)
		tmp++;
	while (idx < len - tmp + 1)
	{
		if (ft_ctype(str[idx++]) != 2)
			return (0);
	}
	return (1);
}

int	ft_ctype(char c)
{
	if (c == '-')
		return (-1);
	else if (c == '+')
		return (1);
	else if (c >= '0' && c <= '9')
		return (2);
	else if (c == ' ' || (c > 8 && c < 14))
		return (3);
	else
		return (0);
}
