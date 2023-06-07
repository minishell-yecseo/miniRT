#include "object.h"

double	hit_obj(t_object *obj, t_ray r)
{
	if (obj->type == sp)
		return (hit_sphere(obj, r));
	/*
	else if (obj->type == pl)
		return (hit_plane(obj, r));
	else if (obj->type == sy)
		return (hit_sy(obj, r));
	else if (obj->type == other)
		return (hit_other(obj, r));
	else
		return (0.0);
	*/
}

double	hit_sphere(t_object *sp, t_ray r)
{
	t_vector	oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;

	oc = vec_sub(r.origin, sp->center);
	a = vec_dot(r.dir, r.dir);
	half_b = vec_dot(oc, r.dir);
	c = vec_len_square(oc) - sp->diameter * sp->diameter;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (-1);
	return (-half_b - sqrt(discriminant) / a);
}
