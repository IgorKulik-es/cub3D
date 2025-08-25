/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/23 15:31:15 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/25 13:06:34 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	put_trapezoid_pixel(t_screen *screen, t_img *texture, t_trapz *trpz,
	int *index_vert);

void	put_tapezoid_to_img(t_screen *screen, t_img *texture, t_trapz trpz)
{
	int	index_src;

	trpz.top_pixel = trpz.y;
	trpz.bot_pixel = trpz.y + trpz.left_height;
	trpz.last_pxl_right = trpz.x + trpz.width;
	trpz.step_screen = (trpz.right_height - trpz.left_height)
		/ (float)(trpz.width);
	trpz.i_screen = trpz.x;
	trpz.x_texture = texture->width * trpz.edge_left;
	trpz.step_width = (1.0f / trpz.width) * trpz.hor_portion * texture->width;
	while (trpz.i_screen <= trpz.last_pxl_right)
	{
		index_src = ((int)trpz.top_pixel) * screen->win_w + trpz.i_screen;
		trpz.y_texture = trpz.edge_top;
		trpz.step_height = (1.0f / (trpz.bot_pixel - trpz.top_pixel))
			* trpz.vert_portion * texture->height;
		while (index_src < ((int)trpz.bot_pixel) * screen->win_w)
			put_trapezoid_pixel(screen, texture, &trpz, &index_src);
		(trpz.i_screen)++;
		trpz.x_texture += trpz.step_width;
		trpz.top_pixel -= trpz.step_screen;
		trpz.bot_pixel += trpz.step_screen;
	}
}

void	put_trapezoid_pixel(t_screen *screen, t_img *texture, t_trapz *trpz,
	int *index_vert)
{
	screen->pixels[*index_vert] = texture->addr[(int)trpz->x_texture
		+ ((int)trpz->y_texture) * texture->width];
	*index_vert += screen->win_w;
	trpz->y_texture += trpz->step_height;
}
