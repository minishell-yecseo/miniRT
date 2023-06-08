#include "object.h"

void	set_face_normal(t_ray r, t_hit_rec *rec)
{
	rec->front_face = vec_dot(r.dir, rec->normal) < 0;
	rec->normal = (rec->front_face) ? rec->normal : vec_mul(rec->normal, -1);
}

int	hit_obj(t_object *obj, t_ray r, t_hit_rec *rec)
{
	if (obj->type == sp)
		return (hit_sphere(obj, r, rec));
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
	return 0;
}

int	hit_sphere(t_object *sp, t_ray r, t_hit_rec *rec)
{
	t_vector	oc;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		sqrtd;
	double		root;

	oc = vec_sub(r.origin, sp->center);
	a = vec_len_square(r.dir);
	half_b = vec_dot(oc, r.dir);
	c = vec_len_square(oc) - sp->diameter * sp->diameter;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	
	sqrtd = sqrt(discriminant);
	root = (-half_b - sqrtd) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrtd) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	rec->tmax = root;
	rec->t = root;
	rec->point = ray_at(r, root);
	rec->normal = vec_mul(vec_sub(rec->point, sp->center), 1 / (sp->diameter));
	set_face_normal(r, rec);
	return (1);
}

int	is_hit(t_object *objs, t_ray r, t_hit_rec *rec)
{
	int	is_hit;
	int	i = 0;

	is_hit = 0;
	while(objs[i].type != -1)
	{
		if (hit_obj(&objs[i], r, rec))
			is_hit = 1;
		i++;
	}
	return is_hit;
}
