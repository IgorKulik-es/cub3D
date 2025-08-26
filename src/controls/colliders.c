/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:21:00 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/25 18:54:09 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	check_wall_collision(t_game *game, t_pos *new)
{
	int		row;
	int		column;
	int		new_row;
	int		new_col;
	t_pos	wall_dist;

	row = floor(new->x);
	column = floor(new->y);
	new_row = row;
	new_col = column;
	if (game->map.map[column][row] != '0')
		return (false);
	wall_dist.x = new->x - row;
	wall_dist.y = new->y - column;
	if (wall_dist.x < P_WALL_LIMIT)
		new_row--;
	if (wall_dist.x > 1.0f - P_WALL_LIMIT)
		new_row++;
	if (wall_dist.y < P_WALL_LIMIT)
		new_col--;
	if (wall_dist.y > 1.0f - P_WALL_LIMIT)
		new_col++;
	if (game->map.map[new_col][row] == '1')
		new->y = game->player.pos.y;
	if (game->map.map[column][new_row] == '1')
		new->x = game->player.pos.x;
	if (row != new_row && column != new_col && game->map.map[new_col][new_row] == '1')
	{
		if (wall_dist.x > wall_dist.y)
			new->x = game->player.pos.x;
		else
			new->y = game->player.pos.y;
	}
	//printf("player %f %f new tile x %d %d, new tile y %d %d\n", game->player.pos.x, game->player.pos.y, column, new_row, new_col, row);
/* 	printf("dist: %f %f, player: %f %f ", wall_dist.x, wall_dist.y, game->player.pos.x, game->player.pos.y);
	if (wall_dist.x > P_WALL_LIMIT && wall_dist.y > P_WALL_LIMIT)
		return (true);
	new_row = row;
	new_col = column;
	if (wall_dist.x < P_WALL_LIMIT)
		new_row += (roundf(new->x) - new->x > 0) - (roundf(new->x) - new->x < 0);
	if (wall_dist.x < P_WALL_LIMIT)
		new_col += (roundf(new->y) - new->y > 0) - (roundf(new->y) - new->y < 0);
	if (wall_dist.x < P_WALL_LIMIT && (game->map.map[column][new_row] != '0'))
		new->x = game->player.pos.x;
	if (wall_dist.y < P_WALL_LIMIT && (game->map.map[new_col][row] != '0'))
		new->y = game->player.pos.y;
 */	return (true);
}

t_pos	find_first_collision(t_game *game, t_pos start, t_pos end)
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
}
