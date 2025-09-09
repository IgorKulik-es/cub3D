/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_frame.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:13:08 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/09 15:47:17 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int		get_wall_pixel(t_game *game, t_hit hit, float height);
void	put_vert_line(t_game *game, float x, t_hit hit);
void	put_sprites_on_screen(t_game *game);
void	draw_walls(t_game *game);
void	cast_all_rays(t_game *game);

int	render_frame(t_game *game)
{
	update_all_positions(game);
	restore_color(game);
	game->screen.last_frame_time = get_time();
	cast_all_rays(game);
	draw_floors(game, &game->player);
	draw_walls(game);
	put_sprites_on_screen(game);
	tint_screen(game);
	put_hp_on_screen(game);
	draw_minimap(game);
	put_fps_counter(game, get_time());
	animate_banners(game, &game->texts.bans);
	upscale_screen(game);
	mlx_put_image_to_window(game->mlx, game->win, game->scr_upscaled.img, 0, 0);
	return (0);
}

void	put_sprites_on_screen(t_game *game)
{
	int		ind_to_put;
	int		ind_find;
	int		find;
	float	curr_max_dist;
	float	last_max_dist;

	ind_to_put = -1;
	last_max_dist = game->map.width;
	find = 0;
	while (++ind_to_put < game->num_enemies)
	{
		ind_find = -1;
		curr_max_dist = 0;
		while (++ind_find < game->num_enemies)
		{
			if (game->enemies[ind_find].dist > curr_max_dist
				&& game->enemies[ind_find].dist < last_max_dist)
			{
				find = ind_find;
				curr_max_dist = game->enemies[ind_find].dist;
			}
		}
		last_max_dist = curr_max_dist;
		put_entity(game, &(game->enemies[find]));
	}
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
