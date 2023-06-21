#include "miniRT.h"
#include <math.h>

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

void	get_texture(t_hit_rec *rec, t_img tx, t_img bp)
{
	int			color;
	t_vector	normal;
	t_vector	tmp;
	t_vector	t;
	t_vector	b;

	color = tx.data[tx.w * (int)((1 - rec->v) * tx.h) + (int)(rec->u * tx.w)];
	rec->albedo = get_vec_color(color);
	color = bp.data[bp.w * (int)((1 - rec->v) * bp.h) + (int)(rec->u * bp.w)];
	normal = vec_sub(vec_mul(get_vec_color(color), 2), vector(1, 1, 1));
	tmp = vector(0, 0, 0);
	t = vec_unit(vec_cross(rec->normal, vec_up(rec->normal)));
	b = vec_unit(vec_cross(t, rec->normal));
	tmp.x = t.x * normal.x + b.x * normal.y + rec->normal.x * normal.z;
	tmp.y = t.y * normal.x + b.y * normal.y + rec->normal.y * normal.z;
	tmp.x = t.z * normal.x + b.z * normal.y + rec->normal.z * normal.z;
	rec->normal = tmp;
}

void	get_checker(t_hit_rec *rec, t_surface s)
{
	if (((int)floor(rec->u * s.x) + (int)floor(rec->v * s.y)) % 2 == 0)
		rec->albedo = s.color;
	else
		rec->albedo = s.color2;
}

int	set_hit_obj(t_surface surface, t_img *t, t_img *b, t_hit_rec *rec)
{
	*t = surface.texture;
	*b = surface.bump;
	rec->color = surface.color;
	rec->tmax = rec->t;
	return (1);
}

int	is_hit(t_object *objs, t_ray r, t_hit_rec *rec)
{
	t_surface	surface;
	t_img		texture;
	t_img		bump;
	int			is_hit;
	int			i;

	i = 0;
	is_hit = 0;
	while (objs[i].type != -1)
	{
		if (hit_obj(&objs[i], r, rec))
		{
			surface = objs[i].surface;
			is_hit = set_hit_obj(surface, &texture, &bump, rec);
			if (surface.type == COLOR)
				rec->albedo = surface.color;
			else if (surface.type == TEXTURE)
				get_texture(rec, texture, bump);
			else
				get_checker(rec, surface);
		}
		i++;
	}
	return (is_hit);
}
