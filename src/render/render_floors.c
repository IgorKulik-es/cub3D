/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:53:53 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 20:42:44 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_hor_line(t_game *game, t_pos h_d, t_pos start, t_pos step);
static void	put_darkened_pixel(t_game *game, t_coords width,
				int text_pixel, float dark);

void	draw_floors(t_game *game, t_player *player)
{
	t_pos	height_dist;
	t_pos	step;
	t_pos	start;
	int		half_h;

	if (game->texts.draw_mode == M_NO_TEXTURE)
		return ;
	height_dist.x = 0;
	half_h = game->screen.win_h / 2;
	while (height_dist.x < half_h)
	{
		height_dist.y = height_dist.x / (float)half_h;
		height_dist.y = 1 / (1 - height_dist.y);
		start = subtr_vectors(player->facing, player->camera);
		start = mult_scalar (start, height_dist.y);
		start = add_vectors(start, player->pos);
		step = mult_scalar(player->camera, height_dist.y / game->screen.half_w);
		draw_hor_line(game, height_dist, start, step);
		(height_dist.x) += 1;
		if (height_dist.y > game->d_max)
			return ;
	}
}

static void	draw_hor_line(t_game *game, t_pos h_d, t_pos start, t_pos step)
{
	int			last_pixel;
	int			text_pixel;
	float		dark;
	t_coords	width;
	t_pos		pos_on_tile;

	width.y = (int)h_d.x * game->screen.win_w;
	width.x = (game->screen.win_h - (int)h_d.x) * game->screen.win_w;
	dark = 2 / h_d.y;
	if (dark > 1)
		dark = 1;
	last_pixel = width.y + game->screen.win_w;
	while (width.y < last_pixel)
	{
		pos_on_tile.x = start.x - floorf(start.x);
		pos_on_tile.y = start.y - floorf(start.y);
		text_pixel = ((int)(pos_on_tile.x * game->texts.floor.width))
			* game->texts.floor.width + (int)(pos_on_tile.y
				* game->texts.floor.width);
		put_darkened_pixel(game, width, text_pixel, dark);
		start = add_vectors(start, step);
		(width.x)++;
		(width.y)++;
	}
}

static void	put_darkened_pixel(t_game *game, t_coords width,
			int text_pixel, float dark)
{
	if (game->texts.draw_mode & M_FL_TEXTURE)
	{
		if (game->mode & M_DARK)
			game->screen.pixels[width.x] = rgb_shift
				(game->texts.floor.addr[text_pixel], dark, dark, dark);
		else
			game->screen.pixels[width.x] = game->texts.floor.addr[text_pixel];
	}
	if (game->texts.draw_mode & M_CEIL_TEXTURE)
	{
		if (game->mode & M_DARK)
			game->screen.pixels[width.y] = rgb_shift
				(game->texts.ceiling.addr[text_pixel], dark, dark, dark);
		else
			game->screen.pixels[width.y] = game->texts.ceiling.addr[text_pixel];
	}
}
