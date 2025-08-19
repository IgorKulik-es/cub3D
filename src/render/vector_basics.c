/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 17:06:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/19 17:16:32 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

t_pos	mult_scalar(t_pos vector, float mult)
{
	t_pos	temp;

	temp.x = vector.x * mult;
	temp.y = vector.y * mult;
	return (temp);
}

t_pos	sum_vectors(t_pos a, t_pos b)
{
	t_pos	temp;

	temp.x = a.x + b.x;
	temp.y = a.y + b.y;
	return (temp);
}
