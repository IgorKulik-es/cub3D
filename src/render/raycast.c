/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:30:07 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/19 20:12:23 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

int	find_intersects(t_pos view, t_pos player, t_pos *start_x, t_pos *start_y);

void	create_screen(t_mlx_data *data)
{
	t_screen	*screen;
	int			dummy;

	screen = &(data->screen);
	screen->img = mlx_new_image(data->mlx, screen->win_w, screen->win_h);
	screen->pixels = (int *)mlx_get_data_addr(screen->img,
			&dummy, &dummy, &dummy);
}

void	cast_ray(t_mlx_data *data, t_screen *screen, float x)
{
	float	mult;
	//bool	hit;
	t_pos	view;
	t_pos	start_x;
	t_pos	start_y;
	t_pos	step_x;
	t_pos	step_y;

	hit = false;
	mult = (x - screen->half_w) / screen->win_w;
	view = mult_scalar(data->player.camera, mult);
	view = add_vectors(view, data->player.facing);
	if (view.x != 0.0f)
		step_x.y = view.y / view.x;
	step_x.x = 1.0f;
	if (view.y != 0.0f)
		step_y.x = view.x / view.y;
	step_y.y = 1.0f;
	find_intersects(view, data->player.pos, &start_x, &start_y);
	//printf("start_x: %f %f, start_y: %f %f\n", start_x.x, start_x.y, start_y.x, start_y.y);
	//printf("step_x: %f %f, step_y: %f %f\n", step_x.x, step_x.y, step_y.x, step_y.y);
}

int	find_intersects(t_pos view, t_pos player, t_pos *start_x, t_pos *start_y)
{

	start_x->x = floor(player.x) + (view.x > 0);
	start_y->y = floor(player.y) + (view.y > 0);
	if (view.x != 0.0f)
		start_x->y = (start_x->x / view.x) * view.y + player.y;
	else
	{
		start_x->y = 0.0f;
		start_x->x = 0.0f;
	}
	if (view.y != 0.0f)
		start_y->x = (start_y->y / view.y) * view.x + player.x;
	else
	{
		start_y->y = 0.0f;
		start_y->x = 0.0f;
	}
	if (fabs(start_x->x - player.x) > fabs(start_y->x - player.x))
		return (FIRST_HIT_Y);
	return (FIRST_HIT_X);
}


