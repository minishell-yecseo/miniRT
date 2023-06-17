#include "miniRT.h"

int	check_args(int argc, char **argv, t_scene *scene)
{
	int	fd;

	fd = 0;
	if (argc != 2)
	{
		error_print("miniRT: please input one scene file path\n");
		return (0);
	}
	// 1. check if file is available
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		error_print("miniRT: open file error\n");
		return (0);
	}
	// 2. check if contents are valid
	//    - and if it's valid, set scene
	close(fd);
	return (1);
}

void	error_print(char *msg)
{
	int	len;

	len = ft_strlen(msg);
	if (!len)
		return ;
	write(2, msg, len);
}
