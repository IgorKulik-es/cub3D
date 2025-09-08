/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 16:04:58 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/08 11:27:40 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	find_closest_entity(t_game *game, t_door *door);

t_door	*find_door(t_game *game, int x, int y)
{
	int	index;

	index = 0;
	while (index < game->num_doors)
	{
		if ((game->doors[index]).x == x && (game->doors[index]).y == y)
			return (&(game->doors[index]));
		index++;
	}
	return (NULL);
}

void	move_door(t_game *game, t_door *door)
{
	float	incr;
	time_t	time;
	int		dist;

	time = get_time();
	dist = find_closest_entity(game, door);
	if (dist <= 1)
		door->last_open = time;
	if (door->state == D_STATE_OPEN && time - door->last_open > P_DOOR_CL_TIME
		&& dist > 1)
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

int	find_closest_entity(t_game *game, t_door *door)
{
	int	dist_to_ent;
	int	min_dist;
	int	index;

	index = 0;
	min_dist = abs(door->x - (int)floor(game->player.pos.x))
		+ abs(door->y - (int)floor(game->player.pos.y));
	while (index < game->num_enemies)
	{
		dist_to_ent = abs(door->x - (int)floor(game->enemies[index].pos.x))
			+ abs(door->y - (int)floor(game->enemies[index].pos.y));
		if (min_dist > dist_to_ent)
			min_dist = dist_to_ent;
		index++;
	}
	return (min_dist);
}
