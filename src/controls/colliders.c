/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:21:00 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/08 13:01:12 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_next_tile(t_game *game, t_pos *new, t_pos old, t_coords new_tile);

t_pos	smooth_collision(t_game *game, t_pos old, t_pos new)
{
	t_coords	new_tile;
	t_pos		wall_dist;

	new_tile.x = floor(new.x);
	new_tile.y = floor(new.y);
	wall_dist.x = new.x - new_tile.x;
	wall_dist.y = new.y - new_tile.y;
	new_tile.x += -(wall_dist.x < P_WALL_D) + (wall_dist.x > 1.0f - P_WALL_D);
	new_tile.y += -(wall_dist.y < P_WALL_D) + (wall_dist.y > 1.0f - P_WALL_D);
	check_next_tile(game, &new, old, new_tile);
	return (new);
}

void	check_next_tile(t_game *game, t_pos *new, t_pos old, t_coords new_tile)
{
	t_coords	old_tile;

	old_tile.x = floorf(old.x);
	old_tile.y = floorf(old.y);
	if (game->map.map[new_tile.y][old_tile.x] == '1'
		|| (game->map.map[new_tile.y][old_tile.x] == 'D'
		&& find_door(game, old_tile.x, new_tile.y)->state == D_STATE_CLOSED))
		new->y = old.y;
	if (game->map.map[old_tile.y][new_tile.x] == '1'
		|| (game->map.map[old_tile.y][new_tile.x] == 'D'
		&& find_door(game, new_tile.x, old_tile.y)->state == D_STATE_CLOSED))
		new->x = old.x;
	if (old_tile.x != new_tile.x && old_tile.y != new_tile.y
		&& old.x != new->x && old.y != new->y
		&& (game->map.map[new_tile.y][new_tile.x] == '1'
		|| (game->map.map[new_tile.y][new_tile.x] == 'D'
		&& find_door(game, new_tile.x, new_tile.y)->state == D_STATE_CLOSED)))
	{
		if (fabsf(old.x - roundf(old.x)) > fabsf(old.y - roundf(old.y)))
			new->x = old.x;
		else
			new->y = old.y;
	}
}

/* t_pos	find_first_collision(t_game *game, t_pos start, t_pos end)
{
	t_ray	ray;
	t_hit	hit;
	t_pos	collision;

	ft_bzero(&ray, sizeof(t_ray));
	ray.view = subtr_vectors(end, start);
	find_intersects(game, start, &ray);
	if (fabs(ray.view.x - 0.0f) > __FLT_EPSILON__)
		ray.step_x = mult_scalar(ray.view, 1.0f / fabs(ray.view.x));
	if (fabs(ray.view.y - 0.0f) > __FLT_EPSILON__)
		ray.step_y = mult_scalar(ray.view, 1.0f / fabs(ray.view.y));
	if (ray.step_x.x < -__FLT_EPSILON__ || ray.step_y.x < -__FLT_EPSILON__)
		collision = find_collision_neg_x(game, &ray, &hit);
	else
		collision = find_collision_pos_x(game, &ray, &hit);
	start = subtr_vectors(collision, start);
	if (fabs(start.x) > fabs(ray.view.x) || fabs(start.y) > fabs(ray.view.y))
		return (end);
	return (collision);
}

t_hit	check_visibility(t_game *game, t_pos start, t_pos end)
{
	t_hit	hit;

	hit.type = 0;
	hit.dist = 0;
	hit.point = find_first_collision(game, start, end);
	if (fabs(hit.point.x - end.x) < __FLT_EPSILON__
		&& fabs(hit.point.y - end.y) < __FLT_EPSILON__)
		hit.type = 1;
	if (hit.type == 1)
		hit.dist = vector_length(subtr_vectors(end, start));
	return (hit);
} */
