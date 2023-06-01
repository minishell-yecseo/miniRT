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
