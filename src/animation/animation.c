/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:47 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/30 18:09:38 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	overlay_entity(t_game *game, t_entity *guy, t_coords pos, int height);
void	put_anim_line(t_game *game, t_img *frame, t_coords pos, t_coords pars);

void	animate_all(t_game *game)
{
	int	index;

	index = 0;
	if (game->player.moving)
		move_player(game, game->player.moving);
	if (game->player.rotating)
		rotate_player(game, game->player.rotating);
	while (index < game->num_doors)
	{
		move_door(game, &(game->doors[index]));
		index++;
	}
	update_animation(game, &(game->enemies[0].anims[game->enemies[0].mode]));
	game->enemies[0].anims[game->enemies[0].mode].active = 1;
}

void	update_animation(t_game *game, t_anim *anim)
{
	time_t	time;

	(void)game;
	if (anim->active == false)
		return ;
	time = get_time();
	if (time - anim->last_frame > P_ANIM_SPEED / anim->num_fr)
	{
		(anim->c_frame)++;
		anim->last_frame = time;
	}
	if (anim->c_frame >= anim->num_fr)
	{
		anim->active = false;
		anim->c_frame = 0;
	}
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
	transform.y = player->inv_det
		* (view.x * player->camera.y - view.y * player->camera.x);
	transform.x = -player->inv_det
		* (view.x * player->facing.y - view.y * player->facing.x);
	mult = (transform.x / transform.y);
	result.x = (game->screen.win_w / 2) * (1 + mult);
	result.y = transform.y;
	return (result);
}

void	put_entity(t_game *game, t_entity *guy)
{
	t_coords	first_pixel;
	int			height;
	int			left_side;
	int			right_side;

	guy->trans = dist_to_entity(game, guy);
	height = game->screen.win_h / guy->trans.y;
	first_pixel.x = guy->trans.x - height / 2;
	first_pixel.y = (game->screen.win_h - height) / 2;
	left_side = first_pixel.x;
	if (left_side < 0)
		left_side = 0;
	right_side = first_pixel.x - height;
	if (right_side > game->screen.win_w)
		right_side = game->screen.win_w - 1;
	if (guy->trans.x < 0 || guy->trans.x >= game->screen.win_w)
		return ;
	if (game->dists[left_side] > guy->trans.y
		|| game->dists[(int)guy->trans.x] > guy->trans.y
		|| game->dists[right_side] > guy->trans.y)
		overlay_entity(game, guy, first_pixel, height);
}

void	overlay_entity(t_game *game, t_entity *guy, t_coords pos, int height)
{
	int			last_px_on_scr;
	t_coords	params;
	t_img		*frame;

	frame = guy->anims[guy->mode].frames[guy->anims[guy->mode].c_frame];
	last_px_on_scr = pos.x + height;
	if (last_px_on_scr >= game->screen.win_w)
		last_px_on_scr = game->screen.win_w - 1;
	params.x = pos.x;
	if (params.x < 0)
		params.x = 0;
	params.y = height;
	while (params.x < last_px_on_scr)
	{
		if (guy->trans.y < game->dists[params.x])
			put_anim_line(game, frame, pos, params);
		(params.x)++;
	}
}

void	put_anim_line(t_game *game, t_img *frame, t_coords pos, t_coords pars)
{
	t_pos	step;
	int		fr_width;
	int		pixel;
	int		last_pixel;
	int		color;

	pixel = pars.x;
	step.y = 0;
	if (pos.y > 0)
		pixel += pos.y * game->screen.win_w;
	else
		step.y = frame->height * (1 - (game->screen.win_h / (float)pars.y)) / 2;
	step.x = (frame->height / (float)pars.y) * (1 - 2 * step.y / frame->height);
	fr_width = ((pars.x - pos.x) / (float)pars.y) * frame->height;
	last_pixel = (pos.y + pars.y) * game->screen.win_w + pars.x;
	if (game->screen.win_h < pars.y)
		last_pixel = pars.x + (game->screen.win_h - 1) * game->screen.win_w;
	while (pixel < last_pixel)
	{
		color = frame->addr[fr_width + (int)step.y * frame->height];
		if (color != C_BLANK)
			game->screen.pixels[pixel] = color;
		pixel += game->screen.win_w;
		step.y += step.x;
	}
}
