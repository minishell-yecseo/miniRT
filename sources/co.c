/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   co.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:02:42 by yecnam            #+#    #+#             */
/*   Updated: 2023/06/26 16:26:43 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT.h"

static int	co_side(t_object *co, t_ray r, t_hit_rec *rec);
static int	co_condition(t_ray r, t_formula f, t_object *co, t_hit_rec *rec);
static int	co_cap(t_object *co, t_ray r, t_hit_rec *rec);

int	is_in_cam(t_object *co, t_ray r)
{
	t_vector	cl;
	t_vector	o_norm;
	double		h_prime;
	double		r_prime;
	double		r_p_max;

	cl = vec_sub(r.origin, co->center);
	h_prime = vec_dot(cl, co->norm);
	if (h_prime > co->height || h_prime < 0.0)
		return (0);
	o_norm = vec_cross(cl, co->norm);
	r_prime = vec_len(o_norm);
	r_p_max = (co->radius * (co->height - h_prime)) / co->height;
	if (r_prime > r_p_max)
		return (0);
	return (1);
}

int	hit_co(t_object *co, t_ray r, t_hit_rec *rec)
{
	int	is_hit;

	is_hit = 0;
	if (co_cap(co, r, rec))
		is_hit = 1;
	set_face_normal(r, rec);
	if (co_side(co, r, rec))
		is_hit = 1;
	if (is_hit == 1)
		get_cy_uv(rec, co);
	return (is_hit);
}

int	co_cap(t_object *co, t_ray r, t_hit_rec *rec)
{
	t_formula	f;
	double		pc;
	t_vector	point;

	f.denominator = vec_dot(r.dir, co->norm);
	if (fabs(f.denominator) < EPSILON)
		return (0);
	f.numerator = -vec_dot(vec_sub(r.origin, co->center), co->norm);
	f.root = f.numerator / f.denominator;
	if (f.root < rec->tmin || f.root > rec->tmax)
		return (0);
	point = ray_at(r, f.root);
	pc = vec_len(vec_sub(co->center, point));
	if (pc > co->radius)
		return (0);
	rec->t = f.root;
	rec->tmax = f.root;
	rec->point = point;
	rec->normal = vec_mul(co->norm, -1);
	return (1);
}



int	co_condition(t_ray r, t_formula f, t_object *co, t_hit_rec *rec)
{
	t_vector	p;
	double		height;
	t_vector	q;
	t_vector	hp;
	t_vector	qp;

	if (f.root < rec->tmin || rec->tmax < f.root)
		return (0);
	p = ray_at(r, f.root);
	height = vec_dot(vec_sub(p, co->center), co->norm);
	if (height > co->height || height < 0)
		return (0);
	rec->t = f.root;
	rec->point = p;
	rec->tmax = f.root;
	q = vec_add(co->center, vec_mul(co->norm, height));
	hp = vec_sub(p, vec_add(co->center, vec_mul(co->norm, co->height)));
	qp = vec_sub(q, p);
	if (vec_len(hp) < EPSILON || vec_len(qp) < EPSILON)
		rec->normal = co->norm;
	else
		rec->normal = vec_unit(vec_cross(hp, vec_cross(hp, qp)));
	set_face_normal(r, rec);
	return (1);
}

int	co_side(t_object *co, t_ray r, t_hit_rec *rec)
{
	t_vector	h;
	t_vector	w;
	t_formula	f;
	double		m;

	h = vec_add(co->center, vec_mul(co->norm, co->height));
	w = vec_sub(r.origin, h);
	m = (co->radius * co->radius) / vec_len_square(vec_sub(co->center, h)) + 1;
	f.a = vec_len_square(r.dir) - (m * vec_dot(r.dir, co->norm) \
			* vec_dot(r.dir, co->norm));
	f.b = vec_dot(r.dir, w) - (m * vec_dot(r.dir, co->norm) \
		* vec_dot(w, co->norm));
	f.c = vec_len_square(w) - (m * (vec_dot(w, co->norm) \
		* vec_dot(w, co->norm)));
	f.discriminant = f.b * f.b - f.a * f.c;
	if (f.discriminant < EPSILON)
		return (0);
	if (is_in_cam(co, r))
		f.root = (-f.b + (sqrt(f.discriminant))) / f.a;
	else
		f.root = (-f.b - (sqrt(f.discriminant))) / f.a;
	if (!co_condition(r, f, co, rec))
		return (0);
	return (1);
}
