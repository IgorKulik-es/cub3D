/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:14:58 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/09/11 20:33:37 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	rotate_player_with_mouse(t_game *game, int delta_x);

int	mouse_move(int x, int y, t_game *game)
{
	int	delta_x;

	(void)y;
	if (game->game_stage != PLAY)
		return (1);
	if (game->last_mouse_x == -1)
	{
		game->last_mouse_x = x;
		return (0);
	}
	delta_x = x - game->last_mouse_x;
	rotate_player_with_mouse(game, delta_x);
	game->last_mouse_x = x;
	return (0);
}

static void	rotate_player_with_mouse(t_game *game, int delta_x)
{
	float	angle;

	angle = delta_x * SENSITIVITY;
	game->player.facing = rotate_vector(game->player.facing, angle);
	game->player.camera = rotate_vector(game->player.camera, angle);
}
