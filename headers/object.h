/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:57:06 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 14:57:06 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_H
# define OBJECT_H

# include "struct.h"
# include "vector.h"
# include "ray.h"

/*
enum object_type
{
	sp,
	pl,
	sy,
	other
};

typedef struct s_object
{
	enum object_type	type;
	t_vector			center;
	t_vector			norm;
	t_vector			color;
	double				diameter;
	double				height;
}	t_object;
*/

int		hit_obj(t_object *obj, t_ray r, t_hit_rec *rec);
int		hit_cy(t_object *cy, t_ray r, t_hit_rec *rec);
int		hit_sphere(t_object *sp, t_ray r, t_hit_rec *rec);
int		hit_co(t_object *co, t_ray r, t_hit_rec *rec);
int		is_hit(t_object *objs, t_ray r, t_hit_rec *rec);
void	get_plane_uv(t_hit_rec *rec, t_object *pl);
void	set_face_normal(t_ray r, t_hit_rec *rec);
int		hit_ci(t_object *ci, t_ray r, t_hit_rec *rec);
int		hit_plane(t_object *pl, t_ray r, t_hit_rec *rec);
int		hit_cylinder(t_object *cy, t_ray *ray, t_hit_rec *rec);
void	get_cy_uv(t_hit_rec *rec, t_object *cy);
void	get_cy_head_uv(t_hit_rec *rec, t_object *cy, int head);
void	get_texture(t_hit_rec *rec, t_img tx, t_img bp, t_surface s);
void	set_checker_xy(t_surface *s, int x, int y);
void	get_checker(t_hit_rec *rec, t_surface s);

#endif
