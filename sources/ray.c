#include "ray.h"
#include "math.h"

t_ray	ray(t_vector origin, t_vector dir)
{
	t_ray new;

	new.origin = origin;
	new.dir = dir;
	return (new);
}

t_vector	ray_at(t_ray ray, double t)
{
	t_vector	new;

	new = vec_add(ray.origin, vec_mul(ray.dir, t));
	return (new);
}

t_camera	camera(t_vector origin)
{
	t_camera cam;
	t_vector tmp;

	cam.dir = vector(0, 0, -1);
	cam.fov = 100;
	cam.focal_len = (float)WIDTH / 2 / tan((cam.fov / 2 * M_PI / 180));
	printf("focal_len : %f\n", cam.focal_len);
	cam.origin = origin;
	if (vec_len(vec_cross(cam.dir, vector(0, 1, 0))))
		cam.right = vec_unit(vec_cross(cam.dir, vector(0, 1, 0)));
	else
		cam.right = vec_unit(vec_cross(cam.dir, vector(0, 0, -1)));
	cam.up = vec_unit(vec_cross(cam.right, cam.dir));
    tmp = vec_add(cam.origin, vec_mul(cam.dir, cam.focal_len));
	tmp = vec_sub(tmp, vec_mul(cam.right, (float)(WIDTH / 2)));
	tmp = vec_sub(tmp, vec_mul(cam.up, (float)(HEIGHT / 2)));
	cam.lower_left_corner = tmp;

	printf("lower left corner : %f %f %f\n", cam.lower_left_corner.x, cam.lower_left_corner.y, cam.lower_left_corner.z);
	return (cam);
}
