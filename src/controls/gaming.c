/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaming.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:25 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/28 20:19:43 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3D.h"

void	move_player(t_game *game, int key);
void	rotate_player(t_game *game, int key);

int	key_press(int key, t_game *game)
{
	if (key == ESC)
		close_game(game);
	if (key == W || key == S)
		game->player.moving = key;
	if (key == A || key == D)
		game->player.rotating = key;
	if (key == SPACE)
		open_door(game);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W || key == S)
		game->player.moving = 0;
	if (key == A || key == D)
		game->player.rotating = 0;
	return (0);
}

void	move_player(t_game *game, int key)
{
	t_pos	new;
	float	mult;

	mult = (get_time() - game->screen.last_frame_time) / (float)P_MOVE_SPEED;
	if (key == S)
		mult *= -1;
	new = mult_scalar(game->player.facing, mult);
	new = add_vectors(game->player.pos, new);
	if (check_collision(game, &new))
		game->player.pos = new;
}

void	rotate_player(t_game *game, int key)
{
	time_t		c_time;
	float		angle;

	c_time = get_time();
	angle = (c_time - game->screen.last_frame_time) / (float)P_ROTATE_SPEED;
	if (key == A)
		angle *= -1;
	game->player.facing = rotate_vector(game->player.facing, angle);
	game->player.camera = rotate_vector(game->player.camera, angle);
}
