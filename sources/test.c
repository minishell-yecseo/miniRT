#include "miniRT.h"
#include "ray.h"
#include "object.h"
#include "light.h"

t_vector ray_color(t_object *objs, t_ray r, t_hit_rec *rec)
{
	if (is_hit(objs, r, rec))
		return rec->color; //return (vec_mul(vec_add(rec->normal, vector(1, 1, 1)), 0.5));

	//sky
	double t;
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
	//plane
	objs[0].type = pl;
	objs[0].center = vector(0, 0, -100000);
	objs[0].color = vector(0, 0.4, 0.4);
	objs[0].norm = vector(0, 90, 1);

	objs[1].type = sp;
	objs[1].center = vector(0, 0, -2);
	objs[1].color = vector(0, 0.2, 0);
	objs[1].diameter = 0.5;

	//objs[1].type = sp;
	//objs[1].center = vector(0.3, 0, -2);
	//objs[1].color = vector(10, 255, 100);
	//objs[1].diameter = 0.5;
	objs[2].type = -1;

	// make two spheres

	//objs[0].type = sp;
	//objs[0].center = vector(-0.5, 0, -1);
	//objs[0].color = vector(256, 0, 0);
	//objs[0].diameter = 0.5;

	//objs[1].type = sp;
	//objs[1].center = vector(0.3, 0, -2);
	//objs[1].color = vector(10, 255, 100);
	//objs[1].diameter = 0.5;

	//objs[2].type = -1;
}

void	test(t_img *img, t_vars *vars)
{
	int			x;
	int			y;
	int			color;
	t_camera	cam;
	t_object	objs[3];
	t_hit_rec	rec;

	rec.tmin = 0.00000001;

	cam = camera(vector(0, 0, 0));
	mlx_clear_window(vars->mlx, vars->win);

	set_two_spheres(objs);
	y = HEIGHT - 1;
	while (--y >= 0)
	{
		x = -1;
		while (++x < WIDTH)
		{
			rec.tmax = 1.7976931348623158e+308;
			double u = (double) x;
			double v = (double) y;
			t_ray r = ray(cam.origin, vec_unit(vec_sub(vec_add(vec_mul(cam.right, u), vec_add(cam.lower_left_corner, vec_mul(cam.up, v))), cam.origin)));
			//printf("(%d, %d)-ray dir : (%f, %f, %f)\n", x, y, r.dir.x, r.dir.y, r.dir.z);
			t_vector color = ray_color(objs, r, &rec);
			paint(img, x, y, test_color(color));
		}
	}
	mlx_put_image_to_window(vars->mlx, vars->win, img->image, 0, 0);
}
