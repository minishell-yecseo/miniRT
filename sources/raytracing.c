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

/*
void set_two_spheres(t_object *objs)
{
	objs[0].type = sp;
	objs[0].center = vector(0, 0, 0);
	objs[0].color = vector(1, 1, 1);
	objs[0].norm = vec_unit(vector(0, 1, 0));
	objs[0].height = 3;
	objs[0].radius = 2;
	objs[0].checker.is_checker = 0;
	objs[0].is_texture = 1;

	objs[1].type = ci;
	objs[1].center = vector(0, 0, 0);
	objs[1].color = vec_unit(vector(51, 0, 25));
	objs[1].norm = vec_unit(vector(0, 1, 0));
	objs[1].checker.is_checker = 0;
	objs[1].is_texture = 0;
	objs[1].radius = 4;
	objs[1].height = 0.05;

	objs[2].type = ci;
	objs[2].center = vector(0, 0, 0);
	objs[2].color = vec_unit(vector(53, 25, 0));
	objs[2].norm = vec_unit(vector(0.3, 1, 0));
	objs[2].checker.is_checker = 0;
	objs[2].is_texture = 0;
	objs[2].radius = 4;
	objs[2].height = 0.05;

	objs[3].type = ci;
	objs[3].center = vector(0, 0, 0);
	objs[3].color = vec_unit(vector(1, 1, 1));
	objs[3].norm = vec_unit(vector(-0.8, 1, 0));
	objs[3].checker.is_checker = 0;
	objs[3].is_texture = 0;
	objs[3].radius = 4;
	objs[3].height = 0.05;

	objs[4].type = ci;
	objs[4].center = vector(0, 0, 0);
	objs[4].color = vector(0.1, 0.1, 0.1);
	objs[4].norm = vec_unit(vector(-0.3, 1, 0.1));
	objs[4].checker.is_checker = 0;
	objs[4].is_texture = 0;
	objs[4].radius = 10;
	objs[4].height = 0.5;

	objs[5].type = ci;
	objs[5].center = vector(0, 0, 0);
	objs[5].color = vector(0.1, 0.1, 0.1);
	objs[5].norm = vec_unit(vector(-0.3, 1, 0.1));
	objs[5].checker.is_checker = 0;
	objs[5].is_texture = 0;
	objs[5].radius = 9;
	objs[5].height = 0.05;

	objs[6].type = -1;
}

void set_light(t_light *lights)
{
	lights[0].type = ambient;
	lights[0].color = vector(1, 1, 1);
	lights[0].ratio = 0.5;

	lights[1].type = light;
	lights[1].origin = vector(-5, 5, 0);
	lights[1].ratio = 0.2;
	lights[1].color = vector(1, 0, 0);

	lights[2].type = light;
	lights[2].origin = vector(4, 4, 5);
	lights[2].ratio = 1;
	lights[2].color = vector(0, 0, 1);

	lights[3].type = light;
	lights[3].origin = vector(0, 0, 7);
	lights[3].ratio = 1;
	lights[3].color = vector(1, 1, 1);

	lights[4].type = -1;
}
*/
