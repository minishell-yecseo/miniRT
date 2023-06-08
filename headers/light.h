#include "vector.h"

typedef struct s_light
{
	t_vector	origin;
	t_vector	color;
	double		ratio;
}	t_light;

t_vector	lighting(t_light *lights);
