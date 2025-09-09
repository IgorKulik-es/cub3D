/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:56:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/09 19:12:21 by ikulik           ###   ########.fr       */
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
	return (acosf(sine));
}

t_mode	determine_facing(t_entity *guy)
{
	float	angle;
	float	c_prod;

	c_prod = cross_product(guy->view, guy->face);
	angle = acosf(c_prod / (vector_length(guy->view)
				* vector_length(guy->face)));
	if (angle < Q_PI)
		return (WALK_BACK);
	if (Q_PI <= angle && angle < THQ_PI)
	{
		if (c_prod > 0)
			return (WALK_RIGHT);
		else
			return (WALK_LEFT);
	}
	return (WALK_FRONT);
}
