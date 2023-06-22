#include "utils.h"

static int	mall_check(char *tmp, char **res);
static int	w_num(char *str, char *charset);
static int	w_size(char *str, char *charset);
static int	is_sep(char c, char *charset);

char	**ft_split(char *str, char *charset)
{
	char	**res;
	char	**tmp;

	res = (char **) malloc(sizeof (char *) * (w_num(str, charset) + 1));
	if (!res)
		return (NULL);
	tmp = res;
	while (*str)
	{
		if (!is_sep(*str, charset))
		{
			*tmp = (char *) malloc(sizeof (char) * (w_size(str, charset) + 1));
			if (!mall_check(*tmp, res))
				return (NULL);
			ft_strncpy(*tmp, str, w_size(str, charset) + 1);
			str += w_size(str, charset);
			tmp++;
		}
		else
			str++;
	}
	*tmp = NULL;
	return (res);
}

static int	mall_check(char *tmp, char **res)
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
	return (1);
}

static int	w_num(char *str, char *charset)
{
	int	word_num;
	int	word_size;

	word_num = 0;
	while (*str)
	{
		word_size = w_size(str, charset);
		if (word_size > 0)
		{
			str += word_size;
			word_num++;
		}
		else
			str++;
	}
	return (word_num);
}

static int	w_size(char *str, char *charset)
{
	int	word_size;

	word_size = 0;
	while (!is_sep(*str++, charset))
		word_size++;
	return (word_size);
}

static int	is_sep(char c, char *charset)
{
	if (!charset || c == 0)
		return (1);
	while (*charset)
	{
		if (*charset == c)
			return (1);
		charset++;
	}
	return (0);
}
