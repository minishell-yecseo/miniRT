#include "utils.h"

int	check_color_range(t_vector *color)
{
	if (color->x < 0 || color->x > 255)
		return (0);
	if (color->y < 0 || color->y > 255)
		return (0);
	if (color->z < 0 || color->z > 255)
		return (0);
	color->x = color->x / 255.9;
	color->y = color->y / 255.9;
	color->z = color->z / 255.9;
	return (1);
}

int	check_norm_range(t_vector *norm)
{
	if (norm->x < -1.0 || norm->x > 1.0)
		return (0);
	if (norm->y < -1.0 || norm->y > 1.0)
		return (0);
	if (norm->z < -1.0 || norm->z > 1.0)
		return (0);
	*norm = vec_unit(*norm);
	return (1);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t dstsize)
{
	size_t	src_cnt;
	size_t	src_len;

	src_cnt = 0;
	src_len = ft_strlen((char *)src);
	if (!dstsize)
		return (src_len);
	while (*src && (1 + src_cnt++ < dstsize))
		*dest++ = *src++;
	*dest = 0;
	return (src_len);
}

void	ft_strncpy(char *dest, char *src, int size)
{
	int	idx;

	idx = 0;
	while (idx++ + 1 < size)
		*dest++ = *src++;
	*dest = 0;
}

void	error_print(char *msg)
{
	int	len;

	len = ft_strlen(msg);
	if (!len)
		return ;
	write(2, msg, len);
}
