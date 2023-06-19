#include "miniRT.h"

static int	mall_check(char *tmp, char **res);
static int	w_num(char *s, char sep);
static int	w_len(char *s, char sep);

char	**ft_split(char const *s, char c)
{
	char	**res;
	char	**tmp;

	res = (char **) malloc(sizeof (char *) * (w_num((char *) s, c) + 1));
	if (!res)
		return (0);
	tmp = res;
	while (*s)
	{
		if (!(*s == c))
		{
			*tmp = (char *) malloc (sizeof (char) * (w_len((char *)s, c) + 1));
			if (!mall_check(*tmp, res))
				return (0);
			ft_strlcpy(*tmp, (char *)s, (w_len((char *)s, c) + 1));
			s += w_len((char *)s, c);
			tmp++;
		}
		else
			s++;
	}
	*tmp = 0;
	return (res);
}

static int	w_num(char *s, char sep)
{
	int	word_num;
	int	word_size;

	word_num = 0;
	while (*s)
	{
		word_size = w_len(s, sep);
		if (word_size > 0)
		{
			s += word_size;
			word_num++;
		}
		else
			s++;
	}
	return (word_num);
}

static int	w_len(char *s, char sep)
{
	int	word_size;

	word_size = 0;
	while (!(*s == sep || *s == 0))
	{
		word_size++;
		s++;
	}
	return (word_size);
}

static int	mall_check(char	*tmp, char **res)
{
	char	**res_temp;

	res_temp = res;
	if (!tmp)
	{
		while (*res_temp)
		{
			free(*res_temp);
			res_temp++;
		}
		free(res);
		return (0);
	}
	else
		return (1);
}

void	free_split(char **split)
{
	int	idx;
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
