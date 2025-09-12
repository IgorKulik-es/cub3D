/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/26 13:12:00 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/12 11:47:14 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	check_door_hit(t_game *game, t_ray *ray, t_hit *hit);
static bool	check_leaf_hit(t_hit *hit, t_pos door_hit,
				float visible_door, float half_width);
static void	check_door_frame_hit(t_ray *ray, t_door *door, t_hit *hit);

t_pos	find_collision_neg_x(t_game *game, t_ray *ray, t_hit *hit)
{
	if (ray->start_x.x > ray->start_y.x)
	{
		hit->tile.y = (int)floorf(ray->start_x.y);
		hit->tile.x = (int)roundf(ray->start_x.x) - 1;
		hit->point = ray->start_x;
		ray->obst = game->map.map[hit->tile.y][hit->tile.x];
		if (ray->obst == 'D')
			check_door_hit(game, ray, hit);
		if (ray->obst != '0')
			return (ray->start_x);
		ray->start_x = add_vectors(ray->start_x, ray->step_x);
		return (find_collision_neg_x(game, ray, hit));
	}
	hit->tile.y = (int)roundf(ray->start_y.y) - (ray->step_y.y < 0);
	hit->tile.x = (int)floorf(ray->start_y.x);
	hit->point = ray->start_y;
	ray->obst = game->map.map[hit->tile.y][hit->tile.x];
	if (ray->obst == 'D')
		check_door_hit(game, ray, hit);
	if (ray->obst != '0')
		return (ray->start_y);
	ray->start_y = add_vectors(ray->start_y, ray->step_y);
	return (find_collision_neg_x(game, ray, hit));
}

t_pos	find_collision_pos_x(t_game *game, t_ray *ray, t_hit *hit)
{
	if (ray->start_x.x < ray->start_y.x)
	{
		hit->tile.y = (int)floorf(ray->start_x.y);
		hit->tile.x = (int)roundf(ray->start_x.x);
		hit->point = ray->start_x;
		ray->obst = game->map.map[hit->tile.y][hit->tile.x];
		if (ray->obst == 'D')
			check_door_hit(game, ray, hit);
		if (ray->obst != '0')
			return (ray->start_x);
		ray->start_x = add_vectors(ray->start_x, ray->step_x);
		return (find_collision_pos_x(game, ray, hit));
	}
	hit->tile.y = (int)roundf(ray->start_y.y) - (ray->step_y.y < 0);
	hit->tile.x = (int)floorf(ray->start_y.x);
	hit->point = ray->start_y;
	ray->obst = game->map.map[hit->tile.y][hit->tile.x];
	if (ray->obst == 'D')
		check_door_hit(game, ray, hit);
	if (ray->obst != '0')
		return (ray->start_y);
	ray->start_y = add_vectors(ray->start_y, ray->step_y);
	return (find_collision_pos_x(game, ray, hit));
}

static void	check_door_hit(t_game *game, t_ray *ray, t_hit *hit)
{
	t_door	*door;
	t_pos	door_hit;
	float	visible_door;

	door = find_door(game, hit->tile.x, hit->tile.y);
	if (door->type == D_TYPE_VERT)
		door_hit = add_vectors(hit->point, mult_scalar(ray->step_x, 0.5f));
	else
		door_hit = add_vectors(hit->point, mult_scalar(ray->step_y, 0.5f));
	visible_door = door_hit.x - hit->tile.x;
	if (door->type == D_TYPE_VERT)
		visible_door = door_hit.y - hit->tile.y;
	if (check_leaf_hit(hit, door_hit, visible_door, door->width / 2))
		return ;
	check_door_frame_hit(ray, door, hit);
}

static bool	check_leaf_hit(t_hit *hit, t_pos door_hit,
	float visible_door, float half_width)
{
	if (visible_door > 0 && visible_door < half_width)
	{
		hit->column = 0.5f - half_width + visible_door;
		hit->point = door_hit;
		return (true);
	}
	if (visible_door < 1 && visible_door >= 1 - half_width)
	{
		hit->column = -0.5f + half_width + visible_door;
		hit->point = door_hit;
		return (true);
	}
	return (false);
}

static void	check_door_frame_hit(t_ray *ray, t_door *door, t_hit *hit)
{
	float	visible_door;
	t_pos	door_hit;

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
