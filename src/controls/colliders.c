/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colliders.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 16:21:00 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/25 15:47:43 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

bool	check_wall_collision(t_game *game, t_pos new)
{
	int		row;
	int		column;
	float	x_wall_dist;
	float	y_wall_dist;

	row = floor(new.x);
	column = floor(new.y);
	x_wall_dist = fabs(roundf(new.x) - new.x);
	y_wall_dist = fabs(roundf(new.y) - new.y);
	printf("x dist: %f y dist: %f, player: %f %f\n", x_wall_dist, y_wall_dist, game->player.pos.x, game->player.pos.y);
	if (x_wall_dist > P_WALL_LIMIT && y_wall_dist > P_WALL_LIMIT)
		return (true);
	if (x_wall_dist < P_WALL_LIMIT)
		if (game->map.map[column][row + (roundf(new.x) - new.x > 0) - (roundf(new.x) - new.x < 0)] != '0')
			return (false);
	if (y_wall_dist < P_WALL_LIMIT)
		if (game->map.map[column + (roundf(new.y) - new.y > 0) - (roundf(new.y) - new.y < 0)][row] != '0')
			return (false);
	if (x_wall_dist < P_WALL_LIMIT && y_wall_dist < P_WALL_LIMIT)
		if (game->map.map[column + (roundf(new.y) - new.y > 0) - (roundf(new.y) - new.y < 0)][row + (roundf(new.x) - new.x > 0) - (roundf(new.x) - new.x < 0)] != '0')
			return (false);
	return (true);
}
