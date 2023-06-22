#include "miniRT.h"
#include <math.h>

int	hit_obj(t_object *obj, t_ray r, t_hit_rec *rec)
{
	rec->type = obj->type;
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
	while (objs[i].type < 0)
	{
		if (hit_obj(&objs[i], r, rec))
		{
			surface = objs[i].surface;
			is_hit = set_hit_obj(surface, &texture, &bump, rec);
			if (surface.type == COLOR)
				rec->albedo = surface.color;
			else if (surface.type == TEXTURE)
				get_texture(rec, texture, bump, surface);
			else
				get_checker(rec, surface);
		}
		i++;
	}
	return (is_hit);
}
