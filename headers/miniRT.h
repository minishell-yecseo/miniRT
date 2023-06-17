#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"
# include "get_next_line.h"
# include "struct.h"
# include "vector.h"
# include "ray.h"
# include "object.h"

# define WIDTH 1200
# define HEIGHT 800

void	color_image(t_img *img, t_vars *vars);
int		get_color(t_vars *vars, double x, double y);
void	paint(t_img *img, int x, int y, int color);

int		destroy_window(t_vars *vars);
int		key_hook_esc(int keycode, t_vars *vars);

void	test(t_img *img, t_vars *vars);
int	hit_cylinder(t_object *cy, t_ray *ray, t_hit_rec *rec);
t_vector	get_vec_color(int color);

int	check_args(int argc, char **argv, t_scene *scene);
void	error_print(char *msg);

int	ft_strlen(char *str);

#endif
