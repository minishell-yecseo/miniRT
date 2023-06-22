#include "miniRT.h"

int	co_side(t_object *co, t_ray r, t_hit_rec *rec);
int	co_cap(t_object *co, t_ray r, t_hit_rec *rec);

int	is_in_cam(t_object *co, t_ray r)
{
	t_vector	cl;
	t_vector	o_norm;
	double		h_prime;
	double		r_prime;
	double		r_p_max;

	cl = vec_sub(r.origin, co->center);
	h_prime = vec_dot(cl, co->norm);
	if (h_prime > co->height || h_prime < 0.0)
		return (0);
	o_norm = vec_cross(cl, co->norm);
	r_prime = vec_len(o_norm);
	r_p_max = (co->radius * (co->height - h_prime)) / co->height;
	if (r_prime > r_p_max)
		return (0);
	return (1);
}

int	hit_co(t_object *co, t_ray r, t_hit_rec *rec)
{
	int	is_hit;

	is_hit = 0;
	if (co_cap(co, r, rec))
		is_hit = 1;
	set_face_normal(r, rec);
	if (co_side(co, r, rec))
		is_hit = 1;
	if (is_hit == 1)
		get_cy_uv(rec, co);
	return (is_hit);
}

int	co_cap(t_object *co, t_ray r, t_hit_rec *rec)
{
	double		denominator;
	double		numrator;
	double		root;
	double		pc;
	t_vector	p;

	denominator = vec_dot(r.dir, co->norm);
	if (fabs(denominator) < EPSILON)
		return (0);
	numrator = -vec_dot(vec_sub(r.origin, co->center), co->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	p = ray_at(r, root);
	pc = vec_len(vec_sub(co->center, p));
	if (pc > co->radius)
		return (0);
	rec->t = root;
	rec->tmax = root;
	rec->point = p;
	rec->normal = vec_mul(co->norm, -1);
	return (1);
}

int	co_side2(t_ray r, t_formula f, t_object *co, t_hit_rec *rec)
{
	t_vector	p;
	double		test;
	t_vector	q;
	t_vector	hp;
	t_vector	qp;

	if (f.root < rec->tmin || rec->tmax < f.root)
		return (1);
	p = ray_at(r, f.root);
	test = vec_dot(vec_sub(p, co->center), co->norm);
	if (test > co->height || test < EPSILON)
		return (1);
	rec->t = f.root;
	rec->point = ray_at(r, f.root);
	rec->tmax = f.root;
	q = vec_add(co->center, vec_mul(co->norm, test));
	hp = vec_sub(p, vec_add(co->center, vec_mul(co->norm, co->height)));
	qp = vec_sub(p, q);
	if (fabs(vec_len(hp)) < EPSILON || fabs(vec_len(qp)) < EPSILON)
		rec->normal = co->norm;
	else
		rec->normal = vec_unit(vec_cross(hp, vec_cross(hp, qp)));
	set_face_normal(r, rec);
	return (0);
}

int	co_side(t_object *co, t_ray r, t_hit_rec *rec)
{
	t_vector	h;
	t_vector	w;
	t_formula	f;
	double		m;

	h = vec_add(co->center, vec_mul(co->norm, co->height));
	w = vec_sub(r.origin, h);
	m = (co->radius * co->radius) / vec_len_square(vec_sub(co->center, h)) + 1;
	f.a = vec_len_square(r.dir) - (m * vec_dot(r.dir, co->norm) \
			* vec_dot(r.dir, co->norm));
	f.b = vec_dot(r.dir, w) - (m * vec_dot(r.dir, co->norm) \
		* vec_dot(w, co->norm));
	f.c = vec_len_square(w) - (m * (vec_dot(w, co->norm) \
		* vec_dot(w, co->norm)));
	f.discriminant = f.b * f.b - f.a * f.c;
	if (f.discriminant < EPSILON)
		return (0);
	if (is_in_cam(co, r))
		f.root = (-f.b + (sqrt(f.discriminant))) / f.a;
	else
		f.root = (-f.b - (sqrt(f.discriminant))) / f.a;
	if (co_side2(r, f, co, rec))
		return (0);
	return (1);
}
