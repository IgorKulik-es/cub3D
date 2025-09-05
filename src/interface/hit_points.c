/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_points.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:13:38 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/05 18:26:29 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_hp_on_screen(t_game *game)
{
	int	side_offset;
	int	top_offset;
	int	counter;

	if ((game->texts.draw_mode & M_VISIBLE_HP) && game->game_over == 0)
	{
		side_offset = game->screen.win_w - (WIN_UI_OFFSET + game->texts
				.hp_resized.width * game->player.hp);
		top_offset = game->screen.win_h
			- WIN_UI_OFFSET - game->texts.hp_resized.width;
		counter = 0;
		while (counter < game->player.hp)
		{
			put_img_to_srceen(game, &game->texts.hp_resized,
				side_offset, top_offset);
			counter++;
			side_offset += game->texts.hp_resized.width;
		}
	}
}
