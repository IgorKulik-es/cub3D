/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 12:49:47 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/09 18:59:04 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	render_entity(t_game *game, t_entity *guy, t_coords pos, int height);
void	put_anim_line(t_game *game, t_img *frame, t_coords pos, t_coords pars);

void	update_anim_frame(t_game *game, t_entity *guy, t_anim *anim,
	t_mode mode)
{
	time_t	time;

	(void)game;
	if (anim->active == false)
		return ;
	time = get_time() - anim->last_frame;
	if (((guy->mode != ACTION) && (time > P_ANIM_SPEED
				/ (guy->state * anim->num_fr)))
		|| (guy->mode == ACTION && time > P_ANIM_SPEED / anim->num_fr))
	{
		(anim->c_frame)++;
		anim->last_frame += time;
	}
	if (anim->c_frame >= anim->num_fr)
	{
		anim->c_frame = 0;
		if (mode == ACTION)
		{
			anim->active = false;
			if (guy->dist < E_DAM_RADIUS)
				damage_player(game, guy);
		}
	}
}

void	put_entity(t_game *game, t_entity *guy)
{
	t_coords	first_pixel;
	int			height;
	int			left_side;
	int			right_side;

	height = game->screen.win_h / guy->trans.y;
	first_pixel.x = guy->trans.x - height / 2;
	first_pixel.y = (game->screen.win_h - height) / 2;
	left_side = first_pixel.x;
	right_side = first_pixel.x + height;
	correct_pixel(game, &left_side);
	correct_pixel(game, &right_side);
	if (game->hits[left_side].dist > guy->trans.y
		|| game->hits[right_side].dist > guy->trans.y
		|| ((int)guy->trans.x >= 0 && guy->trans.x < (int)game->screen.win_w
			&& game->hits[(int)guy->trans.x].dist > guy->trans.y))
		render_entity(game, guy, first_pixel, height);
}

void	render_entity(t_game *game, t_entity *guy, t_coords pos, int height)
{
	int			last_px_on_scr;
	t_coords	params;
	t_img		*frame;

	frame = guy->anims[guy->mode].frames[guy->anims[guy->mode].c_frame];
	last_px_on_scr = pos.x + height;
	determine_animation(guy);
	if (last_px_on_scr >= game->screen.win_w)
		last_px_on_scr = game->screen.win_w - 1;
	params.x = pos.x;
	if (params.x < 0)
		params.x = 0;
	params.y = height;
	while (params.x < last_px_on_scr)
	{
		if (guy->trans.y < game->hits[params.x].dist)
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

bool	check_entity_visibility(t_game *game, t_entity *guy)
{
	guy->height = game->screen.win_h / guy->trans.y;
	guy->left_edge = guy->trans.x - guy->height / 2;
	guy->right_edge = guy->left_edge + guy->height;
	if (correct_pixel(game, &guy->left_edge)
		&& game->hits[guy->left_edge].dist > guy->trans.y)
		return (true);
	if (correct_pixel(game, &guy->right_edge)
		&& game->hits[guy->right_edge].dist > guy->trans.y)
		return (true);
	if (((int)guy->trans.x >= 0 && (int)guy->trans.x < game->screen.win_w
			&& game->hits[(int)guy->trans.x].dist > guy->trans.y))
		return (true);
	return (false);
}
