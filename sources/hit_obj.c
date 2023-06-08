#include "object.h"

void	set_face_normal(t_ray r, t_hit_rec *rec)
{
	rec->front_face = vec_dot(r.dir, rec->normal) < 0;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vec_mul(rec->normal, -1);
}

int	hit_cy(t_object *cy, t_ray r, t_hit_rec *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	root;

	a = vec_len_square(vec_cross(r.dir, cy->norm));
	half_b = vec_dot(vec_cross(r.dir, cy->norm), vec_cross(vec_sub(r.origin, cy->center), cy->norm));
	c = vec_len_square(vec_cross(vec_sub(r.origin, cy->center), cy->norm)) - cy->diameter * cy->diameter;
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	root = (-half_b - sqrt(discriminant)) / a;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	rec->t = root;
	rec->point = ray_at(r, root);
	rec->normal = cy->norm;
	set_face_normal(r, rec);
	return (1);
}

int	hit_plane(t_object *pl, t_ray r, t_hit_rec *rec)
{
	double	numrator;
	double	denominator;
	double	root;

	denominator = vec_dot(r.dir, pl->norm);
	if (fabs(denominator) < 0.0000000001 )
		return (0);
	numrator = vec_dot(vec_sub(pl->center, r.origin), pl->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	rec->t = root;
	rec->point = ray_at(r, root);
	rec->normal = pl->norm;
	set_face_normal(r, rec);
	return (1);
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
	rec->t = root;
	rec->point = ray_at(r, root);
	rec->normal = vec_mul(vec_sub(rec->point, sp->center), 1 / (sp->diameter));
	set_face_normal(r, rec);
	return (1);
}

int	hit_obj(t_object *obj, t_ray r, t_hit_rec *rec)
{
	if (obj->type == sp)
		return (hit_sphere(obj, r, rec));
	else if (obj->type == pl)
		return (hit_plane(obj, r, rec));
	else if (obj->type == cy)
		return (hit_cy(obj, r, rec));
	/*
	else if (obj->type == other)
		return (hit_other(obj, r));
	else
		return (0.0);
	*/
	return 0;
}

int	is_hit(t_object *objs, t_ray r, t_hit_rec *rec)
{
	int	is_hit;
	int	i = 0;

	is_hit = 0;
	while(objs[i].type != -1)
	{
		if (hit_obj(&objs[i], r, rec))
		{
			is_hit = 1;
			rec->color = objs[i].color;
			rec->tmax = rec->t;
		}
		i++;
	}
	return is_hit;
}
