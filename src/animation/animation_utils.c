/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:59:05 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/09 19:12:48 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	correct_pixel(t_game *game, int	*pixel)
{
	if (pixel == NULL)
		return (false);
	if (*pixel < 0)
	{
		*pixel = 0;
		return (false);
	}
	if (*pixel > game->screen.win_w - 1)
	{
		*pixel = game->screen.win_w - 1;
		return (false);
	}
	return (true);
}

t_pos	dist_to_entity(t_game *game, t_entity *guy)
{
	t_pos		view;
	t_pos		transform;
	t_pos		result;
	float		mult;
	t_player	*player;

	player = &(game->player);
	result.x = 0;
	result.y = 0;
	view = subtr_vectors(guy->pos, player->pos);
	guy->view = view;
	guy->dist = vector_length(view);
	transform.y = player->inv_det
		* (view.x * player->camera.y - view.y * player->camera.x);
	transform.x = -player->inv_det
		* (view.x * player->facing.y - view.y * player->facing.x);
	mult = (transform.x / transform.y);
	result.x = (game->screen.win_w / 2) * (1 + mult);
	result.y = transform.y;
	return (result);
}

void	determine_animation(t_entity *guy)
{
	int		index;

	index = -1;
	if ((guy->state == E_STATE_ANGRY && guy->dist < E_ATT_RANGE)
		|| (guy->mode == ACTION && guy->anims[ACTION].active))
		guy->mode = ACTION;
	else
		guy->mode = WALK_FRONT;
	if (guy->mode != ACTION)
		guy->mode = guy->turn;
	while (++index < NUM_ANIM)
		guy->anims[index].active = false;
	guy->anims[guy->mode].active = true;
}
