/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_advanced.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:56:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/25 20:01:49 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

float	cross_product(t_pos a, t_pos b)
{
	return (a.x * b.x + a.y * b.y);
}

float	tangent_known_length(t_pos a, t_pos b, float len_a, float len_b)
{
	float	sine;

	sine = cross_product(a, b) / (len_a * len_b);
	return (tanf(asinf(sine)));
}
