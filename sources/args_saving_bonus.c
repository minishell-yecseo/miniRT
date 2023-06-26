/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_saving_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:57:38 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 14:57:38 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_bonus.h"

int	save_ambient_light(t_vars *vars, char **split, int *flags)
{
	t_scene		*scene;
	t_light		light;
	int			status;

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
	if (!status || !check_color_range(&light.color) \
		|| comma_number(split[2]) != 2)
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
	if (!status || !check_color_range(&(light.color)) \
		|| comma_number(split[3]) != 2)
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
	if (!status || !check_norm_range(&camera.dir) \
		|| comma_number(split[2]) != 2)
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
