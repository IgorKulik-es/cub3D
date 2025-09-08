/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:21:41 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/08 14:41:47 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	check_entity_collision(t_game *game, t_entity *guy, t_pos new);
void	detect_player(t_game *game, t_entity *guy);

void	move_enemy(t_game *game, t_entity *guy)
{
	t_pos	new;
	float	step;

	guy->trans = dist_to_entity(game, guy);
	detect_player(game, guy);
	if (guy->mode == ACTION)
		return ;
	step = ((get_time() - game->screen.last_frame_time) / (float)P_ENEMY_SPEED)
		* guy->state;
	new = add_vectors(guy->pos, mult_scalar(guy->face, step));
	if (guy->dist < E_MIN_DIST && game->game_over == false)
		return ;
	if (guy->state == E_STATE_ANGRY)
		guy->pos = smooth_collision(game, guy->pos, new);
	else if (check_entity_collision(game, guy, new))
		guy->pos = new;
}

bool	check_entity_collision(t_game *game, t_entity *guy, t_pos new)
{
	t_pos	new_pos;
	t_pos	view;

	new_pos = smooth_collision(game, guy->pos, new);
	if (new_pos.x == new.x && new_pos.y == new.y)
		return (true);
	view = subtr_vectors(new, guy->pos);
	if (fabsf(view.x) > 0)
	{
		view.y = (view.x > 0) - (view.x <= 0);
		view.x = 0;
	}
	else
	{
		view.x = (view.y < 0) - (view.y >= 0);
		view.y = 0;
	}
	guy->face = view;
	return (true);
}

void	detect_player(t_game *game, t_entity *guy)
{
	if (guy->mode == WALK_FRONT || guy->mode == ACTION)
	{
		if (guy->dist < E_DET_RADIUS && game->game_over == false)
			guy->state = E_STATE_ANGRY;
		else if (guy->dist > 2 * E_DET_RADIUS)
		{
			if (guy->state == E_STATE_ANGRY)
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
