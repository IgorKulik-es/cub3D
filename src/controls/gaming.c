/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaming.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:25 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/05 20:11:58 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3D.h"

void	update_all_positions(t_game *game)
{
	int	index;

	index = -1;
	if (game->player.moving)
		move_player(game, game->player.moving);
	if (game->player.rotating)
		rotate_player(game, game->player.rotating);
	while (++index < game->num_doors)
		move_door(game, &(game->doors[index]));
	index = -1;
	while (++index < game->num_enemies)
	{
		move_enemy(game, &(game->enemies[index]));
		update_anim_frame(game, &(game->enemies[index]), &(game->enemies[index]
				.anims[game->enemies[index].mode]), game->enemies[index].mode);
	}
}

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		clean_exit(game, NULL, 0);
	if (game->game_over)
		return (1);
	if (key == W || key == S)
		game->player.moving = key;
	if (key == A || key == D)
		game->player.rotating = key;
	if (key == SPACE)
		open_door(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W || key == S)
		game->player.moving = 0;
	if (key == A || key == D)
		game->player.rotating = 0;
	return (0);
}

int	close_game(t_game *game)
{
	clean_exit(game, NULL, 0);
	return (1);
}
