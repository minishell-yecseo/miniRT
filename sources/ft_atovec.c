#include "utils.h"

static int	atovec_util(char **split, t_vector *ret);

t_vector	ft_atovec_stat(char *str, int *status)
{
	t_vector	ret;
	char		**split;

	ret = vector(0, 0, 0);
	split = ft_split(str, ",");
	if (!split)
	{
		*status = 0;
		return (ret);
	}
	if (split_len(split) != 3)
	{
		*status = 0;
		free_split(split);
		return (ret);
	}
	*status = atovec_util(split, &ret);
	free_split(split);
	return (ret);
}

static int	atovec_util(char **split, t_vector *ret)
{
	int		status;
	double	x;
	double	y;
	double	z;

	status = 1;
	x = ft_atof_stat(split[0], &status);
	if (!status)
		return (0);
	y = ft_atof_stat(split[1], &status);
	if (!status)
		return (0);
	z = ft_atof_stat(split[2], &status);
	if (!status)
		return (0);
	*ret = vector(x, y, z);
	return (1);
}
