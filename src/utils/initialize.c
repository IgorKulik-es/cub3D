/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:49:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/09 20:11:06 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	initialize_data(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	game->screen.win_h = WIN_HEIGHT / WIN_UPSC_FACTOR;
	game->screen.win_w = WIN_WIDTH / WIN_UPSC_FACTOR;
	game->screen.half_w = game->screen.win_w / 2;
	game->screen.last_frame_time = get_time();
	game->player.moving = 0;
	game->player.rotating = 0;
	game->last_mouse_x = -1;
	game->player.hp = P_BASE_HP;
	game->player.inv_det = 1.0f / P_POV;
	game->enemy_prot.action.img.height = 64;
	game->enemy_prot.walk_back.img.height = 64;
	game->enemy_prot.walk_front.img.height = 64;
	game->tint.r = WIN_DARK_FACTOR;
	game->tint.g = WIN_DARK_FACTOR;
	game->tint.b = WIN_DARK_FACTOR;
	game->game_stage = INTRO;
	game->texts.bans.move = 1;
	game->texts.bans.pos = 0;
}
