/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   effects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:28:30 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 12:38:12 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	shift_color_component(float *color, float shift, float target);

void	blood_effect(t_game *game, float red)
{
	game->tint.r = red;
	game->tint.g = WIN_DARK_FACTOR / 3;
	game->tint.b = WIN_DARK_FACTOR / 3;
}

void	restore_color(t_game *game, float target_tint)
{
	time_t	time;
	float	shift;

	if (game->game_stage == LOSE)
		return ;
	time = get_time();
	shift = (time - game->screen.last_frame_time) / P_COLOR_SPEED;
	shift_color_component(&game->tint.r, shift, target_tint);
	shift_color_component(&game->tint.g, shift, target_tint);
	shift_color_component(&game->tint.b, shift, target_tint);
}

static void	shift_color_component(float *color, float shift, float target)
{
	if (*color > target)
	{
		*color -= shift;
		if (*color < target)
			*color = target;
	}
	else if (*color < target)
	{
		*color += shift;
		if (*color > target)
			*color = target;
	}
}
