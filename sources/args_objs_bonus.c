#include "args_bonus.h"

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
	if (!status || !check_norm_range(&plane.norm) \
		|| comma_number(split[split_idx]) != 2)
		return (0);
	scene->objs[scene->objs_number] = plane;
	return (1);
}

int	save_cy(t_vars *vars, char **split)
{
	t_object	cylinder;
	int			status;
	int			split_idx;

	status = 1;
	cylinder.type = cy;
	if (!get_split_idx(cylinder.type, split, &split_idx) || \
		!save_objs_surface(vars, &cylinder, split))
		return (0);
	cylinder.center = ft_atovec_stat(split[split_idx], &status);
	if (!status || comma_number(split[split_idx++]) != 2)
		return (0);
	cylinder.norm = ft_atovec_stat(split[split_idx], &status);
	if (!status || !check_norm_range(&cylinder.norm) \
		|| comma_number(split[split_idx++]) != 2)
		return (0);
	cylinder.radius = ft_atof_stat(split[split_idx++], &status) / 2;
	if (!status || cylinder.radius <= 0)
		return (0);
	cylinder.height = ft_atof_stat(split[split_idx++], &status);
	if (!status || cylinder.height <= 0)
		return (0);
	(vars->scene).objs[(vars->scene).objs_number] = cylinder;
	return (1);
}

int	save_co(t_vars *vars, char **split)
{
	t_object	cone;
	int			status;
	int			split_idx;

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
	if (!status || !check_norm_range(&cone.norm) \
		|| comma_number(split[split_idx++]) != 2)
		return (0);
	cone.radius = ft_atof_stat(split[split_idx++], &status) / 2;
	if (!status || cone.radius <= 0)
		return (0);
	cone.height = ft_atof_stat(split[split_idx++], &status);
	if (!status || cone.height <= 0)
		return (0);
	(vars->scene).objs[(vars->scene).objs_number] = cone;
	return (1);
}

int	save_ci(t_vars *vars, char **split)
{
	t_object	circle;
	int			status;
	int			split_idx;

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
	if (!status || !check_norm_range(&circle.norm) \
		|| comma_number(split[split_idx++]) != 2)
		return (0);
	circle.radius = ft_atof_stat(split[split_idx++], &status) / 2;
	if (!status || circle.radius <= 0)
		return (0);
	circle.height = ft_atof_stat(split[split_idx++], &status);
	if (!status || circle.height <= 0)
		return (0);
	(vars->scene).objs[(vars->scene).objs_number] = circle;
	return (1);
}
