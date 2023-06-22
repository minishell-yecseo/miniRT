#include "args_bonus.h"

int	get_split_idx(int obj_type, char **split, int *ret)
{
	int	len;

	len = split_len(split);
	if (obj_type == sp || obj_type == pl)
	{
		if (len == 5)
			*ret = 3;
		else if (len == 6)
			*ret = 4;
		else
			return (0);
	}
	else if (obj_type == cy || obj_type == co || obj_type == ci)
	{
		if (len == 7)
			*ret = 3;
		else if (len == 8)
			*ret = 4;
		else
			return (0);
	}
	return (1);
}
