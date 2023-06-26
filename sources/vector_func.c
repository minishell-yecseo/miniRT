/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:03:11 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 15:03:11 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"

t_vector	vector(double x, double y, double z)
{
	t_vector	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void	vec_set_value(t_vector *vec, double x, double y, double z)
{
	vec->x = x;
	vec->y = y;
	vec->z = z;
}

double	vec_len_square(t_vector vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

double	vec_len(t_vector vec)
{
	double	square;

	square = vec_len_square(vec);
	if (fabs(square - 1) < EPSILON)
		return (1);
	return (sqrt(vec_len_square(vec)));
}

t_vector	vec_unit(t_vector vec)
{
	double	len;

	len = vec_len(vec);
	if (len < EPSILON)
	{
		printf("Error: div 0\n");
		exit(0);
	}
	vec.x /= len;
	vec.y /= len;
	vec.z /= len;
	return (vec);
}
