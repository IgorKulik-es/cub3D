/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:12:00 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/04 20:00:29 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	check_door_hit(t_game *game, t_ray *ray, t_hit *hit);

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

t_pos	find_collision_neg_x(t_game *data, t_ray *ray, t_hit *hit)
{
	if (ray->start_x.x > ray->start_y.x)
	{
		hit->tile.y = (int)floor(ray->start_x.y);
		hit->tile.x = (int)roundf(ray->start_x.x) - 1;
		hit->point = ray->start_x;
		ray->obst = data->map.map[hit->tile.y][hit->tile.x];
		if (ray->obst == 'D')
			check_door_hit(data, ray, hit);
		if (ray->obst != '0')
			return (ray->start_x);
		ray->start_x = add_vectors(ray->start_x, ray->step_x);
		return (find_collision_neg_x(data, ray, hit));
	}
	hit->tile.y = (int)roundf(ray->start_y.y) - (ray->step_y.y < 0);
	hit->tile.x = (int)floor(ray->start_y.x);
	hit->point = ray->start_y;
	ray->obst = data->map.map[hit->tile.y][hit->tile.x];
	if (ray->obst == 'D')
		check_door_hit(data, ray, hit);
	if (ray->obst != '0')
		return (ray->start_y);
	ray->start_y = add_vectors(ray->start_y, ray->step_y);
	return (find_collision_neg_x(data, ray, hit));
}

t_pos	find_collision_pos_x(t_game *data, t_ray *ray, t_hit *hit)
{
	if (ray->start_x.x < ray->start_y.x)
	{
		hit->tile.y = (int)floor(ray->start_x.y);
		hit->tile.x = (int)roundf(ray->start_x.x);
		hit->point = ray->start_x;
		ray->obst = data->map.map[hit->tile.y][hit->tile.x];
		if (ray->obst == 'D')
			check_door_hit(data, ray, hit);
		if (ray->obst != '0')
			return (ray->start_x);
		ray->start_x = add_vectors(ray->start_x, ray->step_x);
		return (find_collision_pos_x(data, ray, hit));
	}
	hit->tile.y = (int)roundf(ray->start_y.y) - (ray->step_y.y < 0);
	hit->tile.x = (int)floor(ray->start_y.x);
	hit->point = ray->start_y;
	ray->obst = data->map.map[hit->tile.y][hit->tile.x];
	if (ray->obst == 'D')
		check_door_hit(data, ray, hit);
	if (ray->obst != '0')
		return (ray->start_y);
	ray->start_y = add_vectors(ray->start_y, ray->step_y);
	return (find_collision_pos_x(data, ray, hit));
}

void	check_door_hit(t_game *game, t_ray *ray, t_hit *hit)
{
	t_door	*door;
	t_pos	door_hit;
	float	visible_door;
	float	half_width;

	door = find_door(game, hit->tile.x, hit->tile.y);
	if (door->type == D_TYPE_VERT)
	{
		door_hit = add_vectors(hit->point, mult_scalar(ray->step_x, 0.5f));
		visible_door = door_hit.y - hit->tile.y;
	}
	else
	{
		door_hit = add_vectors(hit->point, mult_scalar(ray->step_y, 0.5f));
		visible_door = door_hit.x - hit->tile.x;
	}
	half_width = door->width / 2;
	if (visible_door > 0 && visible_door < half_width)
	{
		hit->column = 0.5f - half_width + visible_door;
		hit->point = door_hit;
		return ;
	}
	if (visible_door < 1 && visible_door >= 1 - half_width)
	{
		hit->column = -0.5f + half_width + visible_door;
		hit->point = door_hit;
		return ;
	}
	ray->obst = '0';
	if (door->type == D_TYPE_VERT)
	{
		door_hit = ray->start_y;
		visible_door = door_hit.x - hit->tile.x;
	}
	else
	{
		door_hit = ray->start_x;
		visible_door = door_hit.y - hit->tile.y;
	}
	if (0 < visible_door && visible_door < 1)
	{
		ray->obst = DOOR_WALL;
		hit->type = DOOR_WALL;
		hit->point = door_hit;
		hit->column = visible_door;
	}
}
