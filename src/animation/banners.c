/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   banners.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:58:11 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/09 15:33:06 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	mix_colors(int *old_px, int new_px, float mult_row);
static void	update_banner_state(t_game *game, t_bans *banner);
static void	display_banner(t_game *game, t_bans *ban_str, t_img *banner);

static void	display_banner(t_game *game, t_bans *ban_str, t_img *banner)
{
	int			ind_old_px;
	int			ind_new_px;
	t_coords	limits;
	int			row;
	float		mult_row;

	ind_new_px = 0;
	ind_old_px = game->screen.win_w * (game->screen.win_h - banner->height) / 2;
	limits.y = banner->width * banner->height;
	row = 0;
	while (ind_new_px < limits.y)
	{
		limits.x = -1;
		mult_row = (float)row / banner->height;
		if (mult_row < ban_str->pos)
			mult_row = 1;
		while (++(limits.x) < banner->width)
		{
			mix_colors(&game->screen.pixels[ind_old_px], banner
				->addr[ind_new_px], ban_str->pos);
			ind_new_px++;
			ind_old_px++;
		}
		row++;
	}
}

static void	mix_colors(int *old_px, int new_px, float mult_row)
{
	t_coords	r;
	t_coords	g;
	t_coords	b;

	if (mult_row == 1)
		*old_px = new_px;
	else
	{
		r.x = (*old_px >> 16) & 0xff;
		r.y = (new_px >> 16) & 0xff;
		g.x = (*old_px >> 8) & 0xff;
		g.y = (new_px >> 8) & 0xff;
		b.x = *old_px & 0xff;
		b.y = new_px & 0xff;
		r.x = r.x * (1 - mult_row) + r.y * mult_row;
		b.x = b.x * (1 - mult_row) + b.y * mult_row;
		g.x = g.x * (1 - mult_row) + g.y * mult_row;
		*old_px = (r.x << 16) + (g.x << 8) + b.x;
	}
}

static void	update_banner_state(t_game *game, t_bans *banner)
{
	time_t	time;

	if (game->game_stage == PLAY || banner->move == 0)
		return ;
	banner->last_change = get_time();
	time = banner->last_change - game->screen.last_frame_time;
	banner->pos += ((float)banner->move * time) / P_BAN_SPEED;
	if (banner->pos > 1)
		banner->pos = 1;
	if (banner->pos < 0)
		banner->pos = 0;
	if (banner->pos == 0 || banner->pos == 1)
		banner->move = 0;
}

void	animate_banners(t_game *game, t_bans *banners)
{
	if (game->game_stage == INTRO)
	{
		if ((game->texts.draw_mode & M_INTRO_PL) == 0)
		{
			game->game_stage = PLAY;
			return ;
		}
		update_banner_state(game, banners);
		if ((banners->pos == 1) && (get_time() - game->texts.bans.last_change
				> P_INTRO_TIME))
			banners->move = -1;
		if (banners->pos == 0)
			game->game_stage = PLAY;
	}
	if (game->game_stage == LOSE && (game->texts.draw_mode & M_GAME_OVER_PL))
		update_banner_state(game, banners);
	if (game->game_stage == WIN && (game->texts.draw_mode & M_VICTORY_PL))
		update_banner_state(game, banners);
	if (game->game_stage != PLAY)
		display_banner(game, &game->texts.bans,
			&(game->texts.bans.img[game->game_stage]));
}
