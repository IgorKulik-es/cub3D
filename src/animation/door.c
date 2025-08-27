/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:04:58 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/27 19:46:41 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_door(t_game *game, t_door *door)
{
	float	incr;
	time_t	time;
	int		dist_to_player;

	time = get_time();
	dist_to_player = abs(door->x - (int)floor(game->player.pos.x))
		+ abs(door->y - (int)floor(game->player.pos.y));
	if (dist_to_player <= 1)
		door->last_open = time;
	if (door->state == D_STATE_OPEN && time - door->last_open > P_DOOR_CL_TIME
		&& dist_to_player > 1)
		door->moving = 1;
	if (door->moving == 0)
		return ;
	incr = door->moving * (float)(time - game->screen.last_frame_time)
		/ P_DOOR_SPEED;
	door->width += incr;
	if (door->width > 0)
		door->state = D_STATE_CLOSED;
	if (door->width > 1 || door->width < 0)
	{
		door->state = (door->width > 0);
		door->moving = 0;
		door->width = door->state;
	}
}

void	open_door(t_game *game)
{
	t_coords	player;
	int			ind_door;

	ind_door = 0;
	player.x = floorf(game->player.pos.x);
	player.y = floorf(game->player.pos.y);
	while (ind_door < game->num_doors)
	{
		if (abs((game->doors[ind_door].x - player.x))
			+ abs(game->doors[ind_door].y - player.y) <= 1)
		{
			game->doors[ind_door].moving = -1;
			game->doors[ind_door].last_open = get_time();
		}
		ind_door++;
	}
}
