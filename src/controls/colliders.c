/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:21:00 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 18:12:21 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_next_tile(t_game *game, t_pos *new,
				t_pos old, t_coords new_tile);
static bool	is_wall(t_game *game, int x, int y);

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

	old_tile.x = floorf(new->x);
	old_tile.y = floorf(new->y);
	if (is_wall(game, old_tile.x, new_tile.y))
		new->y = old.y;
	if (is_wall(game, new_tile.x, old_tile.y))
		new->x = old.x;
	if (old_tile.x != new_tile.x && old_tile.y != new_tile.y
		&& old.x != new->x && old.y != new->y
		&& is_wall(game, new_tile.x, new_tile.y))
	{
		if (fabsf(old.x - roundf(old.x)) > fabsf(old.y - roundf(old.y)))
			new->x = old.x;
		else
			new->y = old.y;
	}
}

static bool	is_wall(t_game *game, int x, int y)
{
	if ((0 > x || x >= game->map.width) || (0 > y || y >= game->map.height))
		return (true);
	if (game->map.map[y][x] == '1')
		return (true);
	if (game->map.map[y][x] == 'X')
		return (true);
	if (game->map.map[y][x] == 'D'
		&& find_door(game, x, y)->state == D_STATE_CLOSED)
		return (true);
	return (false);
}
