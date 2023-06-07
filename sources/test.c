#include "miniRT.h"
#include "ray.h"
#include "object.h"


t_vector ray_color(t_object *objs, t_ray r)
{
	// 현재, 첫 record가 없어서 두 번째 도형의 hit만 판별, 표현함
	double t = hit_obj(&objs[1], r);
	if (t > 0)
	{
		t_vector N = vec_unit(vec_sub(ray_at(r, t), vector(0,0,-1)));
		return vec_mul(objs->color, 0.5);
	}

	//sky
    t_vector	unit_direction = vec_unit(r.dir);
    t = 0.5 * (unit_direction.y + 1);
	return vec_add(vec_mul(vector(1, 1, 1), (1 - t)), vec_mul(vector(0.5, 0.7, 1), t));
}

int	test_color(t_vector color)
{
	int	ret;

	ret = 0x00000000;
	ret = ((int)(255.999 * color.x) << 16) + ((int)(255.999 * color.y) << 8) + (int)(255.999 * color.z);
	return (ret);
}

void	set_two_spheres(t_object *objs)
{
	// make two spheres
	objs[0].type = sp;
	objs[0].center = vector(0, 1, -2);
	objs[0].color = vector(18, 10, 100);
	objs[0].diameter = 0.5;

	objs[1].type = sp;
	objs[1].center = vector(1, 1, -2);
	objs[1].color = vector(10, 255, 100);
	objs[1].diameter = 0.3;
}

void	test(t_img *img, t_vars *vars)
{
	int			x;
	int			y;
	int			color;
	t_camera	cam;
	t_object	objs[2];

	cam = camera(vector(0, 0, 0));
	mlx_clear_window(vars->mlx, vars->win);

	set_two_spheres(objs);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			double u = (double)x / (double)(WIDTH);
			double v = (double)y / (double)(HEIGHT);
			t_ray r = ray(cam.origin, vec_sub(vec_add(vec_mul(cam.right, u), vec_add(cam.lower_left_corner, vec_mul(cam.up, v))), cam.origin));
			t_vector color = ray_color(objs, r);
			paint(img, x, y, test_color(color));
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->image, 0, 0);
}
