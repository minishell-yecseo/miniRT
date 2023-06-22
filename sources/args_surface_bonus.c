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

int	save_objs_texture(t_vars *vars, t_object *obj, char **split)
{
	t_surface	surface;
	t_img		texture;
	t_img		bump;

	surface.type = TEXTURE;
	if (!check_texture_files(&surface, split[2], split[3]))
		return (0);
	texture.image = mlx_xpm_file_to_image(\
					vars->mlx, split[2], &texture.w, &texture.h);
	texture.data = (int *)mlx_get_data_addr(texture.image, \
				&texture.bits_per_pixel, &texture.size_len, &texture.endian);
	if (surface.is_bump != 0)
	{
		bump.image = mlx_xpm_file_to_image(\
							vars->mlx, split[3], &bump.w, &bump.h);
		bump.data = (int *)mlx_get_data_addr(bump.image, \
					&bump.bits_per_pixel, &bump.size_len, &bump.endian);
	}
	else
		ft_memset(&bump, sizeof(t_img), 1);
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
	surface->is_bump = 0;
	return (1);
}
