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
# include "light.h"
# include "utils.h"

# define WIDTH 1200
# define HEIGHT 800

void	color_image(t_img *img, t_vars *vars);
int		get_color(t_vars *vars, double x, double y);
void	paint(t_img *img, int x, int y, int color);

int		destroy_window(t_vars *vars);
int		key_hook_esc(int keycode, t_vars *vars);

void	drawing(t_img *img, t_vars *vars);
int	hit_cylinder(t_object *cy, t_ray *ray, t_hit_rec *rec);
t_vector	get_vec_color(int color);

int	check_args(int argc, char **argv, t_vars *vars);
void	error_print(char *msg);
int	save_contents(int fd, t_vars *vars);
int	save_line(t_vars *vars, char **split, int *flags);
int	save_ambient_light(t_vars *vars, char **split, int *flags);
int	save_lights(t_vars *vars, char **split);
int	save_camera(t_vars *vars, char **split, int *flags);
int	save_objs(t_vars *vars, char **split);
int	is_obj_line(char *str);
int	save_sp(t_vars *vars, char **split);
int	save_pl(t_vars *vars, char **split);
int	save_cy(t_vars *vars, char **split);
int	save_co(t_vars *vars, char **split);
int	save_ci(t_vars *vars, char **splt);
int	get_split_idx(int obj_type, char **split, int *ret);
int	save_objs_surface(t_vars *vars, t_object *obj, char **split);
int	save_objs_color(t_object *obj, char **split);
int	save_objs_checker(t_object *obj, char **split);
int	save_objs_texture(t_vars *vars, t_object *obj, char **split);

int	check_color_range(t_vector *color);
int	check_norm_range(t_vector *norm);

int	height_check(t_object *obj, t_ray r, t_formula f, t_hit_rec *rec);

#endif
