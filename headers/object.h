#ifndef OBJECT_H
# define OBJECT_H

# include "struct.h"
# include "vector.h"
# include "ray.h"

/*
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
*/

int	hit_obj(t_object *obj, t_ray r, t_hit_rec *rec);
int	hit_sphere(t_object *sp, t_ray r, t_hit_rec *rec);
int	is_hit(t_object *objs, t_ray r, t_hit_rec *rec);

void	set_face_normal(t_ray r, t_hit_rec *rec);

#endif
