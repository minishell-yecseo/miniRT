#include "miniRT.h"
#include <math.h>

void	set_face_normal(t_ray r, t_hit_rec *rec)
{
	rec->front_face = vec_dot(r.dir, rec->normal) < 0;
	if (rec->front_face)
		rec->normal = rec->normal;
	else
		rec->normal = vec_mul(rec->normal, -1);
}

t_vector	get_cy_norm(t_object *cy, t_vector at_point, double h)
{
	t_vector	hit_center;
	t_vector	normal;

	hit_center = vec_add(cy->center, vec_mul(cy->norm, h));
	normal = vec_sub(at_point, hit_center);
	return (vec_unit(normal));
}

int	hit_ci(t_object *ci, t_ray r, t_hit_rec *rec)
{
	//ci->center, ci->norm, ci->radius
	//1. ci->norm 과 P의 내적이 0인가?
	//2. CP벡터의 크기가 radius랑 일치하는가?
	t_vector	cl;
	t_vector	p;
	double		numrator;
	double		denominator;
	double		root;
	double		r_prime;

	denominator = vec_dot(ci->norm, r.dir);
	if (fabs(denominator) < EPSILON)
		return (0);
	cl = vec_sub(ci->center, r.origin);
	numrator = vec_dot(cl, ci->norm);
	root = numrator / denominator;
	p = ray_at(r, root);
	r_prime = vec_len(vec_sub(p, ci->center));
	if (fabs(r_prime - ci->radius) > ci->height)
		return (0);
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	rec->t = root;
	rec->tmax = root;
	rec->point = p;
	rec->normal = ci->norm;
	return (1);
}

int cy_cap(t_object *cy, t_ray r, t_hit_rec *rec, t_vector c)
{
	t_formula	f;
	t_vector	p;
	double		pc;

	f.denominator = vec_dot(r.dir, vec_unit(cy->norm));
	if (fabs(f.denominator) < EPSILON)
		return (0);
	f.numrator = vec_dot(vec_sub(c, r.origin), vec_unit(cy->norm));
	f.root = f.numrator / f.denominator;
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

int	cy_side(t_object *cy, t_ray r, t_hit_rec *rec)
{
	t_formula	f;
	t_vector	p;
	double		qc;

	f.a = vec_len_square(vec_cross(r.dir, cy->norm));
	f.b = vec_dot(vec_cross(r.dir, cy->norm), vec_cross(vec_sub(r.origin, cy->center), cy->norm));
	f.c = vec_len_square(vec_cross(vec_sub(r.origin, cy->center), cy->norm)) - (cy->radius) * (cy->radius);
	f.discriminant = f.b * f.b - f.a * f.c;
	if (f.discriminant < 0)
		return (0);
	f.root = (-f.b - sqrt(f.discriminant)) / f.a;
	if (f.root < rec->tmin || rec->tmax < f.root)
	{
		f.root = (-f.b + sqrt(f.discriminant)) / f.a;
		if (f.root < rec->tmin || rec->tmax < f.root)
			return (0);
	}
	p = vec_add(r.origin, vec_mul(r.dir, f.root));
	qc = vec_dot(vec_sub(p, cy->center), cy->norm);
	if (qc > cy->height || qc < 0.0)
		return (0);
	rec->t = f.root;
	rec->tmax = f.root;
	rec->point = ray_at(r, f.root);
	rec->normal = get_cy_norm(cy, rec->point, qc);
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
		is_hit = 1;
		rec->normal = vec_mul(rec->normal, -1);
	}
	if (cy_cap(cy, r, rec, h))
		is_hit = 1;
	if (cy_side(cy, r, rec))
		is_hit = 1;
	set_face_normal(r, rec);
	if (is_hit)
		return (1);
	return (0);
}

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

int	hit_obj(t_object *obj, t_ray r, t_hit_rec *rec)
{
	if (obj->type == sp)
		return (hit_sphere(obj, r, rec));
	else if (obj->type == pl)
		return (hit_plane(obj, r, rec));
	else if (obj->type == cy)
		return (hit_cy(obj, r, rec));
	else if (obj->type == co)
		return (hit_co(obj, r, rec));
	else if (obj->type == ci)
		return (hit_ci(obj, r, rec));
	return (0);
}

int	is_hit(t_object *objs, t_ray r, t_hit_rec *rec)
{
	int	is_hit;
	int	i;

	i = 0;
	is_hit = 0;
	while (objs[i].type != -1)
	{
		if (hit_obj(&objs[i], r, rec))
		{
			is_hit = 1;
			rec->color = objs[i].color;
			rec->tmax = rec->t;
			if (objs[i].is_texture == 1)
			{
				//texture
				int color = objs[i].texture.data[objs[i].texture.w * (int)((1 - rec->v) * objs[i].texture.h) + (int)(rec->u * objs[i].texture.w)];
				rec->albedo = get_vec_color(color);

				//bump map
				color = objs[i].bump.data[objs[i].bump.w * (int)((1 - rec->v) * objs[i].bump.h) + (int)(rec->u * objs[i].bump.w)];
				t_vector normal = vec_sub(vec_mul(get_vec_color(color), 2), vector(1, 1, 1));
				t_vector bump = vector(0, 0, 0);
				t_vector t = vec_unit(vec_cross(rec->normal, vec_up(rec->normal)));
				t_vector b = vec_unit(vec_cross(t, rec->normal));

				bump.x = t.x * normal.x + b.x * normal.y + rec->normal.x * normal.z;
				bump.y = t.y * normal.x + b.y * normal.y + rec->normal.y * normal.z;
				bump.x = t.z * normal.x + b.z * normal.y + rec->normal.z * normal.z;
				rec->normal = bump;	
			}
			else if (objs[i].checker.is_checker == 0)
				rec->albedo = objs[i].color;
			else
			{
				if (((int)floor(rec->u * objs[i].checker.x) + (int)floor(rec->v * objs[i].checker.y)) % 2 == 0)
					rec->albedo = objs[i].checker.color1;
				else
				{
					rec->albedo = objs[i].checker.color2;
				}
			}
		}
		i++;
	}
	return is_hit;
}
