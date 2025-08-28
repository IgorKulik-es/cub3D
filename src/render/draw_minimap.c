/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:46:27 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/28 13:02:38 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	put_pixel(t_screen *screen, int x, int y, int color)
{
	if (x < 0 || x >= screen->win_w || y < 0 || y >= screen->win_h)
		return ;
	screen->pixels[y * screen->win_w + x] = color;
}

static void	draw_line(t_screen *screen, t_coords p, t_coords h, int color)
{
	t_coords	d;
	t_coords	s;
	int			err;
	int			e2;

	d.x = abs(h.x - p.x);
	d.y = -abs(h.y - p.y);
	if (p.x < h.x)
		s.x = 1;
	else
		s.x = -1;
	if (p.y < h.y)
		s.y = 1;
	else
		s.y = -1;
	err = d.x + d.y;
	while (1)
	{
		put_pixel(screen, p.x, p.y, color);
		if (p.x == h.x && p.y == h.y)
			break ;
		e2 = 2 * err;
		if (e2 >= d.y)
		{
			err += d.y;
			p.x += s.x;
		}
		if (e2 <= d.x)
		{
			err += d.x;
			p.y += s.y;
		}
	}
}

static void	draw_square(t_screen *screen, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < MINIMAP_SCALE)
	{
		j = 0;
		while (j < MINIMAP_SCALE)
		{
			put_pixel(screen, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

static void	draw_minimap_cell(t_game *game, int i, int j)
{
	int	x;
	int	y;

	x = MINIMAP_OFFSET_X + j * MINIMAP_SCALE;
	y = MINIMAP_OFFSET_Y + i * MINIMAP_SCALE;
	if (game->map.map[i][j] == '1')
		draw_square(&game->screen, x, y, 0x333333);
	else if (game->map.map[i][j] == '0')
		draw_square(&game->screen, x, y, 0xFFFFFF);
	else if (game->map.map[i][j] == 'D')
		draw_square(&game->screen, x, y, 0x996633);
}

static void	draw_minimap_rays(t_game *game, t_coords p)
{
	int		col;
	t_hit	hit;
	t_coords	h;

	col = 0;
	while (col < game->screen.win_w)
	{
		hit = cast_ray(game, col);
		h.x = MINIMAP_OFFSET_X + (int)(hit.point.x * MINIMAP_SCALE);
		h.y = MINIMAP_OFFSET_Y + (int)(hit.point.y * MINIMAP_SCALE);
		draw_line(&game->screen, p, h, 0x00FF00);
		col += 1;
	}
}

void	draw_minimap(t_game *game)
{
	int			i;
	int			j;
	t_coords	p;

	i = 0;
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			draw_minimap_cell(game, i, j);
			j++;
		}
		i++;
	}
	p.x = MINIMAP_OFFSET_X + (int)(game->player.pos.x * MINIMAP_SCALE);
	p.y = MINIMAP_OFFSET_Y + (int)(game->player.pos.y * MINIMAP_SCALE);
	draw_square(&game->screen, p.x - MINIMAP_SCALE / 2, p.y - MINIMAP_SCALE / 2, 0x0000FF);
	draw_minimap_rays(game, p);
}
