#include "miniRT.h"

typedef struct s_formula
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
} t_formula;

int	cylinder_upper_cap(t_vector center, t_object *cy, t_ray *ray, t_hit_rec *rec)
{
	double	numrator;
	double	denominator;
	double	root;
	double	pc;

	denominator = vec_dot(ray->dir, cy->norm);
	if (fabs(denominator) < rec->tmin)
		return (0);
	numrator = vec_dot(vec_sub(center, ray->origin), cy->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	pc = vec_len(vec_sub(vec_add(ray->origin, vec_mul(ray->dir, root)), center));
	if ((pc * pc) > (cy->radius * cy->radius) || pc < 0.0)
		return (0);
	rec->t = root;
	rec->point = ray_at(*ray, root);
	rec->normal = cy->norm;
	set_face_normal(*ray, rec);
	return (1);
}

int	cylinder_lower_cap(t_vector center, t_object *cy, t_ray *ray, t_hit_rec *rec)
{
	double	numrator;
	double	denominator;
	double	root;
	double	pc;

	denominator = vec_dot(ray->dir, cy->norm);
	if (fabs(denominator) < rec->tmin)
		return (0);
	numrator = vec_dot(vec_sub(center, ray->origin), cy->norm);
	root = numrator / denominator;
	if (root < rec->tmin || root > rec->tmax)
		return (0);
	pc = vec_len(vec_sub(vec_add(ray->origin, vec_mul(ray->dir, root)), center));
	if ((pc * pc) > (cy->radius * cy->radius) || pc < 0.0)
		return (0);
	rec->t = root;
	rec->point = ray_at(*ray, root);
	rec->normal = vec_mul(cy->norm, -1);
	set_face_normal(*ray, rec);
	return (1);
}

int	cylinder_cap(t_object *cy, t_ray *ray, t_hit_rec *rec, double root)
{
	t_vector	PC;
	t_vector	H;
	double		condition;

	PC = vec_sub(vec_add(ray->origin, vec_mul(ray->dir, root)), cy->center);
	H = vec_mul(cy->norm, cy->height);
	condition = vec_dot(PC, H);
	if (condition < 0.0)
		return (cylinder_lower_cap(cy->center, cy, ray, rec));
	if (condition > cy->height)
		return (cylinder_upper_cap(vec_add(cy->center, vec_mul(cy->norm, cy->height)), cy, ray, rec));
	return (0);
}

int	cylinder_side(t_formula formula, t_object *cy, t_ray *ray, t_hit_rec *rec)
{
	double	root;
	double	qc;

	if (formula.discriminant < 0.0)
		return (0);
	root = (-formula.b - sqrt(formula.discriminant)) / formula.a;
	if (root < rec->tmin || rec->tmax < root)
	{
		root = (-formula.b + sqrt(formula.discriminant)) / formula.a;
		if (root < rec->tmin || rec->tmax < root)
			return (0);
	}
	qc = vec_dot(vec_sub(vec_add(ray->origin, vec_mul(ray->dir, root)), cy->center), cy->norm);
	if (qc > cy->height || qc < 0.0)
		return (cylinder_cap(cy, ray, rec, root));
	rec->t = root;
	rec->point = ray_at(*ray, root);
	rec->normal = vec_unit(vec_sub(vec_add(cy->center, vec_mul(cy->norm, qc)), \
	vec_add(ray->origin, vec_mul(ray->dir, root))));
	set_face_normal(*ray, rec);
	return (1);
}

void	get_cylinder_data(t_formula *formula, t_object *cy, t_ray *ray)
{
	t_vector	r_center;
	double		vh;
	double		wh;

	r_center = vec_sub(ray->origin, cy->center);
	vh = vec_dot(ray->dir, vec_unit(vec_mul(cy->norm, cy->height)));
	wh = vec_dot(r_center, vec_unit(vec_mul(cy->norm, cy->height)));
	formula->a = vec_dot(ray->dir, ray->dir) - (vh * vh);
	formula->b = vec_dot(ray->dir, r_center) - (vh * wh);
	formula->c = vec_dot(r_center, r_center) - (wh * wh) - (cy->radius * cy->radius);
	formula->discriminant = (formula->b * formula->b) - (formula->a * formula->c);
}

int	hit_cylinder(t_object *cy, t_ray *ray, t_hit_rec *rec)
{
	t_formula	formula;

	get_cylinder_data(&formula, cy, ray);
	return (cylinder_side(formula, cy, ray, rec));
}