#ifndef RAY_H
# define RAY_H

# include "struct.h"

t_ray		ray(t_vector origin, t_vector dir);
t_vector	ray_at(t_ray ray, double t);
t_camera	get_camera(t_vector origin, t_vector direction, double fov);

#endif
