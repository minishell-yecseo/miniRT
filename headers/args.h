#ifndef ARGS_H
# define ARGS_H

# include <unistd.h>
# include <fcntl.h>
# include "get_next_line.h"
# include "struct.h"
# include "vector.h"
# include "ray.h"
# include "utils.h"

int		check_args(int argc, char **argv, t_scene *scene);
int		save(int fd, t_scene *scene);
void	init_contents_flags(int *flags, t_scene *scene, char *whitespaces);
int		save_contents(int fd, t_scene *scene, int *err_line);
int		save_line(t_scene *scene, char **split, int *flags);
int		save_ambient_light(t_scene *scene, char **split, int *flags);
int		save_lights(t_scene *scene, char **split, int *flags);
int		save_camera(t_scene *scene, char **split, int *flags);
int		save_objs(t_scene *scene, char **split);
int		is_obj_line(char *str);
int		save_sp(t_scene *scene, char **split);
int		save_pl(t_scene *scene, char **split);
int		save_cy(t_scene *scene, char **split);
int		save_objs_color(t_object *obj, char *color);

#endif
