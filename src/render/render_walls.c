/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:22:04 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/10 15:36:18 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	put_vert_line(t_game *game, float x, t_hit hit);
static int	get_wall_pixel(t_game *game, t_hit hit, float height);

void	draw_walls(t_game *game)
{
	int	column;

	column = -1;
	while (++column < game->screen.win_w)
		put_vert_line(game, column, game->hits[column]);
}

static void	put_vert_line(t_game *game, float x, t_hit hit)
{
	int	top;
	int	bot;
	int	index;
	int	pixel;
	float	dark;

	index = (int)game->screen.win_h - 1;
	pixel = (int)x;
	top = (int)((game->screen.win_h / 2) * (1 + 1 / hit.dist));
	bot = (int)((game->screen.win_h / 2) * (1 - 1 / hit.dist));
	if (top > game->screen.win_h - 1)
		top = game->screen.win_h - 1;
	if (bot < 0)
		bot = 0;
	dark = (2 / hit.dist);
	if (dark > 1)
		dark = 1;
	while (index > 0)
	{
		if (index > top && !(game->texts.draw_mode & M_CEIL_TEXTURE))
			(game->screen.pixels)[pixel] = C_SKY_BLUE;
		else if (index >= bot && index <= top)
			(game->screen.pixels)[pixel] = rgb_shift(get_wall_pixel
				(game, hit, (float)(top - index) / (float)(top - bot + 1)), dark, dark, dark);
		else if (!(game->texts.draw_mode & M_FL_TEXTURE))
			(game->screen.pixels)[pixel] = C_FLOOR_SAND;
		pixel += game->screen.win_w;
		index--;
	}
}

static int	get_wall_pixel(t_game *game, t_hit hit, float height)
{
	int	coord;

	if (hit.dist < 1)
		height = (1 - hit.dist) / 2 + hit.dist * height;
	coord = (int)(hit.column * game->texts.wall_n.width) + (int)(height
			* game->texts.wall_n.height) * game->texts.wall_n.width;
	if (hit.type == 'N')
		return ((game->texts.wall_n.addr)[coord]);
	else if (hit.type == 'S')
		return ((game->texts.wall_s.addr)[coord]);
	else if (hit.type == 'W')
		return ((game->texts.wall_w.addr)[coord]);
	else if (hit.type == 'E')
		return ((game->texts.wall_e.addr)[coord]);
	else if (hit.type == 'D')
		return ((game->texts.door.addr)[coord]);
	else if (hit.type == DOOR_WALL)
		return ((game->texts.door_w.addr)[coord]);
	else if (hit.type == T_EXIT)
		return ((((game->exit.frames)[game->exit.c_frame])->addr)[coord]);
	else
		return (0);
}
