/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:30:07 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/22 18:07:35 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	find_intersects(t_game *data, t_pos player, t_ray *ray);
void	calculate_steps(t_game *data, t_ray *ray, float column);
t_pos	find_collision_neg_x(t_game *data, t_ray *ray);
t_pos	find_collision_pos_x(t_game *data, t_ray *ray);

t_hit	cast_ray(t_game *data, float column)
{
	t_ray	ray;
	t_hit	hit;
	t_pos	collision;

	calculate_steps(data, &ray, column);
	find_intersects(data, data->player.pos, &ray);
	if (ray.step_x.x < -__FLT_EPSILON__ || ray.step_y.x < -__FLT_EPSILON__)
		collision = find_collision_neg_x(data, &ray);
	else
		collision = find_collision_pos_x(data, &ray);
	if (fabs(collision.y - roundf(collision.y)) < __FLT_EPSILON__)
		hit.type = 'W' * (ray.view.y > 0) + 'E' * (ray.view.y <= 0);
	else
		hit.type = 'N' * (ray.view.x > 0) + 'S' * (ray.view.x <= 0);
	hit.column = collision.x - floor(collision.x)
		+ collision.y - floor(collision.y);
/* 	if (hit.column < 0)
		hit.column = hit.column + 1; */
	collision = subtr_vectors(collision, data->player.pos);
	if (fabs(ray.view.x - 0.0f) > __FLT_EPSILON__)
		hit.dist = collision.x / ray.view.x;
	else
		hit.dist = collision.y / ray.view.y;
	return (hit);
}

void	find_intersects(t_game *data, t_pos player, t_ray *ray)
{

	ray->start_x.x = floor(player.x) + (ray->view.x > 0);
	ray->start_y.y = floor(player.y) + (ray->view.y > 0);
	if (fabs(ray->view.x - 0.0f) > __FLT_EPSILON__)
		ray->start_x.y = ((ray->start_x.x - player.x) / ray->view.x)
			* ray->view.y + player.y;
	else
	{
		ray->start_x.y = data->map.height;
		ray->start_x.x = data->map.width;
	}
	if (fabs(ray->view.y - 0.0f) > __FLT_EPSILON__)
		ray->start_y.x = ((ray->start_y.y - player.y) / ray->view.y)
			* ray->view.x + player.x;
	else
	{
		ray->start_y.y = data->map.height;
		ray->start_y.x = data->map.width * (ray->view.x > 0);
	}
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

t_pos	find_collision_neg_x(t_game *data, t_ray *ray)
{
	if (ray->start_x.x > ray->start_y.x)
	{
		if (data->map.map[(int)floor(ray->start_x.y)][(int)
			roundf(ray->start_x.x) - 1] == '1')
			return (ray->start_x);
		else
		{
			ray->start_x = add_vectors(ray->start_x, ray->step_x);
			return (find_collision_neg_x(data, ray));
		}
	}
	else
	{
		if (data->map.map[(int)roundf(ray->start_y.y) - (ray->step_y.y < 0)]
			[(int)floor(ray->start_y.x)] == '1')
			return (ray->start_y);
		else
		{
			ray->start_y = add_vectors(ray->start_y, ray->step_y);
			return (find_collision_neg_x(data, ray));
		}
	}
}

t_pos	find_collision_pos_x(t_game *data, t_ray *ray)
{
	if (ray->start_x.x < ray->start_y.x)
	{
		if (data->map.map[(int)floor(ray->start_x.y)][(int)
			roundf(ray->start_x.x)] == '1')
			return (ray->start_x);
		else
		{
			ray->start_x = add_vectors(ray->start_x, ray->step_x);
			return (find_collision_pos_x(data, ray));
		}
	}
	else
	{
		if (data->map.map[(int)roundf(ray->start_y.y) - (ray->step_y.y < 0)]
			[(int)floor(ray->start_y.x)] == '1')
			return (ray->start_y);
		else
		{
			ray->start_y = add_vectors(ray->start_y, ray->step_y);
			return (find_collision_pos_x(data, ray));
		}
	}
}
