/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 17:33:56 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/05 17:34:33 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	put_img_to_srceen(t_game *game, t_img *img, int x, int y)
{
	int	ind_old_pix;
	int	ind_new_pix;
	int	column;
	int	max_pixel;

	ind_new_pix = 0;
	ind_old_pix = game->screen.win_w * y + x;
	max_pixel = img->width * img->height;
	while (ind_new_pix < max_pixel)
	{
		column = 0;
		while (column < img->width)
		{
			if (img->addr[ind_new_pix] != C_BLANK)
				game->screen.pixels[ind_old_pix] = img->addr[ind_new_pix];
			ind_new_pix++;
			ind_old_pix++;
			column++;
		}
		ind_old_pix += game->screen.win_w - img->width;
	}
}
