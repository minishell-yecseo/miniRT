/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_surface_bonus_2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saseo <saseo@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/29 13:00:22 by saseo             #+#    #+#             */
/*   Updated: 2023/06/29 13:00:26 by saseo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args_bonus.h"

static int	_get_xpm_image(t_vars *vars, t_img *img, char *path);

int	save_objs_texture(t_vars *vars, t_object *obj, char **split)
{
	t_surface	surface;
	t_img		texture;
	t_img		bump;

	surface.type = TEXTURE;
	if (!check_texture_files(&surface, split[2], split[3]))
		return (0);
	if (!_get_xpm_image(vars, &texture, split[2]))
		return (0);
	if (surface.is_bump)
	{
		if (!_get_xpm_image(vars, &bump, split[3]))
			return (0);
	}
	else
		ft_memset(&bump, 0, sizeof(t_img));
	surface.texture = texture;
	surface.bump = bump;
	obj->surface = surface;
	return (1);
}

int	check_texture_files(t_surface *surface, char *texture, char *bump)
{
	int	texture_fd;
	int	bump_fd;

	if (!check_file_expand(texture, ".xpm"))
		return (0);
	texture_fd = open(texture, O_RDONLY);
	if (!ft_memcmp(bump, "default", len_max(bump, "default")))
		bump_fd = 0;
	else if (check_file_expand(bump, ".xpm"))
		bump_fd = open(bump, O_RDONLY);
	else
		bump_fd = -1;
	close(texture_fd);
	close(bump_fd);
	if (texture_fd < 0 || bump_fd < 0)
		return (0);
	surface->is_bump = bump_fd;
	return (1);
}

static int	_get_xpm_image(t_vars *vars, t_img *img, char *path)
{
	img->image = mlx_xpm_file_to_image(vars->mlx, path, &(img->w), &(img->h));
	if (!img->image)
		return (0);
	img->data = (int *) mlx_get_data_addr(img->image, &(img->bits_per_pixel), \
						&(img->size_len), &(img->endian));
	if (!img->data)
		return (0);
	return (1);
}
