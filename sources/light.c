#include "light.h"

int	shadow(t_object *objs, t_ray r, t_light light, t_vector point)
{
	t_hit_rec	rec;

	r.origin = vec_add(point, vec_mul(vec_sub(light.origin, point), 0.001));
	r.dir = vec_unit(vec_sub(light.origin, point));
	rec.tmax = vec_len(vec_sub(light.origin, point));
	rec.tmin = EPSILON;
	if (is_hit(objs, r, &rec))
		return (1);
	return (0);
}

t_vector	get_diffuse(t_light light, t_hit_rec *rec, t_vector light_dir)
{
	double		k;

	k = fmax(vec_dot(rec->normal, light_dir), 0.0);
	return (vec_mul(light.color, k));
}

t_vector	get_specular(t_light light, t_hit_rec *rec, t_ray r, t_vector dir)
{
	t_vector	v;
	t_vector	re;
	double		spec;
	double		k;

	v = vec_mul(dir, -1);
	re = vec_add(v, vec_mul(rec->normal, vec_dot(dir, rec->normal) * 2));
	v = vec_unit(vec_mul(r.dir, -1));
	k = 64;
	spec = pow(fmax(vec_dot(v, re), 0.0), k);
	return (vec_mul(vec_mul(light.color, 0.6), spec));
}

t_vector	light_get(t_object *objs, t_ray r, t_hit_rec *rec, t_light light)
{
	t_vector	light_dir;
	t_vector	diffuse;
	t_vector	specular;

	if (shadow(objs, r, light, rec->point))
		return (vector(0, 0, 0));
	light_dir = vec_unit(vec_sub(light.origin, rec->point));
	diffuse = get_diffuse(light, rec, light_dir);
	specular = get_specular(light, rec, r, light_dir);
	return (vec2_mul(vec_add(diffuse, specular), light.color));
}

t_vector	lighting(t_object *objs, t_ray r, t_hit_rec *rec)
{
	t_vector	light_color;
	t_vector	one_light;
	t_light		*lights;
	double		ratio;
	int			i;

	light_color = vector(0, 0, 0);
	lights = rec->lights;
	i = 0;
	while (lights[i].type != NO_LIGHT)
	{
		ratio = lights[i].ratio;
		if (lights[i].type == E_AMBIENT)
		{
			one_light = vec_mul(lights[i].color, ratio);
			light_color = vec_add(light_color, vec_mul(lights[i].color, ratio));
		}
		else if (lights[i].type == E_LIGHT)
		{
			one_light = light_get(objs, r, rec, lights[i]);
			light_color = vec_add(light_color, vec_mul(one_light, ratio));
		}
		i++;
	}
	return (vec_min(vec2_mul(light_color, rec->albedo), vector(1, 1, 1)));
}
