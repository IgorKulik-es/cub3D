/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaming.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:25 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 20:08:36 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	update_all_positions(t_game *game)
{
	int	index;

	index = -1;
	if (game->game_stage == WIN)
		return ;
	if (game->player.moving != 0)
		move_player(game, game->player.moving);
	if (game->player.rotating)
		rotate_player(game, game->player.rotating);
	if (game->player.stafing)
		strafe_player(game, game->player.stafing);
	while (++index < game->num_doors)
		move_door(game, &(game->doors[index]));
	index = -1;
	while (++index < game->num_enemies)
	{
		move_enemy(game, &(game->enemies[index]));
		update_enem_frame(game, &(game->enemies[index]), &(game->enemies[index]
				.anims[game->enemies[index].mode]));
	}
	update_exit_frame(&game->exit);
}

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		clean_exit(game, NULL, 0);
	if (game->game_stage != PLAY)
		return (1);
	if (key == W || key == S || key == XK_Down || key == XK_Up)
		game->player.moving = key;
	if (key == A || key == D)
		game->player.stafing = key;
	if (key == XK_Left || key == XK_Right)
		game->player.rotating = key;
	if (key == SPACE)
	{
		open_door(game);
		check_exit(game);
	}
	if (key == XK_1)
		game->mode ^= M_MINIMAP;
	if (key == XK_2)
		game->mode ^= M_FPS;
	if (key == XK_3)
		game->mode ^= M_VISIBLE_HP;
	if (key == XK_4)
		game->mode ^= M_DARK;
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W || key == S || key == XK_Down || key == XK_Up)
		game->player.moving = 0;
	if (key == A || key == D)
		game->player.stafing = 0;
	if (key == XK_Left || key == XK_Right)
		game->player.rotating = 0;
	return (0);
}

void	game_over(t_game *game)
{
	int	index;

	index = 0;
	if ((game->texts.draw_mode & M_GAME_OVER_PL) == false)
		printf("GAME OVER!\n");
	game->game_stage = LOSE;
	game->texts.bans.move = 1;
	while (index < game->num_enemies)
	{
		if (game->enemies[index].state == E_STATE_ANGRY)
			calm_down_enemy(&(game->enemies[index]));
		index++;
	}
}

void	check_exit(t_game *game)
{
	bool	win;

	win = false;
	if (game->map.map[game->player.tile.y - 1][game->player.tile.x] == T_EXIT)
		win = true;
	if (game->map.map[game->player.tile.y + 1][game->player.tile.x] == T_EXIT)
		win = true;
	if (game->map.map[game->player.tile.y][game->player.tile.x - 1] == T_EXIT)
		win = true;
	if (game->map.map[game->player.tile.y][game->player.tile.x + 1] == T_EXIT)
		win = true;
	if (!win)
		return ;
	game->game_stage = WIN;
	game->texts.bans.move = 1;
}
