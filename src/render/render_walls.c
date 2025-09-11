/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_walls.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:22:04 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 19:00:29 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_wall_pixel(t_game *game, t_hit hit, int coord);
static void	draw_floor_ceiling(t_game *game, int column, t_coords borders);
static void	draw_wall_texture(t_game *game, int column,
				t_coords borders, t_hit hit);
static void	initialize_wall_steps(t_game *game, t_coords borders,
				t_hit hit, t_pos *steps);

void	draw_walls(t_game *game)
{
	int			column;
	t_coords	borders;

	column = -1;
	while (++column < game->screen.win_w)
	{
		borders.x = (int)(game->screen.half_h
				* (1 + 1 / (game->hits)[column].dist));
		borders.y = (int)(game->screen.half_h
				* (1 - 1 / (game->hits)[column].dist));
		if (borders.x > game->screen.win_h - 1)
			borders.x = game->screen.win_h - 1;
		if (borders.y < 0)
			borders.y = 0;
		draw_floor_ceiling(game, column, borders);
		draw_wall_texture(game, column, borders, (game->hits)[column]);
	}
}

static int	get_wall_pixel(t_game *game, t_hit hit, int coord)
{
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

void	draw_floor_ceiling(t_game *game, int column, t_coords borders)
{
	int	pixel;
	int	pixel_max;

	if (!(game->texts.draw_mode & M_CEIL_TEXTURE))
	{
		pixel = column;
		pixel_max = column + borders.x * game->screen.win_w;
		while (pixel < pixel_max)
		{
			game->screen.pixels[pixel] = game->texts.top_color;
			pixel += game->screen.win_w;
		}
	}
	if (game->texts.draw_mode & M_FL_TEXTURE)
		return ;
	pixel = column + borders.y * game->screen.win_w;
	pixel_max = game->screen.win_h * game->screen.win_w;
	while (pixel < pixel_max)
	{
		game->screen.pixels[pixel] = game->texts.bot_color;
		pixel += game->screen.win_w;
	}
}

void	draw_wall_texture(t_game *game, int column, t_coords borders, t_hit hit)
{
	t_coords	px_screen;
	t_pos		steps;
	int			color;
	int			text_column;
	float		dark;

	initialize_wall_steps(game, borders, hit, &steps);
	dark = (WIN_LIGHT_RADIUS / hit.dist);
	if (dark > 1)
		dark = 1;
	text_column = game->texts.wall_n.width * hit.column;
	px_screen.x = borders.y * game->screen.win_w + column;
	px_screen.y = borders.x * game->screen.win_w;
	while (px_screen.x < px_screen.y)
	{
		color = get_wall_pixel(game, hit, ((int)steps.y)
				* game->texts.wall_n.width + text_column);
		if (((game->texts.draw_mode & M_CEIL_TEXTURE)
				|| (game->texts.draw_mode & M_FL_TEXTURE))
			&& (game->mode & M_DARK))
			color = rgb_shift(color, dark, dark, dark);
		game->screen.pixels[px_screen.x] = color;
		px_screen.x += game->screen.win_w;
		steps.y += steps.x;
	}
}

static void	initialize_wall_steps(t_game *game, t_coords borders,
		t_hit hit, t_pos *steps)
{
	steps->y = 0;
	steps->x = (float)game->texts.wall_n.height / (borders.x - borders.y + 1);
	if (hit.dist < 1)
	{
		steps->y = game->texts.wall_n.height * (1 - hit.dist) * 0.5f;
		steps->x *= hit.dist;
	}
}
