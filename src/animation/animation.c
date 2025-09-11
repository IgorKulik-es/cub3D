/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:47 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 19:08:42 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	update_enem_frame(t_game *game, t_entity *guy, t_anim *anim)
{
	time_t	time;

	(void)game;
	if (anim->active == false)
		return ;
	time = get_time() - anim->last_frame;
	if (((guy->mode != ACTION) && (time * guy->state > anim->time_per_frame))
		|| (guy->mode == ACTION && time * guy->state > anim->time_per_frame))
	{
		(anim->c_frame)++;
		anim->last_frame += time;
	}
	if (anim->c_frame >= anim->num_fr)
	{
		anim->c_frame = 0;
		if (guy->mode == ACTION)
		{
			anim->active = false;
			if (guy->dist < E_DAM_RADIUS)
				damage_player(game, guy);
		}
	}
}

void	update_exit_frame(t_anim *exit)
{
	time_t	time;

	time = get_time() - exit->last_frame;
	if (2 * time > exit->time_per_frame)
	{
		exit->last_frame += time;
		(exit->c_frame)++;
	}
	if (exit->c_frame >= exit->num_fr)
		exit->c_frame = 0;
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
