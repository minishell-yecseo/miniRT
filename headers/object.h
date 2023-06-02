#ifndef OBJECT_H
# define OBJECT_H

#include "vector.h"

enum object_type
{
	sp,
	pl,
	sy,
	other
};

typedef struct s_object
{
	enum object_type	type;
	t_vector			center;
	t_vector			norm;
	t_vector			color;
	double				diameter;
	double				height;
}	t_object;

double	hit_obj(t_object *obj, t_ray r);
double	hit_sphere(t_object *sp, t_ray r);

#endif
