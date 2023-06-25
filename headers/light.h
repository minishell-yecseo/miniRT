#ifndef LIGHT_H
# define LIGHT_H

# include "object.h"

t_vector	lighting(t_object *objs, t_ray r, t_hit_rec *rec);
t_vector	light_get(t_object *objs, t_ray r, t_hit_rec *rec, t_light light);
t_vector	get_specular(t_light light, t_hit_rec *rec, t_ray r, t_vector dir);
t_vector	get_diffuse(t_light light, t_hit_rec *rec, t_vector light_dir);
int		shadow(t_object *objs, t_ray r, t_light light, t_vector point);

#endif
