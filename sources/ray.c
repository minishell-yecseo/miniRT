#include "ray.h"

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

	cam.viewport_w = 2;
	cam.viewport_h = 2 * WIDTH / HEIGHT;
	cam.focal_len = 1;
	cam.origin = origin;
	cam.horizontal = vector(cam.viewport_w, 0, 0);
	cam.vertical = vector(0, cam.viewport_h, 0);
    cam.lower_left_corner = vec_sub(cam.origin, vec_add(vec_add(vec_mul(cam.horizontal, 0.5), vec_mul(cam.vertical, 0.5)), vector(0, 0, cam.focal_len)));
	return (cam);
}
