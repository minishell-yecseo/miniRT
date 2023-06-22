#include "args.h"

int	save_ambient_light(t_scene *scene, char **split, int *flags)
{
	t_light		light;
	int			status;

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
