#include "miniRT.h"

int	shadow(t_object *objs, t_ray r, t_light light, t_vector point)
{
	t_hit_rec rec;
	t_ray ray;

	r.origin = vec_add(point, vec_mul(vec_sub(light.origin, point), 0.01));
	r.dir = vec_unit(vec_sub(light.origin, point));
	rec.tmax = vec_len(vec_sub(light.origin, point));
	rec.tmin = 0.00000000001;

	if (is_hit(objs, r, &rec))
		return (1);	
	return (0);
}

t_vector	light_get(t_object *objs, t_ray r, t_hit_rec *rec, t_light light)
{
	t_vector	diffuse;
	t_vector	light_dir;
	t_vector	v;
	t_vector	re;
	double		k;
	double		spec_strength;
	double		spec;
	t_vector	specular;

	if (shadow(objs, r, light, rec->point))
	{
		return (vector(0, 0, 0));
	}
	light_dir = vec_unit(vec_sub(light.origin, rec->point));
	k = fmax(vec_dot(rec->normal, light_dir), 0.0); //* (1 / vec_len(vec_sub(light.origin, rec->point)));
	diffuse = vec_mul(light.color, k);

	v = vec_unit(vec_mul(r.dir, -1));
	re = vec_add(vec_mul(light_dir, -1), vec_mul(rec->normal ,vec_dot(light_dir, rec->normal) * 2));
	k = 128; // shininess value
	spec_strength = 1; // vec_len(vec_sub(light.origin, rec->point));
	spec = pow(fmax(vec_dot(v, re), 0.0), k);
	specular = vec_mul(vec_mul(light.color, spec_strength), spec);
	return (vec2_mul(vec_add(diffuse, specular), light.color));
}

t_vector	lighting(t_object *objs, t_ray r, t_hit_rec *rec)
{
	t_vector	light_color;
	t_light	*lights = rec->lights;
	t_vector get_light;
	int	is_shadow = 0;

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
			get_light = light_get(objs, r, rec, lights[i]);
			light_color = vec_add(light_color, get_light);
		}
		i++;
	}
	//if (is_shadow == 1)
	//{
	//	return (vector(0, 0, 0));
	//}

	return (vec_min(vec2_mul(light_color, rec->albedo), vector(1, 1, 1)));
}
