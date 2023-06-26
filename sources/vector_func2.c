/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_func2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:58:19 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 14:58:19 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vec_add(t_vector vec1, t_vector vec2)
{
	t_vector	vec;

	vec.x = vec1.x + vec2.x;
	vec.y = vec1.y + vec2.y;
	vec.z = vec1.z + vec2.z;
	return (vec);
}

t_vector	vec_sub(t_vector vec1, t_vector vec2)
{
	t_vector	vec;

	vec.x = vec1.x - vec2.x;
	vec.y = vec1.y - vec2.y;
	vec.z = vec1.z - vec2.z;
	return (vec);
}

t_vector	vec_mul(t_vector vec1, double t)
{
	t_vector	vec;

	vec.x = vec1.x * t;
	vec.y = vec1.y * t;
	vec.z = vec1.z * t;
	return (vec);
}

// 내적 
double	vec_dot(t_vector vec1, t_vector vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

// 외적
t_vector	vec_cross(t_vector vec1, t_vector vec2)
{
	t_vector	vec;

	vec.x = vec1.y * vec2.z - vec1.z * vec2.y;
	vec.y = vec1.z * vec2.x - vec1.x * vec2.z;
	vec.z = vec1.x * vec2.y - vec1.y * vec2.x;
	return (vec);
}
