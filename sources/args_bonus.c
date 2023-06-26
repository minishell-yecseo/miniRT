/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:57:26 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 14:57:26 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_bonus.h"

int	check_args(int argc, char **argv, t_vars *vars)
{
	int		fd;

	if (argc != 2)
	{
		error_print("Error\nPlease input one scene file path\n");
		return (0);
	}
	fd = rt_file_check(argv[1]);
	if (fd < 0)
		return (0);
	if (!save(fd, vars))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	save(int fd, t_vars *vars)
{
	int		error_line;
	char	*a_error_line;

	error_line = 0;
	if (!save_contents(fd, vars, &error_line))
	{
		if (error_line < 0)
			error_print("Error\nCamera, Ambient light number must be one.\n");
		else
		{
			a_error_line = ft_itoa(error_line + 1);
			error_print("Error\nFile format error at line ");
			error_print(a_error_line);
			error_print("\n");
			free(a_error_line);
		}
		return (0);
	}
	return (1);
}

int	save_contents(int fd, t_vars *vars, int *err_line)
{
	t_save	s;

	init_contents_flags(s.flags, vars, s.whitespaces);
	s.line = get_next_line(fd);
	while (s.line != NULL)
	{
		if (is_white_line(s.line))
		{
			free(s.line);
			s.line = get_next_line(fd);
			*err_line += 1;
			continue ;
		}
		rstrip(s.line);
		s.split = ft_split(s.line, s.whitespaces);
		s.tmp = save_line(vars, s.split, s.flags);
		free(s.line);
		free_split(s.split);
		if (!s.tmp)
			return (0);
		s.line = get_next_line(fd);
		*err_line += 1;
	}
	return (check_contents_flags(s.flags, 2));
}

void	init_contents_flags(int *flags, t_vars *vars, char *whitespaces)
{
	ft_memset(flags, 0, sizeof(int) * 2);
	ft_memset(&(vars->scene), 0, sizeof(t_scene));
	ft_memset(&(vars->scene.objs), no, sizeof(t_object) * (OBJ_MAX));
	ft_memset(&(vars->scene.lights), NO_LIGHT, sizeof(t_light) * (OBJ_MAX));
	get_whitespaces(whitespaces);
}

int	save_line(t_vars *vars, char **split, int *flags)
{
	t_scene	*scene;
	int		ret;

	scene = &(vars->scene);
	if (!ft_memcmp(split[0], "A", len_max(split[0], "A")))
		ret = save_ambient_light(vars, split, flags);
	else if (!ft_memcmp(split[0], "C", len_max(split[0], "C")))
		ret = save_camera(vars, split, flags);
	else if (!ft_memcmp(split[0], "L", len_max(split[0], "L")))
	{
		if (scene->lights_number - 1 == OBJ_MAX)
			return (0);
		ret = save_lights(vars, split);
	}
	else if (is_obj_line(split[0]))
	{
		if (scene->objs_number - 1 == OBJ_MAX)
			return (0);
		ret = save_objs(vars, split);
	}
	else
		ret = 0;
	return (ret);
}
