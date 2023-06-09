#include "light.h"

t_vector	light_get(t_object *objs, t_ray r, t_hit_rec *rec, t_light light)
{
	t_vector	diffuse;
	t_vector	light_dir;
	double		kd;

	light_dir = vec_unit(vec_sub(light.origin, rec->point));
	kd = fmax(vec_dot(rec->normal, light_dir), 0.0);
	diffuse = vec_mul(light.color, kd);
	return (diffuse);
}

t_vector	lighting(t_object *objs, t_ray r, t_hit_rec *rec)
{
	t_vector	light_color;
	t_light	*lights = rec->lights;

	light_color = vector(0, 0, 0);
	int i = 0;
	while (lights[i].type != -1)
	{
		if (lights[i].type == ambient)
		{
			light_color = vec_add(light_color, vec_mul(lights[i].color, lights[i].ratio));
		}
		else if (lights[i].type == light)
		{
			light_color = vec_add(light_color, light_get(objs, r, rec, lights[i]));
		}
		i++;
	}

	return (vec_min(vec2_mul(light_color, rec->albedo), vector(1, 1, 1)));
}
