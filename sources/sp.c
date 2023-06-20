#include "miniRT.h"

void	set_face_normal(t_ray r, t_hit_rec *rec)
{
	rec->front_face = vec_dot(r.dir, rec->normal) < 0;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vec_mul(rec->normal, -1);
}

int	hit_sphere(t_object *sp, t_ray r, t_hit_rec *rec)
{
	t_vector	oc;
	t_formula	f;

	oc = vec_sub(r.origin, sp->center);
	f.a = vec_len_square(r.dir);
	f.b = vec_dot(oc, r.dir);
	f.c = vec_len_square(oc) - (sp->radius) * (sp->radius);
	f.discriminant = f.b * f.b - f.a * f.c;
	if (f.discriminant < 0)
		return (0);
	f.sqrtd = sqrt(f.discriminant);
	f.root = (-f.b - f.sqrtd) / f.a;
	if (f.root < rec->tmin || rec->tmax < f.root)
	{
		f.root = (-f.b + f.sqrtd) / f.a;
		if (f.root < rec->tmin || rec->tmax < f.root)
			return (0);
	}
	rec->t = f.root;
	rec->point = ray_at(r, f.root);
	rec->normal = vec_mul(vec_sub(rec->point, sp->center), 1 / (sp->radius));
	rec->u = (atan2(-rec->normal.z, rec->normal.x) + M_PI) / (2 * M_PI);
	rec->v = acos(-rec->normal.y) / M_PI;
	set_face_normal(r, rec);
	return (1);
}