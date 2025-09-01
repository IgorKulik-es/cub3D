/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:21:41 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/01 20:11:48 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_entity_collision(t_game *game, t_pos face, t_pos new);
void	detect_player(t_game *game, t_entity *guy);

void	move_enemy(t_game *game, t_entity *guy)
{
	t_pos	new;
	float	step;

	guy->trans = dist_to_entity(game, guy);
	detect_player(game, guy);
	step = ((get_time() - game->screen.last_frame_time) / (float)P_ENEMY_SPEED)
		* guy->state;
	new = add_vectors(guy->pos, mult_scalar(guy->face, step));
	if (guy->dist < E_MIN_DIST && game->game_over == false)
		return ;
	if (guy->state == E_STATE_ANGRY)
		guy->pos = smooth_collision(game, guy->pos, new);
	else if (check_entity_collision(game, guy->face, new))
		guy->pos = new;
	else if (guy->face.x)
	{
		guy->face.y = (guy->face.x > 0) - (guy->face.x < 0);
		guy->face.x = 0;
	}
	else
	{
		guy->face.x = (guy->face.y < 0) - (guy->face.y > 0);
		guy->face.y = 0;
	}
}

bool	check_entity_collision(t_game *game, t_pos face, t_pos new)
{
	t_coords	tile;
	t_coords	new_tile;
	float		dist;

	tile.x = floor(new.x);
	tile.y = floor(new.y);
	if (game->map.map[tile.y][tile.x] == '1'
		|| (game->map.map[tile.y][tile.x] == 'D'
			&& find_door(game, tile.x, tile.y)->state == D_STATE_CLOSED))
		return (false);
	new_tile.x = tile.x + face.x;
	new_tile.y = tile.y + face.y;
	if (game->map.map[new_tile.y][new_tile.x] == '0'
		|| (game->map.map[new_tile.y][new_tile.x] == 'D'
			&& find_door(game, new_tile.x, new_tile.y)->state == D_STATE_OPEN))
		return (true);
	dist = (roundf(new.x) - new.x) * face.x + (roundf(new.y) - new.y) * face.y;
	if (dist > 0 && dist < P_WALL_D)
		return (false);
	return (true);
}

void	detect_player(t_game *game, t_entity *guy)
{
	if (guy->mode == WALK_FRONT || guy->mode == ACTION)
	{
		if (guy->dist < E_DET_RADIUS && game->game_over == false)
			guy->state = E_STATE_ANGRY;
		else if (guy->dist > 2 * E_DET_RADIUS || game->game_over)
		{
			if (guy->state == E_STATE_ANGRY || game->game_over)
			{
				guy->face.x = -(guy->face.x > 0) + (guy->face.x < 0);
				guy->face.y = -(guy->face.y > 0) + (guy->face.y < 0);
				if (fabsf(guy->face.x) > fabsf(guy->face.y))
					guy->face.y = 0;
				else
					guy->face.x = 0;
			}
			guy->state = E_STATE_CALM;
		}
	}
	if (guy->state == E_STATE_ANGRY)
		guy->face = mult_scalar(guy->view, -1 / guy->dist);
}

