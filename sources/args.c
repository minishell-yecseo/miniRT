#include "args.h"

int	check_args(int argc, char **argv, t_vars *vars)
{
	int		fd;
	int		line;
	char	*err_line;

	fd = 0;
	if (argc != 2)
	{
		error_print("miniRT: please input one scene file path\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		error_print("miniRT: open file error\n");
		return (0);
	}
	if (!check_file_expand(argv[1], ".rt"))
	{
		error_print("miniRT: input expand must be '.rt'\n");
		close(fd);
		return (0);
	}
	line = 0;
	if (!save_contents(fd, vars, &line))
	{
		if (line < 0)
			error_print("miniRT: Camera, Ambient light number must be one.\n");
		else
		{
			err_line = ft_itoa(line + 1);
			error_print("miniRT: file format error at line ");
			error_print(err_line);
			error_print("\n");
			free(err_line);
		}
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	save_contents(int fd, t_vars *vars, int *err_line)
{
	char	**split;
	char	*line;
	int		tmp;
	int		flags[2];
	char	whitespaces[7];

	ft_memset(flags, 0, sizeof(int) * 2);
	ft_memset(&(vars->scene), 0, sizeof(t_scene));
	ft_memset(&(vars->scene.objs), -1, sizeof(t_object) * (OBJ_MAX));
	ft_memset(&(vars->scene.lights), -1, sizeof(t_light) * (OBJ_MAX));
	get_whitespaces(whitespaces);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (is_white_line(line))
		{
			free(line);
			line = get_next_line(fd);
			*err_line += 1;
			continue ;
		}
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		split = ft_split(line, whitespaces);
		tmp = save_line(vars, split, flags);
		free(line);
		free_split(split);
		if (!tmp)
			return (0);
		line = get_next_line(fd);
		*err_line += 1;
	}
	if (flags[0] != 1 || flags[1] != 1)
	{
		*err_line = -1;
		return (0);
	}
	return (1);
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

int	save_ambient_light(t_vars *vars, char **split, int *flags)
{
	t_scene		*scene;
	t_light		light;
	int			status;
	t_vector	color;

	scene = &(vars->scene);
	status = 1;
	flags[AMBIENT] += 1;
	light.type = E_AMBIENT;
	if (split_len(split) != 3)
		return (0);
	light.ratio = ft_atof_stat(split[1], &status);
	if (!status || light.ratio < 0 || light.ratio > 1.0)
		return (0);
	light.color = ft_atovec_stat(split[2], &status);
	if (!status || !check_color_range(&light.color) || comma_number(split[2]) != 2)
		return (0);
	(scene->lights)[scene->lights_number] = light;
	scene->lights_number += 1;
	return (1);
}

int	save_lights(t_vars *vars, char **split)
{
	t_scene		*scene;
	int			status;
	t_light		light;
	t_vector	tmp;

	light.type = E_LIGHT;
	scene = &(vars->scene);
	status = 1;
	if (split_len(split) != 3 && split_len(split) != 4)
		return (0);
	light.origin = ft_atovec_stat(split[1], &status);
	if (!status || comma_number(split[1]) != 2)
		return (0);
	light.ratio = ft_atof_stat(split[2], &status);
	if (!status || light.ratio < 0 || light.ratio > 1.0)
		return (0);
	if (split_len(split) == 3)
		light.color = vector(1, 1, 1);
	else
		light.color = ft_atovec_stat(split[3], &status);
	if (!status || !check_color_range(&(light.color)) || comma_number(split[3]) != 2)
		return (0);
	scene->lights[scene->lights_number] = light;
	scene->lights_number += 1;
	return (1);
}

int	save_camera(t_vars *vars, char **split, int *flags)
{
	t_scene		*scene;
	t_camera	camera;
	int			status;

	scene = &(vars->scene);
	status = 1;
	if (split_len(split) != 4)
		return (0);
	flags[CAM] += 1;
	camera.origin = ft_atovec_stat(split[1], &status);
	if (!status || comma_number(split[1]) != 2)
		return (0);
	camera.dir = ft_atovec_stat(split[2], &status);
	if (!status || !check_norm_range(&camera.dir) || comma_number(split[2]) != 2)
		return (0);
	camera.fov = (double) ft_atoi_stat(split[3], &status);
	if (!status || camera.fov < 0 || camera.fov > 180)
		return (0);
	scene->camera = get_camera(camera.origin, camera.dir, camera.fov);
	return (1);
}

int	save_objs(t_vars *vars, char **split)
{
	int	status;

	status = 0;
	if (!ft_memcmp(split[0], "sp", len_max(split[0], "sp")))
		status = save_sp(vars, split);
	else if (!ft_memcmp(split[0], "pl", len_max(split[0], "pl")))
		status = save_pl(vars, split);
	else if (!ft_memcmp(split[0], "cy", len_max(split[0], "cy")))
		status = save_cy(vars, split);
	else if (!ft_memcmp(split[0], "co", len_max(split[0], "co")))
		status = save_co(vars, split);
	else if (!ft_memcmp(split[0], "ci", len_max(split[0], "ci")))
		status = save_ci(vars, split);
	if (status)
		(vars->scene).objs_number += 1;
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
	else if (!ft_memcmp(str, "co", len_max(str, "co")))
		ret = 1;
	else if (!ft_memcmp(str, "ci", len_max(str, "ci")))
		ret = 1;
	return (ret);
}

int	save_sp(t_vars *vars, char **split)
{
	t_scene		*scene;
	t_object	sphere;
	int			status;
	int			split_idx;

	scene = &(vars->scene);
	status = 1;
	sphere.type = sp;
	if (!get_split_idx(sphere.type, split, &split_idx))
		return (0);
	if (!save_objs_surface(vars, &sphere, split))
		return (0);
	sphere.center = ft_atovec_stat(split[split_idx], &status);
	if (!status || comma_number(split[split_idx++]) != 2)
		return (0);
	sphere.radius = ft_atof_stat(split[split_idx], &status) / 2.0;
	if (!status || sphere.radius <= 0)
		return (0);
	scene->objs[scene->objs_number] = sphere;
	return (1);
}

int	save_pl(t_vars *vars, char **split)
{
	t_scene		*scene;
	t_object	plane;
	int			status;
	int			split_idx;

	scene = &(vars->scene);
	status = 1;
	plane.type = pl;
	if (!get_split_idx(plane.type, split, &split_idx))
		return (0);
	if (!save_objs_surface(vars, &plane, split))
		return (0);
	plane.center = ft_atovec_stat(split[split_idx], &status);
	if (!status || comma_number(split[split_idx++]) != 2)
		return (0);
	plane.norm = ft_atovec_stat(split[split_idx], &status);
	if (!status || !check_norm_range(&plane.norm) || comma_number(split[split_idx]) != 2)
		return (0);
	scene->objs[scene->objs_number] = plane;
	return (1);
}

int	save_cy(t_vars *vars, char **split)
{
	t_scene		*scene;
	t_object	cylinder;
	int			status;
	int			split_idx;

	scene = &(vars->scene);
	status = 1;
	cylinder.type = cy;
	if (!get_split_idx(cylinder.type, split, &split_idx))
		return (0);
	if (!save_objs_surface(vars, &cylinder, split))
		return (0);
	cylinder.center = ft_atovec_stat(split[split_idx], &status);
	if (!status || comma_number(split[split_idx++]) != 2)
		return (0);
	cylinder.norm = ft_atovec_stat(split[split_idx], &status);
	if (!status || !check_norm_range(&cylinder.norm) || comma_number(split[split_idx++]) != 2)
		return (0);
	cylinder.radius = ft_atof_stat(split[split_idx++], &status) / 2;
	if (!status || cylinder.radius <= 0)
		return (0);
	cylinder.height = ft_atof_stat(split[split_idx++], &status);
	if (!status || cylinder.height <= 0)
		return (0);
	scene->objs[scene->objs_number] = cylinder;
	return (1);
}

int	save_co(t_vars *vars, char **split)
{
	t_scene		*scene;
	t_object	cone;
	int			status;
	int			split_idx;

	scene = &(vars->scene);
	status = 1;
	cone.type = co;
	if (!get_split_idx(cone.type, split, &split_idx))
		return (0);
	if (!save_objs_surface(vars, &cone, split))
		return (0);
	cone.center = ft_atovec_stat(split[split_idx], &status);
	if (!status || comma_number(split[split_idx++]) != 2)
		return (0);
	cone.norm = ft_atovec_stat(split[split_idx], &status);
	if (!status || !check_norm_range(&cone.norm) || comma_number(split[split_idx++]) != 2)
		return (0);
	cone.radius = ft_atof_stat(split[split_idx++], &status) / 2;
	if (!status || cone.radius <= 0)
		return (0);
	cone.height = ft_atof_stat(split[split_idx++], &status);
	if (!status || cone.height <= 0)
		return (0);
	scene->objs[scene->objs_number] = cone;
	return (1);
}

int	save_ci(t_vars *vars, char **split)
{
	t_scene		*scene;
	t_object	circle;
	int			status;
	int			split_idx;

	scene = &(vars->scene);
	status = 1;
	circle.type = ci;
	if (!get_split_idx(circle.type, split, &split_idx))
		return (0);
	if (!save_objs_surface(vars, &circle, split))
		return (0);
	circle.center = ft_atovec_stat(split[split_idx], &status);
	if (!status || comma_number(split[split_idx++]) != 2)
		return (0);
	circle.norm = ft_atovec_stat(split[split_idx], &status);
	if (!status || !check_norm_range(&circle.norm) || comma_number(split[split_idx++]) != 2)
		return (0);
	circle.radius = ft_atof_stat(split[split_idx++], &status) / 2;
	if (!status || circle.radius <= 0)
		return (0);
	circle.height = ft_atof_stat(split[split_idx++], &status);
	if (!status || circle.height <= 0)
		return (0);
	scene->objs[scene->objs_number] = circle;
	return (1);
}

int	get_split_idx(int obj_type, char **split, int *ret)
{
	int	len;

	len = split_len(split);
	if (obj_type == sp || obj_type == pl)
	{
		if (len == 5)
			*ret = 3;
		else if (len == 6)
			*ret = 4;
		else
			return (0);
	}
	else if (obj_type == cy || obj_type == co || obj_type == ci)
	{
		if (len == 7)
			*ret = 3;
		else if (len == 8)
			*ret = 4;
		else
			return (0);
	}
	return (1);
}

int	save_objs_surface(t_vars *vars, t_object *obj, char **split)
{
	char	*type;
	int		status;

	type = split[1];
	if (!ft_memcmp(type, "color", len_max(type, "color")))
		status = save_objs_color(obj, split);
	else if (!ft_memcmp(type, "checker", len_max(type, "checker")))
		status = save_objs_checker(obj, split);
	else if (!ft_memcmp(type, "texture", len_max(type, "texture")))
		status = save_objs_texture(vars, obj, split);
	else
		status = 0;
	return (status);
}

int	save_objs_color(t_object *obj, char **split)
{
	t_surface	surface;
	int			status;

	status = 1;
	surface.type = COLOR;
	surface.color = ft_atovec_stat(split[2], &status);
	if (!status || !check_color_range(&(surface.color)) || comma_number(split[2]) != 2)
		return (0);
	obj->surface = surface;
	return (1);
}

int	save_objs_checker(t_object *obj, char **split)
{
	t_surface	surface;
	t_vector	color1;
	t_vector	color2;
	int			status;

	status = 1;
	surface.type = CHECKER;
	surface.color = ft_atovec_stat(split[2], &status);
	if (!status || !check_color_range(&(surface.color)) || comma_number(split[2]) != 2)
		return (0);
	surface.color2 = ft_atovec_stat(split[3], &status);
	if (!status || !check_color_range(&(surface.color2)) || comma_number(split[3]) != 2)
		return (0);
	obj->surface = surface;
	return (1);
}

int	save_objs_texture(t_vars *vars, t_object *obj, char **split)
{
	t_surface	surface;
	t_img		texture;
	t_img		bump;
	int			texture_fd;
	int			bump_fd;

	surface.type = TEXTURE;
	if (!check_file_expand(split[2], ".xpm"))
		return (0);
	texture_fd = open(split[2], O_RDONLY);
	if (!ft_memcmp(split[3], "default", len_max(split[3], "default")))
		bump_fd = 0;
	else if (check_file_expand(split[3], ".xpm"))
		bump_fd = open(split[3], O_RDONLY);
	else
		bump_fd = -1;
	close(texture_fd);
	close(bump_fd);
	if (texture_fd < 0 || bump_fd < 0)
		return (0);
	texture.image = mlx_xpm_file_to_image(vars->mlx, split[2], &texture.w, &texture.h);
	texture.data = (int *)mlx_get_data_addr(texture.image, &texture.bits_per_pixel, &texture.size_len, &texture.endian);
	if (bump_fd > 0)
	{
		bump.image = mlx_xpm_file_to_image(vars->mlx, split[3], &bump.w, &bump.h);
		bump.data = (int *)mlx_get_data_addr(bump.image, &bump.bits_per_pixel, &bump.size_len, &bump.endian);
	}
	else if (bump_fd == 0)
		surface.is_bump = 0;
	surface.texture = texture;
	surface.bump = bump;
	obj->surface = surface;
	return (1);
}
