#include "miniRT.h"

int	hit_co(t_object *co, t_ray r, t_hit_rec *rec)
{
	t_vector	H;
	t_vector	w;
	double		m;
	double		a;
	double		half_b;
	double		c;
	double		discriminant;
	double		root;

	H = vec_add(co->center, vec_mul(co->norm, co->height));
	w = vec_sub(r.origin, H);
	a = vec_len_square(r.dir) - ((m + 1) * vec_dot(r.dir, co->norm) * vec_dot(r.dir, co->norm));
	half_b = vec_dot(r.dir, w) - ((m + 1) * vec_dot(r.dir, co->norm) * vec_dot(w, co->norm));
	c = vec_len_square(w) - ((m + 1) * (vec_dot(w, co->norm) * vec_dot(w, co->norm)));

	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	root = (-half_b - (sqrt(discriminant))) / a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	t_vector	P = vec_add(r.origin, vec_mul(r.dir, root));
	double		test = vec_dot(vec_sub(P, co->center), co->norm);
	if (test < 0.0)
		return (0);
	rec->t = root;
	rec->point = ray_at(r, root);
	rec->normal = vec_unit(vec_sub(rec->point, co->center));
	set_face_normal(r, rec);
	return (1);
}
