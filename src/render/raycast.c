/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:30:07 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/05 20:01:40 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

static void	calculate_steps(t_game *game, t_ray *ray, float column);
static char	get_hit_type(t_game *game, t_ray *ray, t_pos point);
static bool	check_inside_door(t_game *game, t_pos point);
static void	find_intersects(t_game *game, t_pos player, t_ray *ray);

t_hit	cast_ray(t_game *game, float column)
{
	t_ray	ray;
	t_hit	hit;
	t_pos	vector;

	calculate_steps(game, &ray, column);
	find_intersects(game, game->player.pos, &ray);
	if (ray.step_x.x < -__FLT_EPSILON__ || ray.step_y.x < -__FLT_EPSILON__)
		find_collision_neg_x(game, &ray, &hit);
	else
		find_collision_pos_x(game, &ray, &hit);
	hit.type = get_hit_type(game, &ray, hit.point);
	if (ray.obst == '1')
		hit.column = hit.point.x - floor(hit.point.x)
			+ hit.point.y - floor(hit.point.y);
	vector = subtr_vectors(hit.point, game->player.pos);
	if (fabsf(ray.view.x - 0.0f) > __FLT_EPSILON__)
		hit.dist = vector.x / ray.view.x;
	else
		hit.dist = vector.y / ray.view.y;
	return (hit);
}

static void	calculate_steps(t_game *game, t_ray *ray, float column)
{
	ray->view = mult_scalar(game->player.camera, 2 * column
			/ game->screen.win_w - 1.0f);
	ray->view = add_vectors(ray->view, game->player.facing);
	ray->step_x.y = 0;
	ray->step_x.x = 0;
	ray->step_y.x = 0;
	ray->step_y.y = 0;
	if (fabsf(ray->view.x - 0.0f) > __FLT_EPSILON__)
		ray->step_x = mult_scalar(ray->view, 1.0f / fabsf(ray->view.x));
	if (fabsf(ray->view.y - 0.0f) > __FLT_EPSILON__)
		ray->step_y = mult_scalar(ray->view, 1.0f / fabsf(ray->view.y));
}

static void	find_intersects(t_game *game, t_pos player, t_ray *ray)
{

	ray->start_x.x = floor(player.x) + (ray->view.x > 0);
	ray->start_y.y = floor(player.y) + (ray->view.y > 0);
	if (fabs(ray->view.x - 0.0f) > __FLT_EPSILON__)
		ray->start_x.y = ((ray->start_x.x - player.x) / ray->view.x)
			* ray->view.y + player.y;
	else
	{
		ray->start_x.y = game->map.height;
		ray->start_x.x = game->map.width;
	}
	if (fabs(ray->view.y - 0.0f) > __FLT_EPSILON__)
		ray->start_y.x = ((ray->start_y.y - player.y) / ray->view.y)
			* ray->view.x + player.x;
	else
	{
		ray->start_y.y = game->map.height;
		ray->start_y.x = game->map.width * (ray->view.x > 0);
	}
}

static char	get_hit_type(t_game *game, t_ray *ray, t_pos point)
{
	if (ray->obst != '1')
		return (ray->obst);
	if (check_inside_door(game, point))
		return (DOOR_WALL);
	if (fabsf(point.y - roundf(point.y)) < __FLT_EPSILON__)
	{
		if (ray->view.y > 0)
			return ('N');
		else
			return ('S');
	}
	else if (ray->view.x > 0)
		return ('W');
	return ('E');
}

static bool	check_inside_door(t_game *game, t_pos point)
{
	t_coords	hit_pos;
	int			diff;

	if (game->map.map[game->player.tile.y][game->player.tile.x] == 'D')
	{
		hit_pos.x = floorf(point.x);
		hit_pos.y = floorf(point.y);
		diff = abs(game->player.tile.x - hit_pos.x);
		diff += abs(game->player.tile.y - hit_pos.y);
		if (diff <= 1 && (game->map.map[hit_pos.y][hit_pos.x] == '1'
			|| game->map.map[hit_pos.y][hit_pos.x] == 'D'))
			return (true);
	}
	return (false);
}
