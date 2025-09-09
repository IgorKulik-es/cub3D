/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:56:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/09 16:53:06 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

float	cross_product(t_pos a, t_pos b)
{
	return (a.x * b.x + a.y * b.y);
}

float	vectors_angle(t_pos a, t_pos b)
{
	float	sine;

	sine = cross_product(a, b) / (vector_length(a) * vector_length(b));
	return (asinf(sine));
}

t_mode	determine_facing(float angle)
{
	angle = fmodf(angle, D_PI);
	if (angle < 0)
		angle += D_PI;

	if (7 * Q_PI <= angle || angle < Q_PI)
		return (WALK_BACK);
	if (Q_PI <= angle && angle < THQ_PI)
		return (WALK_LEFT);
	if (THQ_PI <= angle && angle < M_PI + Q_PI)
		return (WALK_FRONT);
	if (M_PI + Q_PI < angle && angle < D_PI - Q_PI)
		return (WALK_RIGHT);
}
