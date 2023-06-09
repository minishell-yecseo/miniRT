#include "vector.h"

t_vector	vector(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void	vec_set_value(t_vector *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

double	vec_len_square(t_vector vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	vec_len(t_vector vec)
{
	return (sqrt(vec_len_square(vec)));
}

t_vector	vec_add(t_vector vec1, t_vector vec2)
{
	t_vector	vec;

	vec.x = vec1.x + vec2.x;
	vec.y = vec1.y + vec2.y;
	vec.z = vec1.z + vec2.z;
	return (vec);
}

t_vector	vec_sub(t_vector vec1, t_vector vec2)
{
	t_vector	vec;

	vec.x = vec1.x - vec2.x;
	vec.y = vec1.y - vec2.y;
	vec.z = vec1.z - vec2.z;
	return (vec);
}

t_vector	vec_mul(t_vector vec1, double t)
{
	t_vector	vec;

	vec.x = vec1.x * t;
	vec.y = vec1.y * t;
	vec.z = vec1.z * t;
	return (vec);
}

// 내적 
double	vec_dot(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

// 외적
t_vector	vec_cross(t_vector vec1, t_vector vec2)
{
	t_vector	vec;

	vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	vec.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (vec);
}

t_vector	vec_unit(t_vector vec)
{
	double	len;

	len = vec_len(vec);
	if (len == 0)
	{
		printf("Error: div 0\n");
		exit(0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}

t_vector	vec_min(t_vector vec1, t_vector vec2)
{
	t_vector	new;

	if (vec1.x > vec2.x)
		new.x = vec2.x;
	else
		new.x = vec1.x;
	if (vec1.y > vec2.y)
		new.y = vec2.y;
	else
		new.y = vec1.y;
	if (vec1.z > vec2.z)
		new.z = vec2.z;
	else
		new.z = vec1.z;
	return (new);
}

t_vector	vec2_mul(t_vector vec1, t_vector vec2)
{
	t_vector	vec;

	vec.x = vec1.x * vec2.x;
	vec.y = vec1.y * vec2.y;
	vec.z = vec1.z * vec2.z;
	return (vec);
}
