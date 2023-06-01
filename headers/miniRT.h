#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "ray.h"
# include "vector.h"

# define WIDTH 1200
# define HEIGHT 800

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

void	color_image(t_img *img, t_vars *vars);
int		get_color(t_vars *vars, double x, double y);
void	paint(t_img *img, int x, int y, int color);

int		destroy_window(t_vars *vars);
int		key_hook_esc(int keycode, t_vars *vars);

#endif
