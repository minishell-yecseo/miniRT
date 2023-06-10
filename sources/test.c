#include "miniRT.h"
#include "ray.h"
#include "object.h"
#include "light.h"

t_vector ray_color(t_object *objs, t_ray r, t_hit_rec *rec)
{
	if (is_hit(objs, r, rec))
		return lighting(objs, r, rec); //return (vec_mul(vec_add(rec->normal, vector(1, 1, 1)), 0.5));

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

	objs[1].type = cy;
	objs[1].center = vector(-3, 0, -5);
	objs[1].color = vector(1, 1, 1);
	objs[1].diameter = 1;
	objs[1].norm = vec_unit(vector(0.5, 0, -1));
	objs[1].height = 2;

	objs[2].type = sp;
	objs[2].center = vector(0, 0, -1.5);
	objs[2].color = vector(1, 0, 1);
	objs[2].diameter = 0.5;

	objs[3].type = sp;
	objs[3].center = vector(0.4, 0, -1);
	objs[3].color = vector(0.1, 0.2, 0.6);
	objs[3].diameter = 0.25;
	
	objs[4].type = -1;
}

void	set_light(t_light *lights)
{
	lights[0].type = ambient;
	lights[0].color = vector(1, 1, 1);
	lights[0].ratio = 0.2;

	lights[1].type = light;
	lights[1].origin = vector(0, 5, 0);
	lights[1].ratio = 0.5;
	lights[1].color = vector(1, 1, 1);

	lights[2].type = -1;
}

void	test(t_img *img, t_vars *vars)
{
	int			x;
	int			y;
	int			color;
	t_camera	cam;
	t_object	objs[100];
	t_light		lights[100];
	t_hit_rec	rec;

	rec.tmin = 0.00000001;

	cam = camera(vector(0, 0, 0));
	mlx_clear_window(vars->mlx, vars->win);

	set_two_spheres(objs);
	set_light(lights);

	rec.lights = lights;
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
