/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 20:07:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/08 14:49:51 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_player(t_game *game, int key)
{
	t_pos	new;
	float	mult;

	if (game->game_over)
		return ;
	mult = (get_time() - game->screen.last_frame_time) / (float)P_MOVE_SPEED;
	if (key == S)
		mult *= -1;
	new = mult_scalar(game->player.facing, mult);
	new = add_vectors(game->player.pos, new);
	game->player.pos = smooth_collision(game, game->player.pos, new);
	game->player.tile.x = floorf(game->player.pos.x);
	game->player.tile.y = floorf(game->player.pos.y);
}

void	rotate_player(t_game *game, int key)
{
	time_t		c_time;
	float		angle;

	if (game->game_over)
		return ;
	c_time = get_time();
	angle = (c_time - game->screen.last_frame_time) / (float)P_ROTATE_SPEED;
	if (key == A)
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
	if (game->game_over)
	{
		guy->face.x = -(guy->face.x > 0) + (guy->face.x < 0);
		guy->face.y = -(guy->face.y > 0) + (guy->face.y < 0);
		if (fabsf(guy->face.x) > fabsf(guy->face.y))
			guy->face.y = 0;
		else
			guy->face.x = 0;
		guy->state = E_STATE_CALM;
	}
}
