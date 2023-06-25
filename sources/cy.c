#include "miniRT.h"

t_vector	get_cy_norm(t_object *cy, t_vector at_point, double h)
{
	t_vector	hit_center;
	t_vector	normal;

	hit_center = vec_add(cy->center, vec_mul(cy->norm, h));
	normal = vec_sub(at_point, hit_center);
	return (vec_unit(normal));
}

int	cy_cap(t_object *cy, t_ray r, t_hit_rec *rec, t_vector c)
{
	t_formula	f;
	t_vector	p;
	double		pc;

	f.denominator = vec_dot(r.dir, vec_unit(cy->norm));
	if (fabs(f.denominator) < EPSILON)
		return (0);
	f.numerator = vec_dot(vec_sub(c, r.origin), vec_unit(cy->norm));
	f.root = f.numerator / f.denominator;
	if (f.root < rec->tmin || f.root > rec->tmax)
		return (0);
	p = vec_add(r.origin, vec_mul(r.dir, f.root));
	pc = vec_len(vec_sub(p, c));
	if (pc > cy->radius || pc < 0.0)
		return (0);
	rec->t = f.root;
	rec->tmax = f.root;
	rec->point = ray_at(r, f.root);
	rec->normal = cy->norm;
	return (1);
}

int	height_check(t_object *obj, t_ray r, t_formula f, t_hit_rec *rec)
{
	t_vector	p;
	double		qc;

	p = vec_add(r.origin, vec_mul(r.dir, f.root));
	qc = vec_dot(vec_sub(p, obj->center), obj->norm);
	if (qc > obj->height || qc < 0.0)
		return (1);
	rec->t = f.root;
	rec->tmax = f.root;
	rec->point = ray_at(r, f.root);
	rec->normal = get_cy_norm(obj, rec->point, qc);
	return (0);
}

int	cy_side(t_object *cy, t_ray r, t_hit_rec *rec)
{
	t_formula	f;

	f.a = vec_len_square(vec_cross(r.dir, cy->norm));
	f.b = vec_dot(vec_cross(r.dir, cy->norm), \
		vec_cross(vec_sub(r.origin, cy->center), cy->norm));
	f.c = vec_len_square(vec_cross(\
		vec_sub(r.origin, cy->center), cy->norm)) - (cy->radius) * (cy->radius);
	f.discriminant = f.b * f.b - f.a * f.c;
	if (f.discriminant < EPSILON)
		return (0);
	f.root = (-f.b - sqrt(f.discriminant)) / f.a;
	if (f.root < rec->tmin || rec->tmax < f.root)
	{
		f.root = (-f.b + sqrt(f.discriminant)) / f.a;
		if (f.root < rec->tmin || rec->tmax < f.root)
			return (0);
	}
	if (height_check(cy, r, f, rec))
		return (0);
	return (1);
}

int	hit_cy(t_object *cy, t_ray r, t_hit_rec *rec)
{
	t_vector	h;
	int			is_hit;

	is_hit = 0;
	h = vec_add(cy->center, vec_mul(vec_unit(cy->norm), cy->height));
	if (cy_cap(cy, r, rec, cy->center))
	{
		is_hit = 2;
		rec->normal = vec_mul(rec->normal, -1);
	}
	if (cy_cap(cy, r, rec, h))
		is_hit = 1;
	if (is_hit)
		get_cy_head_uv(rec, cy, is_hit);
	if (cy_side(cy, r, rec))
	{
		get_cy_uv(rec, cy);
		is_hit = 1;
	}
	set_face_normal(r, rec);
	if (is_hit)
		return (1);
	return (0);
}
