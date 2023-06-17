#include "miniRT.h"

int	ft_strlen(char *str)
{
	int	ret;

	ret = 0;
	if (!str)
		return (0);
	while (*str++)
		ret++;
	return (ret);
}
