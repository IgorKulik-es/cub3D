/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 13:59:05 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/12 11:54:01 by ikulik           ###   ########.fr       */
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

bool	check_entity_visibility(t_game *game, t_entity *guy)
{
	bool	is_in_front;

	guy->height = game->screen.win_h / guy->trans.y;
	guy->left_edge = guy->trans.x - guy->height / 2;
	guy->right_edge = guy->left_edge + guy->height;
	is_in_front = vectors_angle(game->player.facing, guy->view) < M_PI * 0.5f;
	if (is_in_front && correct_pixel(game, &guy->left_edge)
		&& game->hits[guy->left_edge].dist > guy->trans.y)
		return (true);
	if (is_in_front && correct_pixel(game, &guy->right_edge)
		&& game->hits[guy->right_edge].dist > guy->trans.y)
		return (true);
	if (((int)guy->trans.x >= 0 && (int)guy->trans.x < game->screen.win_w
			&& is_in_front
			&& game->hits[(int)guy->trans.x].dist > guy->trans.y))
		return (true);
	return (false);
}

void	correct_entity_position(t_game *game, t_pos *new, t_pos old)
{
	if (new->x < 1 || new->x > game->map.width - 1
		|| new->y < 1 || new->y > game->map.height - 1)
		*new = old;
}
