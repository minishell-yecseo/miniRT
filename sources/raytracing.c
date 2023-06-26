/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:03:04 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 15:03:04 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

t_vector	ray_color(t_object *objs, t_ray r, t_hit_rec *rec);
t_vector	get_vec_color(int color);
t_vector	get_vec_color(int color);
int			get_ret_color(t_vector color);

t_ray	get_ray(t_camera cam, int x, int y)
{
	t_ray	r;

	r = ray(cam.origin, vec_unit(vec_sub(vec_add(vec_mul(cam.right, (double)x), \
		vec_add(cam.lower_left_corner, \
		vec_mul(cam.up, (double)y))), cam.origin)));
	return (r);
}

void	drawing(t_img *img, t_vars *vars)
{
	int			x;
	int			y;
	t_camera	cam;
	t_hit_rec	rec;
	t_vector	color;

	cam = (vars->scene).camera;
	rec.tmin = EPSILON;
	rec.lights = (vars->scene).lights;
	mlx_clear_window(vars->mlx, vars->win);
	y = HEIGHT - 1;
	while (--y >= 0)
	{
		x = -1;
		while (++x < WIDTH)
		{
			rec.tmax = REC_TMAX;
			color = ray_color((vars->scene).objs, get_ray(cam, x, y), &rec);
			paint(img, x, y, get_ret_color(color));
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->image, 0, 0);
}

t_vector	ray_color(t_object *objs, t_ray r, t_hit_rec *rec)
{
	if (is_hit(objs, r, rec))
		return (lighting(objs, r, rec));
	return (vector(0, 0, 0));
}

t_vector	get_vec_color(int color)
{
	t_vector	vec;
	int			tmp;
	int			mask;

	mask = 255;
	tmp = (color >> 16) & mask;
	vec.x = tmp / 255.999;
	tmp = (color >> 8) & mask;
	vec.y = tmp / 255.999;
	tmp = (color) & mask;
	vec.z = tmp / 255.999;
	return (vec);
}

int	get_ret_color(t_vector color)
{
	int	ret;

	ret = 0x00000000;
	ret = ((int)(255.999 * color.x) << 16) + \
		((int)(255.999 * color.y) << 8) + \
		(int)(255.999 * color.z);
	return (ret);
}
