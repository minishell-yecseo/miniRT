#include "utils.h"

int	len_max(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	return (len2);
}

int	split_len(char **split)
{
	int	ret;

	ret = 0;
	if (!split)
		return (0);
	while (*split)
	{
		ret++;
		split++;
	}
	return (ret);
}

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

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*_s1;
	unsigned char	*_s2;

	_s1 = (unsigned char *) s1;
	_s2 = (unsigned char *) s2;
	while (n--)
	{
		if (*_s1 != *_s2)
			return (*_s1 - *_s2);
		_s1++;
		_s2++;
	}
	return (0);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*tmp;

	tmp = (unsigned char *) b;
	while (len--)
		*tmp++ = (unsigned char) c;
	return (b);
}
