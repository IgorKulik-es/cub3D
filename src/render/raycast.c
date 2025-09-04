/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:30:07 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/04 20:01:02 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	calculate_steps(t_game *data, t_ray *ray, float column);
char	get_hit_type(t_ray *ray, t_pos point);

t_hit	cast_ray(t_game *data, float column)
{
	t_ray	ray;
	t_hit	hit;
	t_pos	vector;

	calculate_steps(data, &ray, column);
	find_intersects(data, data->player.pos, &ray);
	if (ray.step_x.x < -__FLT_EPSILON__ || ray.step_y.x < -__FLT_EPSILON__)
		find_collision_neg_x(data, &ray, &hit);
	else
		find_collision_pos_x(data, &ray, &hit);
	hit.type = get_hit_type(&ray, hit.point);
	if (ray.obst == '1')
		hit.column = hit.point.x - floor(hit.point.x)
			+ hit.point.y - floor(hit.point.y);
	vector = subtr_vectors(hit.point, data->player.pos);
	if (fabsf(ray.view.x - 0.0f) > __FLT_EPSILON__)
		hit.dist = vector.x / ray.view.x;
	else
		hit.dist = vector.y / ray.view.y;
	return (hit);
}

void	calculate_steps(t_game *data, t_ray *ray, float column)
{
	ray->view = mult_scalar(data->player.camera, 2 * column
			/ data->screen.win_w - 1.0f);
	ray->view = add_vectors(ray->view, data->player.facing);
	ray->step_x.y = 0;
	ray->step_x.x = 0;
	ray->step_y.x = 0;
	ray->step_y.y = 0;
	if (fabsf(ray->view.x - 0.0f) > __FLT_EPSILON__)
		ray->step_x = mult_scalar(ray->view, 1.0f / fabsf(ray->view.x));
	if (fabsf(ray->view.y - 0.0f) > __FLT_EPSILON__)
		ray->step_y = mult_scalar(ray->view, 1.0f / fabsf(ray->view.y));
}

char	get_hit_type(t_ray *ray, t_pos point)
{
	if (ray->obst != '1')
		return (ray->obst);
	if (fabsf(point.y - roundf(point.y)) < __FLT_EPSILON__)
	{
		if (ray->view.y > 0)
			return ('N');
		else
			return ('S');
	}
	else if (ray->view.x > 0)
		return ('W');
	return ('E');
}
