/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_scaling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:47:11 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/08 16:50:05 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_img	make_new_image(t_game *game, int width, int height, t_pos *old);

void	resize_texture(t_game *game, t_img *img, int new_width, int new_height)
{
	t_img		new_img;
	t_pos		step;
	t_pos		old_pos;
	t_coords	pixels;
	int			max_pixel;

	new_img = make_new_image(game, new_width, new_height, &old_pos);
	step.x = img->width / (float)new_width;
	step.y = img->height / (float)new_height;
	pixels.x = -1;
	max_pixel = new_width * new_height;
	while (pixels.x < max_pixel)
	{
		pixels.y = -1;
		old_pos.x = 0;
		while (++(pixels.y) < new_width)
		{
			new_img.addr[++(pixels.x)] = img->addr[((int)old_pos.y) * img->width
				+ (int)old_pos.x];
			old_pos.x += step.x;
		}
		old_pos.y += step.y;
	}
	mlx_destroy_image(game->mlx, img->img);
	*img = new_img;
}

static t_img	make_new_image(t_game *game, int width, int height, t_pos *old)
{
	t_img		new_img;

	new_img.img = mlx_new_image(game->mlx, width, height);
	new_img.addr = (int *)mlx_get_data_addr(new_img.img, &(new_img.bpp),
			&(new_img.line_length), &(new_img.endian));
	new_img.width = width;
	new_img.height = height;
	*old = (t_pos){0, 0};
	return (new_img);
}

void	stretch_to_screen_width(t_game *game, t_img *img)
{
	int	new_height;

	new_height = ((float)img->height * game->screen.win_w) / img->width;
	resize_texture(game, img, game->screen.win_w, new_height);
}
