#ifndef RAY_H
# define RAY_H

# include "vector.h"
# include "miniRT.h"

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
	t_vector	origin;
	t_vector	horizontal;
	t_vector	vertical;
	t_vector	lower_left_corner;
}	t_camera;


t_ray		ray(t_vector origin, t_vector dir);
t_vector	ray_at(t_ray ray, double t);
t_camera	camera(t_vector origin);

#endif
