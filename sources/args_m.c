#include "args_m.h"

int	check_args(int argc, char **argv, t_scene *scene)
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
	if (!save(fd, scene))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	save(int fd, t_scene *scene)
{
	int		error_line;
	char	*a_error_line;

	error_line = 0;
	if (!save_contents(fd, scene, &error_line))
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

void	init_contents_flags(int *flags, t_scene *scene, char *whitespaces)
{
	ft_memset(flags, 0, sizeof(int) * 3);
	ft_memset(scene, 0, sizeof(t_scene));
	ft_memset(&(scene->objs), -1, sizeof(t_object) * (OBJ_MAX));
	ft_memset(&(scene->lights), -1, sizeof(t_light) * (OBJ_MAX));
	get_whitespaces(whitespaces);
}

int	save_contents(int fd, t_scene *scene, int *err_line)
{
	t_save	s;

	init_contents_flags(s.flags, scene, s.whitespaces);
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
		s.tmp = save_line(scene, s.split, s.flags);
		free(s.line);
		free_split(s.split);
		if (!s.tmp)
			return (0);
		s.line = get_next_line(fd);
		*err_line += 1;
	}
	return ((check_contents_flags(s.flags, 3, err_line)));
}

int	save_line(t_scene *scene, char **split, int *flags)
{
	int	ret;

	if (!ft_memcmp(split[0], "A", len_max(split[0], "A")))
		ret = save_ambient_light(scene, split, flags);
	else if (!ft_memcmp(split[0], "C", len_max(split[0], "C")))
		ret = save_camera(scene, split, flags);
	else if (!ft_memcmp(split[0], "L", len_max(split[0], "L")))
		ret = save_lights(scene, split, flags);
	else if (is_obj_line(split[0]))
	{
		if (scene->objs_number - 1 == OBJ_MAX)
			return (0);
		ret = save_objs(scene, split);
	}
	else
		ret = 0;
	return (ret);
}

int	save_ambient_light(t_scene *scene, char **split, int *flags)
{
	t_light		light;
	int			status;
	t_vector	color;

	status = 1;
	flags[AMBIENT] += 1;
	light.type = E_AMBIENT;
	if (split_len(split) != 3)
		return (0);
	light.ratio = ft_atof_stat(split[1], &status);
	if (!status || light.ratio < 0 || light.ratio > 1.0)
		return (0);
	light.color = ft_atovec_stat(split[2], &status);
	if (!status || !check_color_range(&light.color) \
		|| comma_number(split[2]) != 2)
		return (0);
	(scene->lights)[scene->lights_number] = light;
	scene->lights_number += 1;
	return (1);
}

int	save_lights(t_scene *scene, char **split, int *flags)
{
	int			status;
	t_light		light;

	flags[LIGHT] += 1;
	light.type = E_LIGHT;
	status = 1;
	if (split_len(split) != 3)
		return (0);
	light.origin = ft_atovec_stat(split[1], &status);
	if (!status || comma_number(split[1]) != 2)
		return (0);
	light.ratio = ft_atof_stat(split[2], &status);
	if (!status || light.ratio < 0 || light.ratio > 1.0)
		return (0);
	light.color = vector(255, 255, 255);
	scene->lights[scene->lights_number] = light;
	scene->lights_number += 1;
	return (1);
}

int	save_camera(t_scene *scene, char **split, int *flags)
{
	t_camera	camera;
	int			status;

	flags[CAM] += 1;
	status = 1;
	if (split_len(split) != 4)
		return (0);
	camera.origin = ft_atovec_stat(split[1], &status);
	if (!status || comma_number(split[1]) != 2)
		return (0);
	camera.dir = ft_atovec_stat(split[2], &status);
	if (!status || !check_norm_range(&camera.dir) \
		|| comma_number(split[2]) != 2)
		return (0);
	camera.fov = (double) ft_atoi_stat(split[3], &status);
	if (!status || camera.fov < 0 || camera.fov > 180)
		return (0);
	scene->camera = get_camera(camera.origin, camera.dir, camera.fov);
	return (1);
}

int	save_objs(t_scene *scene, char **split)
{
	int	status;

	status = 0;
	if (!ft_memcmp(split[0], "sp", len_max(split[0], "sp")))
		status = save_sp(scene, split);
	else if (!ft_memcmp(split[0], "pl", len_max(split[0], "pl")))
		status = save_pl(scene, split);
	else if (!ft_memcmp(split[0], "cy", len_max(split[0], "cy")))
		status = save_cy(scene, split);
	if (status)
		scene->objs_number += 1;
	return (status);
}

int	is_obj_line(char *str)
{
	int	ret;

	ret = 0;
	if (!ft_memcmp(str, "sp", len_max(str, "sp")))
		ret = 1;
	else if (!ft_memcmp(str, "pl", len_max(str, "pl")))
		ret = 1;
	else if (!ft_memcmp(str, "cy", len_max(str, "cy")))
		ret = 1;
	return (ret);
}

int	save_sp(t_scene *scene, char **split)
{
	t_object	sphere;
	int			status;

	status = 1;
	sphere.type = sp;
	if (split_len(split) != 4)
		return (0);
	sphere.center = ft_atovec_stat(split[1], &status);
	if (!status || comma_number(split[1]) != 2)
		return (0);
	sphere.radius = ft_atof_stat(split[2], &status) / 2.0;
	if (!status || sphere.radius <= 0)
		return (0);
	if (!save_objs_color(&sphere, split[3]))
		return (0);
	scene->objs[scene->objs_number] = sphere;
	return (1);
}

int	save_pl(t_scene *scene, char **split)
{
	t_object	plane;
	int			status;

	status = 1;
	plane.type = pl;
	if (split_len(split) != 4)
		return (0);
	plane.center = ft_atovec_stat(split[1], &status);
	if (!status || comma_number(split[1]) != 2)
		return (0);
	plane.norm = ft_atovec_stat(split[2], &status);
	if (!status || !check_norm_range(&plane.norm) \
		|| comma_number(split[2]) != 2)
		return (0);
	if (!save_objs_color(&plane, split[3]))
		return (0);
	scene->objs[scene->objs_number] = plane;
	return (1);
}

int	save_cy(t_scene *scene, char **split)
{
	t_object	cylinder;
	int			status;

	status = 1;
	cylinder.type = cy;
	if (split_len(split) != 6)
		return (0);
	cylinder.center = ft_atovec_stat(split[1], &status);
	if (!status || comma_number(split[1]) != 2)
		return (0);
	cylinder.norm = ft_atovec_stat(split[2], &status);
	if (!status || !check_norm_range(&cylinder.norm) \
		|| comma_number(split[2]) != 2)
		return (0);
	cylinder.radius = ft_atof_stat(split[3], &status) / 2;
	if (!status || cylinder.radius <= 0)
		return (0);
	cylinder.height = ft_atof_stat(split[4], &status);
	if (!status || cylinder.height <= 0)
		return (0);
	if (!save_objs_color(&cylinder, split[5]))
		return (0);
	scene->objs[scene->objs_number] = cylinder;
	return (1);
}

int	save_objs_color(t_object *obj, char *color)
{
	t_surface	surface;
	int			status;

	status = 1;
	surface.type = COLOR;
	surface.color = ft_atovec_stat(color, &status);
	if (!status || !check_color_range(&(surface.color)) \
		|| comma_number(color) != 2)
		return (0);
	obj->surface = surface;
	return (1);
}
