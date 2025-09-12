/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_moves.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:21:41 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/12 11:54:21 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static bool	check_entity_collision(t_game *game, t_entity *guy, t_pos new);
static void	detect_player(t_game *game, t_entity *guy);
static void	check_player_visibility(t_game *game, t_entity *guy);

void	move_enemy(t_game *game, t_entity *guy)
{
	t_pos	new;
	float	step;

	guy->trans = dist_to_entity(game, guy);
	check_player_visibility(game, guy);
	guy->is_ent_visible = check_entity_visibility(game, guy);
	guy->turn = determine_facing(guy);
	if (!(guy->is_pl_visible) || !(guy->turn == WALK_FRONT))
		guy->is_pl_visible = false;
	detect_player(game, guy);
	if (guy->mode == ACTION)
		return ;
	step = ((get_time() - game->screen.last_frame_time) / (float)P_ENEMY_SPEED)
		* guy->state;
	new = add_vectors(guy->pos, mult_scalar(guy->face, step));
	correct_entity_position(game, &new, guy->pos);
	if (guy->state == E_STATE_ANGRY)
		guy->pos = smooth_collision(game, guy->pos, new);
	else if (check_entity_collision(game, guy, new))
		guy->pos = new;
}

static bool	check_entity_collision(t_game *game, t_entity *guy, t_pos new)
{
	t_pos	new_pos;
	t_pos	view;

	new_pos = smooth_collision(game, guy->pos, new);
	if (new_pos.x == new.x && new_pos.y == new.y)
		return (true);
	view = subtr_vectors(new, guy->pos);
	if (fabsf(view.x) > 0)
	{
		view.y = (view.x > 0) - (view.x <= 0);
		view.x = 0;
	}
	else
	{
		view.x = (view.y < 0) - (view.y >= 0);
		view.y = 0;
	}
	guy->face = view;
	return (true);
}

static void	detect_player(t_game *game, t_entity *guy)
{
	if (guy->is_pl_visible)
	{
		if (guy->dist < E_DET_RADIUS && game->game_stage == PLAY)
			guy->state = E_STATE_ANGRY;
		else if (guy->dist > 2 * E_DET_RADIUS && guy->state == E_STATE_ANGRY)
			calm_down_enemy(guy);
	}
	if (guy->state == E_STATE_ANGRY)
		guy->face = mult_scalar(guy->view, -1 / guy->dist);
}

void	calm_down_enemy(t_entity *guy)
{
	guy->face.x = -(guy->face.x > 0) + (guy->face.x < 0);
	guy->face.y = -(guy->face.y > 0) + (guy->face.y < 0);
	if (fabsf(guy->face.x) > fabsf(guy->face.y))
		guy->face.y = 0;
	else
		guy->face.x = 0;
	guy->state = E_STATE_CALM;
}

static void	check_player_visibility(t_game *game, t_entity *guy)
{
	t_ray	ray;
	t_hit	hit;
	t_pos	hit_vector;

	guy->is_pl_visible = false;
	ft_bzero(&ray, sizeof(t_ray));
	ray.view = mult_scalar(guy->view, -1.0f / guy->dist);
	calculate_steps(&ray);
	find_intersects(game, guy->pos, &ray);
	if (ray.step_x.x < -__FLT_EPSILON__ || ray.step_y.x < -__FLT_EPSILON__)
		find_collision_neg_x(game, &ray, &hit);
	else
		find_collision_pos_x(game, &ray, &hit);
	hit_vector = subtr_vectors(hit.point, guy->pos);
	if (fabsf(hit_vector.x) > fabsf(guy->view.x)
		|| fabsf(hit_vector.y) > fabsf(guy->view.y))
		guy->is_pl_visible = true;
}
