/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_surface_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:34 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/27 14:13:01 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_bonus.h"

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
	if (!status || !check_color_range(&(surface.color)) \
		|| comma_number(split[2]) != 2)
		return (0);
	obj->surface = surface;
	return (1);
}

int	save_objs_checker(t_object *obj, char **split)
{
	t_surface	surface;
	int			status;

	status = 1;
	surface.type = CHECKER;
	surface.color = ft_atovec_stat(split[2], &status);
	if (!status || !check_color_range(&(surface.color)) \
		|| comma_number(split[2]) != 2)
		return (0);
	surface.color2 = ft_atovec_stat(split[3], &status);
	if (!status || !check_color_range(&(surface.color2)) \
		|| comma_number(split[3]) != 2)
		return (0);
	obj->surface = surface;
	return (1);
}
