/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_basics.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:06:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/25 16:50:08 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

t_pos	mult_scalar(t_pos vector, float mult)
{
	vector.x *= mult;
	vector.y *= mult;
	return (vector);
}

t_pos	add_vectors(t_pos a, t_pos b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}

t_pos	subtr_vectors(t_pos a, t_pos b)
{
	a.x -= b.x;
	a.y -= b.y;
	return (a);
}

t_pos	rotate_vector(t_pos vector, float angle)
{
	float	m_sin;
	float	m_cos;
	t_pos	result;

	m_sin = sin(angle);
	m_cos = cos(angle);
	result.x = m_cos * vector.x - m_sin * vector.y;
	result.y = m_sin * vector.x + m_cos * vector.y;
	return (result);
}

float	vector_length(t_pos vector)
{
	return (sqrtf(vector.x * vector.x + vector.y * vector.y));
}
