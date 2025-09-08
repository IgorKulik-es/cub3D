/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   post_processing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:59:10 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/08 11:54:29 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	rgb_shift(int color, float r_mult, float g_mult, float b_mult);

void	upscale_screen(t_game *game)
{
	float		step;
	t_coords	new_pix;
	int			old_row;
	t_pos		old_pos;
	int			new_size;

	step = 1.0f / WIN_UPSC_FACTOR;
	new_pix.x = 0;
	new_size = game->scr_upscaled.width * game->scr_upscaled.height;
	old_pos.y = 0;
	while (new_pix.x < new_size)
	{
		new_pix.y = 0;
		old_pos.x = 0;
		old_row = ((int)old_pos.y) * game->screen.win_w;
		while (new_pix.y < game->scr_upscaled.width)
		{
			game->scr_upscaled.addr[new_pix.x]
				= game->screen.pixels[old_row + (int)old_pos.x];
			old_pos.x += step;
			(new_pix.y)++;
			(new_pix.x)++;
		}
		old_pos.y += step;
	}
}

void	tint_screen(t_game *game)
{
	int	ind_pixel;
	int	last_pixel;

	ind_pixel = 0;
	last_pixel = game->screen.win_w * game->screen.win_h;
	while (ind_pixel < last_pixel)
	{
		game->screen.pixels[ind_pixel] = rgb_shift(game->screen
				.pixels[ind_pixel], game->tint.r, game->tint.g, game->tint.b);
		ind_pixel++;
	}
}

static int	rgb_shift(int color, float r_mult, float g_mult, float b_mult)
{
	int	r;
	int	g;
	int	b;

	r = (color >> 16) & 0xff;
	g = (color >> 8) & 0xff;
	b = color & 0xff;
	r = r * r_mult;
	g = g * g_mult;
	b = b * b_mult;
	if (r > 0xff)
		r = 0xff;
	if (g > 0xff)
		g = 0xff;
	if (b > 0xff)
		b = 0xff;
	return ((r << 16) + (g << 8) + b);
}
