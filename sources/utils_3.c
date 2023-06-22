#include "utils.h"

// expand should include . (dot)
int	check_file_expand(char *path, char *expand)
{
	int	path_len;
	int	expand_len;
	int	dot_idx;

	path_len = ft_strlen(path);
	expand_len = ft_strlen(expand);
	if (expand_len > path_len)
		return (0);
	if (!ft_memcmp(&path[path_len - expand_len], expand, expand_len))
		return (1);
	return (0);
}

int	is_white_line(char *line)
{
	int	len;

	len = ft_strlen(line);
	if (!len)
		return (0);
	while (len--)
	{
		if (ft_ctype(*line) == 3)
			line++;
		else
			return (0);
	}
	return (1);
}
