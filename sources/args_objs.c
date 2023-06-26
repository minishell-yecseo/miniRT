/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_objs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:31 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 15:02:31 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"

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
