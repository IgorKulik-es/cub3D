/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:04:58 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/27 16:34:16 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	move_door(t_game *game, t_door *door)
{
	float	incr;

	if (door->moving == 0)
		return ;
	incr = door->moving * (float)(get_time() - game->screen.last_frame_time)
		/ P_DOOR_SPEED;
	door->width += incr;
	if (door->width > 1)
	{
		door->width = 1;
		door->state = D_STATE_CLOSED;
	}
	if (door->width < 0)
	{
		door->width = 0;
		door->state = D_STATE_OPEN;
	}
}
