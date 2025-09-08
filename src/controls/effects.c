/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:28:30 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/08 12:00:31 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	shift_color_component(float *color, float shift);

void	blood_effect(t_game *game, float red)
{
	game->tint.r = red;
	game->tint.g = WIN_DARK_FACTOR / 3;
	game->tint.b = WIN_DARK_FACTOR / 3;
}

void	restore_color(t_game *game)
{
	time_t	time;
	float	shift;

	if (game->game_over)
		return ;
	time = get_time();
	shift = (time - game->screen.last_frame_time) / P_COLOR_SPEED;
	shift_color_component(&game->tint.r, shift);
	shift_color_component(&game->tint.g, shift);
	shift_color_component(&game->tint.b, shift);
}

static void	shift_color_component(float *color, float shift)
{
	if (*color > WIN_DARK_FACTOR)
	{
		*color -= shift;
		if (*color < WIN_DARK_FACTOR)
			*color = WIN_DARK_FACTOR;
	}
	else if (*color < WIN_DARK_FACTOR)
	{
		*color += shift;
		if (*color > WIN_DARK_FACTOR)
			*color = WIN_DARK_FACTOR;
	}
}
