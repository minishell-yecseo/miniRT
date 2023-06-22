#include "utils.h"

static int	get_size(int n);

char	*ft_itoa(int n)
{
	char			*ret;
	char			*tmp;
	unsigned int	positive_n;
	int				size;

	size = get_size(n);
	ret = (char *) malloc(sizeof (char) * (size + 1));
	if (!ret)
		return (0);
	tmp = ret + size;
	if (n < 0)
	{
		ret[0] = '-';
		positive_n = n * (-1);
	}
	else
		positive_n = n;
	*tmp-- = 0;
	while (positive_n / 10)
	{
		*tmp-- = positive_n % 10 + '0';
		positive_n /= 10;
	}
	*tmp = positive_n % 10 + '0';
	return (ret);
}

static int	get_size(int n)
{
	int	size;

	size = 0;
	if (n < 0)
	{
		size++;
		n *= -1;
	}
	else if (n == 0)
		return (1);
	while (n)
	{
		size++;
		n /= 10;
	}
	return (size);
}

int	rt_file_check(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		error_print("Error\nOpen file error\n");
		return (-1);
	}
	if (!check_file_expand(path, ".rt"))
	{
		error_print("Error\nInput file expand must be .rt\n");
		close(fd);
		return (-1);
	}
	return (fd);
}

void	rstrip(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (str[len - 1] == '\n')
		str[len - 1] = '\0';
}

int	check_contents_flags(int *flags, int len, int *err_line)
{
	int	idx;

	idx = 0;
	while (idx < len)
	{
		if (flags[idx++] != 1)
			return (0);
	}
	return (1);
}
