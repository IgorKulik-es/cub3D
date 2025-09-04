/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 11:46:27 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/09/04 13:52:39 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_minimap_cell(t_game *game, t_minimap *m, int i, int j)
{
	int	x;
	int	y;

	x = m->offset_x + j * m->scale;
	y = m->offset_y + i * m->scale;
	if (game->map.map[i][j] == '0')
		draw_square(&game->screen, x, y, 0xFFFFFF);
	else if (game->map.map[i][j] == 'D')
		draw_square(&game->screen, x, y, 0x996633);
	else
		draw_square(&game->screen, x, y, 0x333333);
}

static void	draw_minimap_rays(t_game *game, t_minimap *m, t_coords p)
{
	int			col;
	t_pos		hit;
	t_coords	h;

	col = 0;
	while (col < game->screen.win_w)
	{
		hit = game->hits[col];
		h.x = m->offset_x + (int)(hit.x * m->scale);
		h.y = m->offset_y + (int)(hit.y * m->scale);
		draw_line(&game->screen, p, h, 0x00FF00);
		col += 1;
	}
}

static void	draw_minimap_enemies(t_game *game, t_minimap *m)
{
	int			k;
	int			x;
	int			y;
	t_entity	enemy;

	k = 0;
	while (k < game->num_enemies)
	{
		enemy = game->enemies[k];
		x = m->offset_x + (int)(enemy.pos.x * m->scale);
		y = m->offset_y + (int)(enemy.pos.y * m->scale);
		draw_square(&game->screen, x - m->scale / 4,
			y - m->scale / 4, 0xFF0000);
		k++;
	}
}

void	draw_minimap(t_game *game)
{
	int			i;
	int			j;
	t_coords	p;
	t_minimap	m;

	i = 0;
	m = get_minimap_params(game);
	while (i < game->map.height)
	{
		j = 0;
		while (j < game->map.width)
		{
			draw_minimap_cell(game, &m, i, j);
			j++;
		}
		i++;
	}
	p.x = m.offset_x + (int)(game->player.pos.x * m.scale);
	p.y = m.offset_y + (int)(game->player.pos.y * m.scale);
	draw_square(&game->screen, p.x - m.scale / 2, p.y - m.scale / 2, 0x0000FF);
	draw_minimap_rays(game, &m, p);
	draw_minimap_enemies(game, &m);
}
