/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   upscaler.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 17:59:10 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/04 18:35:53 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	upscale_screen(t_game *game)
{
	float		step;
	t_coords	new_pix;
	int			old_row;
	t_pos		old_pos;
	int			new_size;

	step = 1.0f / WIN_UPSC_FACTOR;
	new_pix.x = 0;
	new_size = game->src_upscaled.width * game->src_upscaled.height;
	while (new_pix.x < new_size)
	{
		new_pix.y = 0;
		old_pos.x = 0;
		old_row = ((int)old_pos.y) * game->screen.win_w;
		while (new_pix.y < game->src_upscaled.width)
		{
			game->src_upscaled.addr[new_pix.x]
				= game->screen.pixels[old_row + (int)old_pos.x];
			old_pos.x += step;
			(new_pix.y)++;
			(new_pix.x)++;
		}
		old_pos.y += step;
	}
}
