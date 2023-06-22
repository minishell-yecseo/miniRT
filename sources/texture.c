#include "miniRT.h"

void	get_texture(t_hit_rec *rec, t_img tx, t_img bp, t_surface s)
{
	int			color;
	t_vector	normal;
	t_vector	tmp;
	t_vector	t;
	t_vector	b;

	color = tx.data[tx.w * (int)((1 - rec->v) * (tx.h - 1)) + \
			(int)(rec->u * tx.w)];
	rec->albedo = get_vec_color(color);
	if (s.is_bump != 0)
	{
		color = bp.data[bp.w * (int)((1 - rec->v) * bp.h) + \
				(int)(rec->u * bp.w)];
		normal = vec_sub(vec_mul(get_vec_color(color), 2), vector(1, 1, 1));
		tmp = vector(0, 0, 0);
		t = vec_unit(vec_cross(rec->normal, vec_up(rec->normal)));
		b = vec_unit(vec_cross(t, rec->normal));
		tmp.x = t.x * normal.x + b.x * normal.y + rec->normal.x * normal.z;
		tmp.y = t.y * normal.x + b.y * normal.y + rec->normal.y * normal.z;
		tmp.x = t.z * normal.x + b.z * normal.y + rec->normal.z * normal.z;
		rec->normal = tmp;
	}
}

void	set_checker_xy(t_surface *s, int x, int y)
{
	s->x = x;
	s->y = y;
}

void	get_checker(t_hit_rec *rec, t_surface s)
{
	if (rec->type == sp)
		set_checker_xy(&s, 20, 10);
	else if (rec->type == pl)
		set_checker_xy(&s, 2, 2);
	else if (rec->type == cy)
		set_checker_xy(&s, 16, 8);
	else if (rec->type == co)
		set_checker_xy(&s, 14, 8);
	if (((int)(rec->u * s.x) + (int)(rec->v * s.y)) % 2 == 0)
		rec->albedo = s.color;
	else
		rec->albedo = s.color2;
}
