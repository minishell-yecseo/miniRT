#include "light.h"

t_vector	lighting(t_light *lights)
{
	t_vector	light_color;

	lights = (t_light *)malloc(sizeof(t_light) * 2);
	lights[0].color = vector(0.1, 0.9, 0.1);
	light_color = vector(0, 0, 0);
	light_color = vec_add(light_color, lights[0].color);
	return (vec_min(vec_mul(light_color, 0.4), vector(1, 1, 1)));
}
