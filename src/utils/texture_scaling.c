/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_scaling.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 16:47:11 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/05 17:58:33 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static t_img	make_new_square(t_game *game, int size);

t_img	resize_texture(t_game *game, t_img *img, int new_size)
{
	t_img		new_img;
	float		step;
	t_pos		old_pos;
	t_coords	pixels;
	int			max_pixel;

	new_img = make_new_square(game, new_size);
	old_pos = (t_pos){0, 0};
	step = img->width / (float)new_size;
	pixels.x = 0;
	max_pixel = new_size * new_size;
	while (pixels.x < max_pixel)
	{
		pixels.y = -1;
		old_pos.x = 0;
		while (++(pixels.y) < new_size)
		{
			new_img.addr[pixels.x] = img->addr[((int)old_pos.y) * img->width
				+ (int)old_pos.x];
			(pixels.x)++;
			old_pos.x += step;
		}
		old_pos.y += step;
	}
	return (new_img);
}

static t_img	make_new_square(t_game *game, int size)
{
	t_img		new_img;

	new_img.img = mlx_new_image(game->mlx, size, size);
	new_img.addr = (int *)mlx_get_data_addr(new_img.img, &(new_img.bpp),
			&(new_img.line_length), &(new_img.endian));
	new_img.width = size;
	new_img.height = size;
	return (new_img);
}
