#include "miniRT.h"
#include "ray.h"


double	hit_sphere(t_vector center, double radius, t_ray r)
{
	t_vector oc = vec_sub(r.origin, center);
	double a = vec_dot(r.dir, r.dir);
	double half_b = vec_dot(oc, r.dir);
	double c = vec_len_square(oc) - radius * radius;
	double discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return -1;
	else
		return (-half_b - sqrt(discriminant) / a);
}

t_vector ray_color(t_ray r)
{
	double t = hit_sphere(vector(0, 0, -1), 0.5, r);
	if (t > 0)
	{
		t_vector N = vec_unit(vec_sub(ray_at(r, t), vector(0,0,-1)));
		return vec_mul(vector(N.x + 1, N.y + 1, N.z + 1), 0.5);
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

void	test(t_img *img, t_vars *vars)
{
	int			x;
	int			y;
	int			color;
	t_camera	cam;

	cam = camera(vector(0, 0, 0));
	mlx_clear_window(vars->mlx, vars->win);
	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			double u = (double)x / (double)(WIDTH);
			double v = (double)y / (double)(HEIGHT);
			t_ray r = ray(cam.origin, vec_sub(vec_add(vec_mul(cam.horizontal, u), vec_add(cam.lower_left_corner, vec_mul(cam.vertical, v))), cam.origin));
			t_vector color = ray_color(r);
			paint(img, x, y, test_color(color));
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->image, 0, 0);
}
