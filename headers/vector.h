#ifndef VECTOR_H
# define VECTOR_H

# include <stdio.h>
# include <math.h>
# include <stdlib.h>

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

t_vector	vector(double x, double y, double z);
void		vec_set_value(t_vector *vec, double x, double y, double z);
double		vec_len_square(t_vector vec);
double		vec_len(t_vector vec);
t_vector	vec_add(t_vector vec1, t_vector vec2);
t_vector	vec_sub(t_vector vec1, t_vector vec2);
double		vec_dot(t_vector vec1, t_vector vec2);
t_vector	vec_cross(t_vector vec1, t_vector vec2);
t_vector	vec_unit(t_vector vec);
t_vector	vec_mul(t_vector vec1, double t);

#endif
