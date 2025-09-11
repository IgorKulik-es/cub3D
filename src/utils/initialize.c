/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:49:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 20:00:57 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	initialize_data(t_game *game)
{
	ft_bzero(game, sizeof(t_game));
	if (WIN_UPSC_FACTOR < 1)
		clean_exit(game, "wrong upscale parameter", EXIT_FAILURE);
	game->screen.win_h = WIN_HEIGHT / WIN_UPSC_FACTOR;
	game->screen.win_w = WIN_WIDTH / WIN_UPSC_FACTOR;
	game->screen.half_w = game->screen.win_w * 0.5f;
	game->screen.half_h = game->screen.win_h * 0.5f;
	game->screen.last_frame_time = get_time();
	game->player.moving = 0;
	game->player.rotating = 0;
	game->last_mouse_x = -1;
	game->player.hp = P_BASE_HP;
	game->player.inv_det = 1.0f / P_POV;
	game->mode = 0b1111;
	game->game_stage = PLAY;
	game->texts.bans.move = 1;
	game->texts.bans.pos = 0;
	game->darkness = WIN_DARK_FACTOR;
	game->tint.r = 0;
	game->tint.g = 0;
	game->tint.b = 0;
}
