#include "miniRT.h"

void	get_cy_head_uv(t_hit_rec *rec, t_object *cy, int head)
{
	t_vector	u;
	t_vector	v;
	t_vector	p;

	p = vec_sub(rec->point, cy->center);
	u = vec_unit(vec_cross(cy->norm, vec_up(cy->norm)));
	v = vec_unit(vec_cross(u, cy->norm));
	rec->u = (atan2(-vec_dot(p, u), vec_dot(p, v)) + M_PI) / (2 * M_PI);
	if (head == 1)
		rec->v = 1;
	else
		rec->v = 0;
}

void	get_cy_uv(t_hit_rec *rec, t_object *cy)
{
	t_vector	u;
	t_vector	v;
	t_vector	p;
	t_vector	p_unit;

	p = vec_sub(rec->point, cy->center);
	u = vec_unit(vec_cross(cy->norm, vec_up(cy->norm)));
	v = vec_unit(vec_cross(u, cy->norm));
	rec->u = (atan2(-1 * vec_dot(p, u), vec_dot(p, v)) + M_PI) * 0.5 * M_1_PI;
	rec->v = vec_dot(p, cy->norm) / cy->height;
}
