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

char	*get_whitespaces(char *charset)
{
	char	value;
	int		idx;

	idx = 0;
	value = 9;
	while (idx < 5)
		charset[idx++] = value++;
	charset[idx++] = 32;
	charset[idx] = '\0';
	return (charset);
}

void	free_split(char **split)
{
	int		idx;
	char	*tmp;

	idx = 0;
	tmp = *split;
	while (tmp)
	{
		free(tmp);
		tmp = split[++idx];
	}
	free(split);
}

int	comma_number(char *str)
{
	int	comma_number;
	int	len;

	comma_number = 0;
	len = ft_strlen(str);
	while (len--)
	{
		if (*str++ == ',')
			comma_number++;
	}
	return (comma_number);
}
