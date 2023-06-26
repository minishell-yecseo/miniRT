/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:57:03 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 14:57:03 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../mlx/mlx.h"
# include "struct.h"
# include "vector.h"
# include "ray.h"
# include "object.h"
# include "light.h"

# define WIDTH 1200
# define HEIGHT 800

void		color_image(t_img *img, t_vars *vars);
int			get_color(double x, double y);
void		paint(t_img *img, int x, int y, int color);

int			destroy_window(t_vars *vars);
int			key_hook_esc(int keycode, t_vars *vars);

void		drawing(t_img *img, t_vars *vars);
int			hit_cylinder(t_object *cy, t_ray *ray, t_hit_rec *rec);
t_vector	get_vec_color(int color);

int			height_check(t_object *obj, \
			t_ray r, t_formula f, t_hit_rec *rec);

#endif
