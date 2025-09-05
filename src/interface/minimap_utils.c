/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:17:45 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/09/02 13:00:36 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_minimap	get_minimap_params(t_game *game)
{
	t_minimap	m;
	t_coords	minimap_max;
	t_pos		scale;

	minimap_max.x = game->screen.win_w / 4;
	minimap_max.y = game->screen.win_h / 4;
	scale.x = (float)minimap_max.x / game->map.width;
	scale.y = (float)minimap_max.y / game->map.height;
	m.scale = (int)fminf(scale.x, scale.y);
	if (m.scale < 1)
		m.scale = 1;
	game->screen.minimap_scale = m.scale;
	m.offset_x = 10;
	m.offset_y = 10;
	return (m);
}

void	put_pixel(t_screen *screen, int x, int y, int color)
{
	if (x < 0 || x >= screen->win_w || y < 0 || y >= screen->win_h)
		return ;
	screen->pixels[y * screen->win_w + x] = color;
}

static t_line	init_line_params(t_coords p, t_coords h)
{
	t_line	line;

	line.d.x = abs(h.x - p.x);
	line.d.y = -abs(h.y - p.y);
	if (p.x < h.x)
		line.s.x = 1;
	else
		line.s.x = -1;
	if (p.y < h.y)
		line.s.y = 1;
	else
		line.s.y = -1;
	line.err = line.d.x + line.d.y;
	return (line);
}

void	draw_line(t_screen *screen, t_coords p, t_coords h, int color)
{
	t_line	line;
	int		e2;

	line = init_line_params(p, h);
	while (1)
	{
		put_pixel(screen, p.x, p.y, color);
		if (p.x == h.x && p.y == h.y)
			break ;
		e2 = 2 * line.err;
		if (e2 >= line.d.y)
		{
			line.err += line.d.y;
			p.x += line.s.x;
		}
		if (e2 <= line.d.x)
		{
			line.err += line.d.x;
			p.y += line.s.y;
		}
	}
}

void	draw_square(t_screen *screen, int x, int y, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < screen->minimap_scale)
	{
		j = 0;
		while (j < screen->minimap_scale)
		{
			put_pixel(screen, x + j, y + i, color);
			j++;
		}
		i++;
	}
}
