/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_screen.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:13:08 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/04 19:55:11 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int		get_wall_pixel(t_game *game, t_hit hit, float height);
void	put_vert_line(t_game *game, float x, t_hit hit);
void	put_sprites_on_screen(t_game *game);
void	draw_walls(t_game *game);
void	cast_all_rays(t_game *game);

void	create_screen(t_game *game)
{
	t_screen	*screen;
	int			dummy;

	screen = &(game->screen);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	screen->img = mlx_new_image(game->mlx, screen->win_w, screen->win_h);
	screen->pixels = (int *)mlx_get_data_addr(screen->img,
			&dummy, &dummy, &dummy);
	game->src_upscaled.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->src_upscaled.addr = (int *)mlx_get_data_addr(game->src_upscaled.img,
			&(game->src_upscaled.bpp), &(game->src_upscaled.line_length),
			&(game->src_upscaled.endian));
	game->src_upscaled.width = WIN_WIDTH;
	game->src_upscaled.height = WIN_HEIGHT;
}

int	render_frame(t_game *game)
{
	update_all_positions(game);
	game->screen.last_frame_time = get_time();
	cast_all_rays(game);
	draw_floors(game, &game->player);
	draw_walls(game);
	put_sprites_on_screen(game);
	draw_minimap(game);
	upscale_screen(game);
	mlx_put_image_to_window(game->mlx, game->win, game->src_upscaled.img, 0, 0);
	put_fps_counter(game, get_time());
	return (0);
}

void	put_sprites_on_screen(t_game *game)
{
	int	index;

	index = 0;
	while (index < game->num_enemies)
	{
		put_entity(game, &game->enemies[index]);
		index++;
	}
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
		if (index > top && !(game->texts.draw_mode & M_CEIL_TEXTURE))
			(game->screen.pixels)[pixel] = C_SKY_BLUE;
		else if (index >= bot && index <= top)
			(game->screen.pixels)[pixel] = get_wall_pixel
				(game, hit, (float)(top - index) / (float)(top - bot + 1));
		else if (!(game->texts.draw_mode & M_FL_TEXTURE))
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
		return ((game->texts.wall_e.addr)[coord]);
	else if (hit.type == DOOR_WALL)
		return ((game->texts.wall_n.addr)[coord]);
	else
		return (0);
}
void	cast_all_rays(t_game *game)
{
	t_hit	hit;
	int		column;

	column = 0;
	game->d_max = 0;
	while (column < game->screen.win_w)
	{
		hit = cast_ray(game, column);
		game->hits[column] = hit;
		if (hit.dist > game->d_max)
			game->d_max = hit.dist;
		column++;
	}
}



void	draw_walls(t_game *game)
{
	int	column;

	column = -1;
	while (++column < game->screen.win_w)
		put_vert_line(game, column, game->hits[column]);
}


