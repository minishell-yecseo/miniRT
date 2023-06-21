#include "miniRT.h"

void	get_plane_uv(t_hit_rec *rec, t_object *pl)
{
	t_vector	u;
	t_vector	v;

	if (vec_len(vec_cross(pl->norm, vector(0, 1, 0))))
		u = vec_unit(vec_cross(pl->norm, vector(0, 1, 0)));
	else
		u = vec_unit(vec_cross(pl->norm, vector(0, 0, -1)));
	v = vec_unit(vec_cross(u, pl->norm));
	rec->u = fmod(vec_dot(rec->point, u), 1);
	rec->v = fmod(vec_dot(rec->point, v), 1);
}

int	hit_plane(t_object *pl, t_ray r, t_hit_rec *rec)
{
	t_formula	f;

	f.denominator = vec_dot(r.dir, pl->norm);
	if (fabs(f.denominator) < EPSILON)
		return (0);
	f.numrator = vec_dot(vec_sub(pl->center, r.origin), pl->norm);
	f.root = f.numrator / f.denominator;
	if (f.root < rec->tmin || f.root > rec->tmax)
		return (0);
	rec->t = f.root;
	rec->point = ray_at(r, f.root);
	rec->normal = pl->norm;
	get_plane_uv(rec, pl);
	set_face_normal(r, rec);
	return (1);
}

int	hit_ci(t_object *ci, t_ray r, t_hit_rec *rec)
{
	t_vector	cl;
	t_vector	p;
	t_formula	f;
	double		r_prime;

	f.denominator = vec_dot(ci->norm, r.dir);
	if (fabs(f.denominator) < EPSILON)
		return (0);
	cl = vec_sub(ci->center, r.origin);
	f.numrator = vec_dot(cl, ci->norm);
	f.root = f.numrator / f.denominator;
	p = ray_at(r, f.root);
	r_prime = vec_len(vec_sub(p, ci->center));
	if (fabs(r_prime - ci->radius) > ci->height)
		return (0);
	if (f.root < rec->tmin || f.root > rec->tmax)
		return (0);
	rec->t = f.root;
	rec->tmax = f.root;
	rec->point = p;
	rec->normal = ci->norm;
	return (1);
}
