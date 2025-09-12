/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:07:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/12 11:55:25 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_game *game, int key)
{
	t_pos	new;
	float	mult;

	if (game->game_stage != PLAY)
		return ;
	mult = (get_time() - game->screen.last_frame_time) / (float)P_MOVE_SPEED;
	if (key == S || key == DOWN)
		mult *= -1;
	new = mult_scalar(game->player.facing, mult);
	new = add_vectors(game->player.pos, new);
	correct_entity_position(game, &new, game->player.pos);
	game->player.pos = smooth_collision(game, game->player.pos, new);
	game->player.tile.x = floorf(game->player.pos.x);
	game->player.tile.y = floorf(game->player.pos.y);
}

void	rotate_player(t_game *game, int key)
{
	time_t		c_time;
	float		angle;

	if (game->game_stage != PLAY)
		return ;
	c_time = get_time();
	angle = (c_time - game->screen.last_frame_time) / (float)P_ROTATE_SPEED;
	if (key == LEFT)
		angle *= -1;
	game->player.facing = rotate_vector(game->player.facing, angle);
	game->player.camera = rotate_vector(game->player.camera, angle);
}

void	damage_player(t_game *game, t_entity *guy)
{
	blood_effect(game, P_RED_SHIFT);
	if (game->player.hp > 0)
		(game->player.hp)--;
	if (game->player.hp == 0)
		game_over(game);
	else if (!(game->texts.draw_mode & M_VISIBLE_HP))
		printf("Hit points left: %d\n", game->player.hp);
	if (game->game_stage == LOSE)
		calm_down_enemy(guy);
}

void	strafe_player(t_game *game, int key)
{
	t_pos	new;
	float	mult;

	if (game->game_stage != PLAY)
		return ;
	mult = (get_time() - game->screen.last_frame_time) / (float)P_MOVE_SPEED;
	mult /= vector_length(game->player.camera);
	if (key == A)
		mult *= -1;
	new = mult_scalar(game->player.camera, mult);
	new = add_vectors(game->player.pos, new);
	game->player.pos = smooth_collision(game, game->player.pos, new);
	game->player.tile.x = floorf(game->player.pos.x);
	game->player.tile.y = floorf(game->player.pos.y);
}
