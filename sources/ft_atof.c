/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:46 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 19:01:16 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static double	ft_atof_util(char *str, int sign, int *status);
static int		get_dot_idx(char *str);
static int		is_double(char *str, int *sign);
static int		_is_double(char *str, int str_len);

double	ft_atof_stat(const char *str, int *status)
{
	double	ret;
	int		sign;

	ret = 0;
	while (ft_ctype(*str) == 3)
		str++;
	if (!is_double((char *)str, &sign))
	{
		*status = 0;
		return (0);
	}
	ret = ft_atof_util((char *)str, sign, status);
	return (ret);
}

static double	ft_atof_util(char *str, int sign, int *status)
{
	double	ret;
	double	tmp;
	int		dot_idx;
	int		strlen;

	strlen = ft_strlen(str);
	dot_idx = get_dot_idx(str);
	if (dot_idx > 0)
		str[strlen - dot_idx - 1] = 0;
	ret = (double) ft_atoi_stat(str, status);
	if (dot_idx > 5)
	{
		str[strlen - dot_idx + PRECISION] = 0;
		dot_idx = 5;
	}
	tmp = (double) ft_atoi(str + strlen - dot_idx);
	while (dot_idx-- > 0)
		tmp /= 10;
	if (sign < 0)
		ret -= tmp;
	else
		ret += tmp;
	return (ret);
}

static int	is_double(char *str, int *sign)
{
	int	str_len;

	str_len = ft_strlen(str);
	if (ft_ctype(*str) == 1 || ft_ctype(*str) == -1)
	{
		str++;
		str_len--;
		*sign = -1;
	}
	return (_is_double(str, str_len));
}

static int	_is_double(char *str, int str_len)
{
	int	dot_flag;
	int	idx;

	dot_flag = 0;
	idx = 0;
	while (idx < str_len)
	{
		if (str[idx] == '.' && dot_flag == 0)
		{
			if (idx == 0)
				return (0);
			dot_flag++;
		}
		else if (str[idx] == '.' && dot_flag > 0)
			return (0);
		if (str[idx] != '.' && (str[idx] < '0' || str[idx] > '9'))
			return (0);
		idx++;
	}
	return (1);
}

static int	get_dot_idx(char *str)
{
	int	len;
	int	ret;

	len = ft_strlen(str);
	str = str + len - 1;
	ret = 0;
	while (len-- > 0)
	{
		if (*str == '.')
			return (ret);
		str--;
		ret++;
	}
	return (0);
}
