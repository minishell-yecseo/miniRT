/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:05 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 15:04:29 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include "object.h"

t_vector	lighting(t_object *objs, t_ray r, t_hit_rec *rec);
t_vector	light_get(t_object *objs, t_ray r, t_hit_rec *rec, t_light light);
t_vector	get_specular(t_light light, t_hit_rec *rec, t_ray r, t_vector dir);
t_vector	get_diffuse(t_light light, t_hit_rec *rec, t_vector light_dir);
int			shadow(t_object *objs, t_ray r, t_light light, t_vector point);

#endif
