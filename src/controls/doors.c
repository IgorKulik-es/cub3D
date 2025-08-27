/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 18:54:45 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/27 13:40:36 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

//t_hit	see_door(t_game *game, t_door door);

/*void	render_door(t_game *game, t_door door)
{
	t_hit	hit;
	t_pos	other_edge;
	t_trapz	trpz;

	hit = see_door(game, door);
	if (hit.type == MISS)
		return ;
	other_edge = hit.point;
	if (door.type == D_TYPE_VERT)
		other_edge.y = other_edge.y + 1;
	else if (hit.point.x > door.x)
		other_edge.x = other_edge.x - 1;
	else
		other_edge.x = other_edge.x + 1;
	trpz.x = game->screen.win_w * (0.5f + tangent_known_length
		(game->player.facing, hit.point, 1, hit.dist) / P_POV);
	trpz.left_height = game->screen.win_h /
}

t_hit	see_door(t_game *game, t_door door)
{
	t_hit	hit;

	hit = check_visibility(game, game->player.pos, (t_pos){door.x, door.y});
	if (hit.type == MISS)
		hit = check_visibility(game, game->player.pos,
			(t_pos){door.x + 1, door.y});
	if (hit.type == MISS)
		hit = check_visibility(game, game->player.pos,
			(t_pos){door.x, door.y + 1});
	if (hit.type == MISS)
		hit = check_visibility(game, game->player.pos,
			(t_pos){door.x + 1, door.y + 1});
	return (hit);
}*/

t_door	*find_door(t_game *game, t_coords wall)
{
	int	index;

	index = 0;
	while (index < game->num_doors)
	{
		if ((game->doors[index]).x == wall.x && (game->doors[index]).y == wall.y)
			return &(game->doors[index]);
		index++;
	}
	return (NULL);
}
