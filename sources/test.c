#include "miniRT.h"
#include "ray.h"

t_vector ray_color(t_ray r)
{
    t_vector	unit_direction = vec_unit(r.dir);
    double t = 0.5 * (unit_direction.y + 1.0);
    
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
			double u = (double)x / (WIDTH);
			double v = (double)y / (HEIGHT);
			t_ray r = ray(cam.origin, vec_sub(vec_add(vec_mul(cam.horizontal, u), vec_add(cam.lower_left_corner, vec_mul(cam.vertical, v))), cam.origin));
			t_vector color = ray_color(r);
			paint(img, x, y, test_color(color));
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->image, 0, 0);
}
