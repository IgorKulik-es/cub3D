/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:13:08 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 18:47:56 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	put_vert_line(t_game *game, float x, float dist);

int	render_frame(t_game *game)
{
	float	column;
	float	distance;
	time_t	time;
	// time_t	fps;

	column = 0;
	if (game->moving)
		move_player(game, game->moving);
	time = get_time();
	// fps = T_MICROSEC / (time - game->screen.last_frame_time);
	game->screen.last_frame_time = time;
	while (column < game->screen.win_w)
	{
		distance = cast_ray(game, &(game->screen), column);
		put_vert_line(game, column, distance);
		column += 1;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	// printf("fps: %d\n", (int)fps);
	return (0);
}

void	put_vert_line(t_game *game, float x, float dist)
{
	int	top;
	int	bot;
	int	index;
	int	pixel;

	index = (int)game->screen.win_h - 1;
	pixel = (int)x;
	top = (int)((game->screen.win_h / 2) * (1 + 1 / dist));
	bot = (int)((game->screen.win_h / 2) * (1 - 1 / dist));
	if (top > game->screen.win_h - 1)
		top = game->screen.win_h - 1;
	if (bot < 0)
		bot = 0;
	while (index > 0)
	{
		if (index >= top)
			(game->screen.pixels)[pixel] = C_SKY_BLUE;
		else if (index >= bot)
			(game->screen.pixels)[pixel] = C_WALL_BROWN;
		else
			(game->screen.pixels)[pixel] = C_FLOOR_SAND;
		pixel += game->screen.win_w;
		index--;
	}
}
