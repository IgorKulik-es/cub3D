/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 11:17:45 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/09/02 12:30:19 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_minimap	get_minimap_params(t_game *game)
{
	t_minimap	m;
	t_coords	minimap_max;
	t_pos	scale;

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

void	draw_line(t_screen *screen, t_coords p, t_coords h, int color)
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
