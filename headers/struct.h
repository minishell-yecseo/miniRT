#ifndef STRUCT_H
# define STRUCT_H

//for mlx window drawing
typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}			t_color;

typedef struct s_img
{
	void	*image;
	int		bits_per_pixel;
	int		size_len;
	int		endian;
}			t_img;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_img			img;
	struct s_color	color;
}			t_vars;

//for vector
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

//for ray, camera
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

//for multiple objeects
enum object_type
{
	sp,
	pl,
	cy,
	co
};

typedef struct s_object
{
	enum object_type	type;
	t_vector			center;
	t_vector			norm;
	t_vector			color;
	double				radius;
	double				height;
	t_vector			albedo;
}	t_object;

//light
enum light_type
{
	ambient,
	light
};

typedef struct s_light
{
	enum light_type	type;
	t_vector		origin;
	t_vector		color;
	double			ratio;
}	t_light;

//hit_rec
typedef struct s_hit_rec
{
	t_vector	point;
	t_vector	normal;
	double		tmin;
	double		tmax;
	double		t;
	int			front_face;
	t_vector	color;
	t_vector	albedo;
	t_light		*lights;
}	t_hit_rec;

#endif