/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:13:08 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/27 13:26:10 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int		get_wall_pixel(t_game *game, t_hit hit, float height);
void	put_vert_line(t_game *game, float x, t_hit hit);

void	create_screen(t_game *game)
{
	t_screen	*screen;
	int			dummy;

	screen = &(game->screen);
	game->win = mlx_new_window(game->mlx, screen->win_w
			, screen->win_h, "cub3D");
	screen->img = mlx_new_image(game->mlx, screen->win_w, screen->win_h);
	screen->pixels = (int *)mlx_get_data_addr(screen->img,
			&dummy, &dummy, &dummy);
}

int	render_frame(t_game *game)
{
	float	column;
	t_hit	hit;
	time_t	time;
	// time_t	fps;

	column = 0;
	if (game->player.moving)
		move_player(game, game->player.moving);
	if (game->player.rotating)
		rotate_player(game, game->player.rotating);
	time = get_time();
	// fps = T_MICROSEC / (time - game->screen.last_frame_time);
	game->screen.last_frame_time = time;
	while (column < game->screen.win_w)
	{
		hit = cast_ray(game, column);
		put_vert_line(game, column, hit);
		column += 1;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->screen.img, 0, 0);
	// printf("fps: %d\n", (int)fps);
	return (0);
}

void	put_vert_line(t_game *game, float x, t_hit hit)
{
	int	top;
	int	bot;
	int	index;
	int	pixel;

	index = (int)game->screen.win_h - 1;
	pixel = (int)x;
	top = (int)((game->screen.win_h / 2) * (1 + 1 / hit.dist));
	bot = (int)((game->screen.win_h / 2) * (1 - 1 / hit.dist));
	if (top > game->screen.win_h - 1)
		top = game->screen.win_h - 1;
	if (bot < 0)
		bot = 0;
	while (index > 0)
	{
		if (index > top)
			(game->screen.pixels)[pixel] = C_SKY_BLUE;
		else if (index >= bot)
			(game->screen.pixels)[pixel] = get_wall_pixel
				(game, hit, (float)(top - index) / (float)(top - bot + 1));
		else
			(game->screen.pixels)[pixel] = C_FLOOR_SAND;
		pixel += game->screen.win_w;
		index--;
	}
}

int	get_wall_pixel(t_game *game, t_hit hit, float height)
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
		return (((game->texts.wall_e.addr)[coord]));
	else
		return (0);
}


