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

	cam.dir = vector(0, 0.5, -1);
	cam.fov = 70;
	cam.focal_len = 1;
	cam.viewport_h = 2 * tan(((cam.fov / 2) * (M_PI / 180)));
	cam.viewport_w = cam.viewport_h * WIDTH / HEIGHT;
	printf("%f\n", cam.focal_len);
	cam.origin = origin;
	if (vec_len(vec_cross(cam.dir, vector(0, 1, 0))))
		cam.right = vec_mul(vec_unit(vec_cross(cam.dir, vector(0, 1, 0))), cam.viewport_w);
	else
		cam.right = vec_mul(vec_unit(vec_cross(cam.dir, vector(0, 0, -1))), cam.viewport_w);
	cam.up = vec_mul(vec_unit(vec_cross(cam.right, cam.dir)), cam.viewport_h);
    tmp = vec_add(cam.origin, vec_mul(cam.dir, cam.focal_len));
	tmp = vec_add(tmp, vec_mul(cam.right, -0.5));
	tmp = vec_add(tmp, vec_mul(cam.up, -0.5));
	cam.lower_left_corner = tmp;

	printf("%f %f %f", cam.lower_left_corner.x, cam.lower_left_corner.y, cam.lower_left_corner.z);
	return (cam);
}
