/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gaming.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:25 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 17:26:26 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/cub3D.h"

void	move_player(t_game *game, int key);
void	rotate_player(t_game *game, int key);

int	key_press(int key, t_game *data)
{
	if (key == ESC)
		close_game(data);
	if (key == W || key == S)
		data->moving = key;
	if (key == A || key == D)
		rotate_player(data, key);
	return (0);
}

int	key_release(int key, t_game *game)
{
	if (key == W || key == S)
		game->moving = 0;
	return (0);
}

void	move_player(t_game *game, int key)
{
	t_pos	new;
	time_t	c_time;
	float	mult;
	int		column;
	int		row;

	game->moving = true;
	printf("hello\n");
	c_time = get_time();
	mult = (c_time - game->screen.last_frame_time) / (float)P_MOVE_SPEED;
	if (key == S)
		mult *= -1;
	new = mult_scalar(game->player.facing, mult);
	new = add_vectors(game->player.pos, new);
	column = (int)(floor(new.x));
	row = (int)(floor(new.y));
	if (new.x < 1.0f || new.x > game->map.width - 1 || new.y < 0
		|| new.y > game->map.height - 1)
	{
		game->moving = false;
		return ;
	}
	if (0 <= column && column < game->map.height && 0 <= row
		&& row < game->map.width && game->map.map[row][column] != '1')
		game->player.pos = new;
	game->moving = false;
}

void	rotate_player(t_game *game, int key)
{
	time_t	c_time;
	float	angle;

	game->moving = true;
	c_time = get_time();
	angle = (c_time - game->screen.last_frame_time) / (float)P_ROTATE_SPEED;
	if (key == D)
		angle *= -1;
	game->player.facing = rotate_vector(game->player.facing, angle);
	game->player.camera = rotate_vector(game->player.camera, angle);
	game->moving = false;
}
