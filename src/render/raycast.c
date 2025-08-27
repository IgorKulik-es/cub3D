/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:30:07 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/27 12:45:14 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	calculate_steps(t_game *data, t_ray *ray, float column);
char	get_hit_type(t_ray *ray, t_pos point);

t_hit	cast_ray(t_game *data, float column)
{
	t_ray	ray;
	t_hit	hit;
	t_pos	collision;

	calculate_steps(data, &ray, column);
	find_intersects(data, data->player.pos, &ray);
	if (ray.step_x.x < -__FLT_EPSILON__ || ray.step_y.x < -__FLT_EPSILON__)
		collision = find_collision_neg_x(data, &ray, &hit);
	else
		collision = find_collision_pos_x(data, &ray, &hit);
	hit.type = get_hit_type(&ray, collision);
	if (ray.obst == '1')
		hit.column = collision.x - floor(collision.x)
			+ collision.y - floor(collision.y);
	collision = subtr_vectors(collision, data->player.pos);
	if (fabs(ray.view.x - 0.0f) > __FLT_EPSILON__)
		hit.dist = collision.x / ray.view.x;
	else
		hit.dist = collision.y / ray.view.y;
	return (hit);
}

void	calculate_steps(t_game *data, t_ray *ray, float column)
{
	ray->view = mult_scalar(data->player.camera, (column - data->screen.half_w)
			/ data->screen.win_w);
	ray->view = add_vectors(ray->view, data->player.facing);
	ray->step_x.y = 0;
	ray->step_x.x = 0;
	ray->step_y.x = 0;
	ray->step_y.y = 0;
	if (fabs(ray->view.x - 0.0f) > __FLT_EPSILON__)
		ray->step_x = mult_scalar(ray->view, 1.0f / fabs(ray->view.x));
	if (fabs(ray->view.y - 0.0f) > __FLT_EPSILON__)
		ray->step_y = mult_scalar(ray->view, 1.0f / fabs(ray->view.y));
}

char	get_hit_type(t_ray *ray, t_pos point)
{
	if (ray->obst != '1')
		return (ray->obst);
	if (fabs(point.y - roundf(point.y)) < __FLT_EPSILON__)
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
