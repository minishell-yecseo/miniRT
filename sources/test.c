#include "miniRT.h"
#include "ray.h"
#include "object.h"
#include "light.h"

t_vector ray_color(t_object *objs, t_ray r, t_hit_rec *rec);
t_vector get_vec_color(int color);
t_vector get_vec_color(int color);
int test_color(t_vector color);

void test(t_img *img, t_vars *vars)
{
	int		x;
	int		y;
	int		color;
	t_camera	cam;
	t_hit_rec	rec;

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
			t_ray r = ray(cam.origin, vec_unit(vec_sub(vec_add(vec_mul(cam.right, (double)x), vec_add(cam.lower_left_corner, vec_mul(cam.up, (double)y))), cam.origin)));
			t_vector color = ray_color((vars->scene).objs, r, &rec);
			paint(img, x, y, test_color(color));
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->image, 0, 0);
}

t_vector ray_color(t_object *objs, t_ray r, t_hit_rec *rec)
{
	if (is_hit(objs, r, rec))
		return lighting(objs, r, rec); // return (vec_mul(vec_add(rec->normal, vector(1, 1, 1)), 0.5));

	// sky
	// double t;
	// t_vector	unit_direction = vec_unit(r.dir);
	// t = 0.5 * (unit_direction.y + 1);
	// return vec_add(vec_mul(vector(1, 1, 1), (1 - t)), vec_mul(vector(0.5, 0.7, 1), t));
	return vector(0, 0, 0);
}

t_vector get_vec_color(int color)
{
	t_vector ret;
	int tmp;
	int mask;

	mask = 255;
	tmp = (color >> 16) & mask;
	ret.x = tmp / 255.999;
	tmp = (color >> 8) & mask;
	ret.y = tmp / 255.999;
	tmp = (color)&mask;
	ret.z = tmp / 255.999;
	return (ret);
}

int test_color(t_vector color)
{
	int ret;

	ret = 0x00000000;
	ret = ((int)(255.999 * color.x) << 16) + ((int)(255.999 * color.y) << 8) + (int)(255.999 * color.z);
	return (ret);
}
