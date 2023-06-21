#include "utils.h"

static int	get_dot_idx(const char *str);
static int	is_double(char *str);

double	ft_atof_stat(const char *str, int *status)
{
	double	ret;
	int		dot_idx;
	int		tmp;
	int		sign;

	tmp = 0;
	sign = 1;
	while (ft_ctype(*str) == 3)
		str++;
	if (ft_ctype(*str) == 1 || ft_ctype(*str) == -1)
		sign *= ft_ctype(*str++);
	if (!is_double((char *)str))
	{
		*status = 0;
		return (0);
	}
	dot_idx = get_dot_idx(str);
	ret = (double) ft_atoi(str);
	while (tmp++ < dot_idx)
		ret *= 10.0;
	ret += (double) ft_atoi(str + ft_strlen((char *)str) - dot_idx);
	while (dot_idx-- > 0)
		ret /= 10;
	return (sign * ret);
}

static int	is_double(char *str)
{
	int	str_len;
	int	dot_flag;
	int	idx;

	idx = 0;
	dot_flag = 0;
	str_len = ft_strlen(str);
	while (idx < str_len)
	{
		if (str[idx] == '.' && dot_flag == 0)
			dot_flag++;
		else if (str[idx] == '.' && dot_flag > 0)
			return (0);
		if (str[idx] != '.' && (str[idx] < '0' || str[idx] > '9'))
			return (0);
		idx++;
	}
	return (1);
}

static int	get_dot_idx(const char *str)
{
	int	len;
	int	ret;

	len = ft_strlen((char *)str);
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
