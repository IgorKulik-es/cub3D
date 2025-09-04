/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_floors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 13:53:53 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/04 17:16:44 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_hor_line(t_game *game, int height, t_pos start, t_pos step);

void	draw_floors(t_game *game, t_player *player)
{
	int		height;
	t_pos	step;
	t_pos	start;
	float	dist;
	int		half_h;

	if (game->texts.draw_mode == M_NO_TEXTURE)
		return ;
	height = 0;
	half_h = game->screen.win_h / 2;
	while (height < half_h)
	{
		dist = height / (float)half_h;
		dist = 1 / (1 - dist);
		start = subtr_vectors(player->facing, player->camera);
		start = mult_scalar (start, dist);
		start = add_vectors(start, player->pos);
		step = mult_scalar(player->camera, dist / game->screen.half_w);
		draw_hor_line(game, height, start, step);
		height++;
	}
}

void	draw_hor_line(t_game *game, int height, t_pos start, t_pos step)
{
	int			last_pixel;
	int			text_pixel;
	t_coords	width;
	t_pos		pos_on_tile;

	width.y = height * game->screen.win_w;
	width.x = (game->screen.win_h - height) * game->screen.win_w;
	last_pixel = width.y + game->screen.win_w;
	while (width.y < last_pixel)
	{
		pos_on_tile.x = start.x - floorf(start.x);
		pos_on_tile.y = start.y - floorf(start.y);
		text_pixel = ((int)(pos_on_tile.x * TEXTURE_SIZE))
			* TEXTURE_SIZE + (int)(pos_on_tile.y * TEXTURE_SIZE);
		if (game->texts.draw_mode & M_FL_TEXTURE)
			game->screen.pixels[width.x] = game->texts.floor.addr[text_pixel];
		if (game->texts.draw_mode & M_CEIL_TEXTURE)
			game->screen.pixels[width.y] = game->texts.ceiling.addr[text_pixel];
		start = add_vectors(start, step);
		(width.x)++;
		(width.y)++;
	}
}


