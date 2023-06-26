/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_bonus.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:01 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 15:02:01 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_BONUS_H
# define ARGS_BONUS_H

# include <fcntl.h>
# include "get_next_line.h"
# include "mlx.h"
# include "struct.h"
# include "vector.h"
# include "ray.h"
# include "utils.h"

int		check_args(int argc, char **argv, t_vars *vars);
int		save(int fd, t_vars *vars);
void	init_contents_flags(int *flags, t_vars *vars, char *whitespaces);
int		save_contents(int fd, t_vars *vars, int *err_line);
int		save_line(t_vars *vars, char **split, int *flags);
int		save_ambient_light(t_vars *vars, char **split, int *flags);
int		save_lights(t_vars *vars, char **split);
int		save_camera(t_vars *vars, char **split, int *flags);
int		save_objs(t_vars *vars, char **split);
int		is_obj_line(char *str);
int		save_sp(t_vars *vars, char **split);
int		save_pl(t_vars *vars, char **split);
int		save_cy(t_vars *vars, char **split);
int		save_co(t_vars *vars, char **split);
int		save_ci(t_vars *vars, char **splt);
int		get_split_idx(int obj_type, char **split, int *ret);
int		save_objs_surface(t_vars *vars, t_object *obj, char **split);
int		save_objs_color(t_object *obj, char **split);
int		save_objs_checker(t_object *obj, char **split);
int		save_objs_texture(t_vars *vars, t_object *obj, char **split);
int		check_texture_files(t_surface *surface, char *texture, char *bump);

#endif
