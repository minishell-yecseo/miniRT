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

int	cy_cap(t_object *cy, t_ray r, t_hit_rec *rec, t_vector c)
{
	double	numrator;
	double	denominator;
	double	root;

	denominator = vec_dot(r.dir, vec_unit(cy->norm));
	if (fabs(denominator) < EPSILON )
		return (0);
	numrator = vec_dot(vec_sub(c, r.origin), vec_unit(cy->norm));
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	t_vector	P = vec_add(r.origin, vec_mul(r.dir, root));
	double		pc = vec_len(vec_sub(P, c));
	if (pc > cy->radius || pc < 0.0)
		return (0);
	rec->t = root;
	rec->tmax = root;
	rec->point = ray_at(r, root);
	rec->normal = cy->norm;
	return (1);
}

int	cy_side(t_object *cy, t_ray r, t_hit_rec *rec)
{
	double	a;
	double	half_b;
	double	c;
	double	discriminant;
	double	root;

	a = vec_len_square(vec_cross(r.dir, cy->norm));
	half_b = vec_dot(vec_cross(r.dir, cy->norm), vec_cross(vec_sub(r.origin, cy->center), cy->norm));
	c = vec_len_square(vec_cross(vec_sub(r.origin, cy->center), cy->norm)) - (cy->radius) * (cy->radius);
	discriminant = half_b * half_b - a * c;
	if (discriminant < 0)
		return (0);
	root = (-half_b - sqrt(discriminant)) / a;
	//if (root < rec->tmin || rec->tmax < root)
	{
		root = (-half_b + sqrt(discriminant)) / a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}

	t_vector	P = vec_add(r.origin, vec_mul(r.dir, root));
	double		qc = vec_dot(vec_sub(P, cy->center), cy->norm);
	if (qc > cy->height || qc < 0.0)
		return (0);
	rec->t = root;
	rec->tmax = root;
	rec->point = ray_at(r, root);
	rec->normal = get_cy_norm(cy, rec->point, qc);
	set_face_normal(r, rec);
	return (1);
}

int	hit_cy(t_object *cy, t_ray r, t_hit_rec *rec)
{
	int	is_hit;

	is_hit = 0;
	t_vector	H = vec_add(cy->center, vec_mul(vec_unit(cy->norm), cy->height));
	if (cy_cap(cy, r, rec, cy->center))
	{
		is_hit = 1;
		rec->normal = vec_mul(rec->normal, -1);
	}
	if (cy_cap(cy, r, rec, H))
		is_hit = 1;
	set_face_normal(r, rec);
	if (cy_side(cy, r, rec))
		is_hit = 1;
	if (is_hit)
		return (1);
	return (0);
}

int	hit_plane(t_object *pl, t_ray r, t_hit_rec *rec)
{
	double	numrator;
	double	denominator;
	double	root;

	denominator = vec_dot(r.dir, pl->norm);
	if (fabs(denominator) < EPSILON )
		return (0);
	numrator = vec_dot(vec_sub(pl->center, r.origin), pl->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	rec->t = root;
	rec->point = ray_at(r, root);
	rec->normal = pl->norm;

	t_vector u;
	t_vector v;
	if (vec_len(vec_cross(pl->norm, vector(0, 1, 0))))
		u = vec_unit(vec_cross(pl->norm, vector(0, 1, 0)));
	else
		u = vec_unit(vec_cross(pl->norm, vector(0, 0, -1)));
	v = vec_unit(vec_cross(u, pl->norm));

	rec->u = fmod(vec_dot(rec->point, u), 1);
	rec->v = fmod(vec_dot(rec->point, v), 1);
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
	c = vec_len_square(oc) - (sp->radius) * (sp->radius);
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
	rec->normal = vec_mul(vec_sub(rec->point, sp->center), 1 / (sp->radius));
	
	t_vector norm = rec->normal;
	
	rec->u = (atan2(-norm.z, norm.x) + M_PI) / (2 * M_PI);
	rec->v = acos(-norm.y) / M_PI;

	//rec->u = 1 - ((atan2(rec->point.x, rec->point.z)) / (2 * M_PI) + 0.5);
	//rec->v = 1 - acos(rec->point.y / sp->radius) / M_PI;
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
	return (0);
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
			if (objs[i].is_texture == 1)
			{
				int color = objs[i].texture.data[objs[i].texture.w * (int)(rec->v * objs[i].texture.h) + (int)(rec->u * objs[i].texture.w)];
				rec->albedo = get_vec_color(color);
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
