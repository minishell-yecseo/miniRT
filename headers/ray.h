#ifndef RAY_H
# define RAY_H

#include "struct.h"

/*
typedef struct	s_ray
{
	t_vector	origin;
	t_vector	dir;
}	t_ray;

typedef struct	s_camera
{
	double		viewport_h;
	double		viewport_w;
	double		focal_len;
	double		fov;
	t_vector	origin;
	t_vector	dir;
	t_vector	right;
	t_vector	up;
	t_vector	lower_left_corner;
}	t_camera;
*/

t_ray		ray(t_vector origin, t_vector dir);
t_vector	ray_at(t_ray ray, double t);
t_camera	get_camera(t_vector origin, t_vector direction, double fov);

#endif
