/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:12 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 15:02:12 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

# include "struct.h"
# include <stdio.h>
# include <math.h>
# include <stdlib.h>

/*
typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;
*/

t_vector	vector(double x, double y, double z);
void		vec_set_value(t_vector *vec, double x, double y, double z);
double		vec_len_square(t_vector vec);
double		vec_len(t_vector vec);
t_vector	vec_add(t_vector vec1, t_vector vec2);
t_vector	vec_sub(t_vector vec1, t_vector vec2);
double		vec_dot(t_vector vec1, t_vector vec2);
t_vector	vec_cross(t_vector vec1, t_vector vec2);
t_vector	vec_unit(t_vector vec);
t_vector	vec_mul(t_vector vec1, double t);
t_vector	vec_min(t_vector vec1, t_vector vec2);
t_vector	vec2_mul(t_vector vec1, t_vector vec2);
t_vector	vec_up(t_vector vec);

#endif
