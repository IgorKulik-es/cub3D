/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 13:14:58 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/09/09 15:43:44 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3D.h"

static void rotate_player_with_mouse(t_game *game, int delta_x);

int mouse_move(int x, int y, t_game *game)
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

static void rotate_player_with_mouse(t_game *game, int delta_x)
{
	float	angle;
/* 	float	old_dir_x;
	float	old_plane_x; */

	angle = delta_x * SENSITIVITY;
	game->player.facing = rotate_vector(game->player.facing, angle);
	game->player.camera = rotate_vector(game->player.camera, angle);
/* 	old_dir_x = game->player.camera.x;
	game->player.camera.x = game->player.camera.x * cos(angle) - game->player.camera.y * sin(angle);
	game->player.camera.y = old_dir_x * sin(angle) + game->player.camera.y * cos(angle);
	old_plane_x = game->player.facing.x;
	game->player.facing.x = game->player.facing.x * cos(angle) - game->player.facing.y * sin(angle);
	game->player.facing.y = old_plane_x * sin(angle) + game->player.facing.y * cos(angle);
 */}
