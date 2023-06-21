#ifndef STRUCT_H
# define STRUCT_H

# define OBJ_MAX 10001
# define CAM 0
# define AMBIENT 1
# define LIGHT 2
# define UINT_MAX 2147483647
# define REC_TMAX 1.7976931348623158e+308
# define EPSILON 1.11e-16
# define MAX 1.7976931348623158e+308
# define WIDTH 1200
# define HEIGHT 800

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
	
	int		*data;
	int		h;
	int		w;
	
	int		bits_per_pixel;
	int		size_len;
	int		endian;
}			t_img;

//for vector
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

enum e_surface_type
{
	COLOR,
	CHECKER,
	TEXTURE
};

typedef struct s_surface
{
	enum e_surface_type	type;
	int					x;
	int					y;
	int					is_bump;
	t_vector			color;
	t_vector			color2;
	t_img				texture;
	t_img				bump;
}	t_surface;

//formula
typedef struct s_formula
{
	double	a;
	double	b;
	double	c;
	double	discriminant;
	double	sqrtd;
	double	root;
	double	numrator;
	double	denominator;
}	t_formula;

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
enum e_object_type
{
	sp,
	pl,
	cy,
	co,
	ci
};

typedef struct s_object
{
	enum e_object_type	type;
	t_surface		surface;
	t_vector		center;
	t_vector		norm;
	double			radius;
	double			height;
}	t_object;

//light
enum light_type
{
	E_AMBIENT,
	E_LIGHT
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
	double		u;
	double		v;
	t_light		*lights;
	enum e_object_type	type;
}	t_hit_rec;

typedef struct s_scene
{
	int		objs_number;
	int		lights_number;
	t_camera	camera;
	t_object	objs[OBJ_MAX];
	t_light		lights[OBJ_MAX];
}	t_scene;

typedef struct s_vars
{
	void			*mlx;
	void			*win;
	t_img			img;
	t_scene			scene;
	struct s_color	color;
}			t_vars;

/*
   .rt format

   - surface (1~3) 
   	* MAND *
		color

   	* BONUS *
   		1. color [color]
		2. checker [color1] [color2]
		3. texture [texture.xpm] [bump.xpm]

   -objects
   	identifier surface center ...
		[Sphere]
			available token numbers : 5, 6
			sp surface center diameter

		[Plane]
			available token numbers : 5, 6
			pl surface center norm

		[Cylinder]
			available token number : 7, 8
			cy surface bottom_center axis diameter height

		[Cone]
			available token number : 7, 8
			co surface bottom_center axis diameter height

		[Circle]
			available token number : 7, 8
			ci surface center axis diameter width
*/

#endif
