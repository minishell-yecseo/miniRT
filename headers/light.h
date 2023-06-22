#ifndef LIGHT_H
# define LIGHT_H

# include "vector.h"

t_vector	lighting(t_object *objs, t_ray r, t_hit_rec *rec);

#endif
