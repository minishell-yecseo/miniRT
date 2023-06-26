/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_func3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 14:58:20 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 14:58:20 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vec_min(t_vector vec1, t_vector vec2)
{
	t_vector	new;

	if (vec1.x > vec2.x)
		new.x = vec2.x;
	else
		new.x = vec1.x;
	if (vec1.y > vec2.y)
		new.y = vec2.y;
	else
		new.y = vec1.y;
	if (vec1.z > vec2.z)
		new.z = vec2.z;
	else
		new.z = vec1.z;
	return (new);
}

t_vector	vec2_mul(t_vector vec1, t_vector vec2)
{
	t_vector	vec;

	vec.x = vec1.x * vec2.x;
	vec.y = vec1.y * vec2.y;
	vec.z = vec1.z * vec2.z;
	return (vec);
}

t_vector	vec_up(t_vector vec)
{
	if (vec.x == 0 && vec.y == 1 && vec.z == 0)
		return (vector(0, 0, 1));
	else if (vec.x == 0 && vec.y == -1 && vec.z == 0)
		return (vector(0, 0, -1));
	return (vector(0, 1, 0));
}
