/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:49:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/04 20:12:37 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	initialize_data(t_game *data)
{
	ft_bzero(data, sizeof(t_game));
	data->screen.win_h = WIN_HEIGHT / WIN_UPSC_FACTOR;
	data->screen.win_w = WIN_WIDTH / WIN_UPSC_FACTOR;
	data->screen.half_w = data->screen.win_w / 2;
	data->screen.last_frame_time = get_time();
	data->player.moving = 0;
	data->player.rotating = 0;
	data->player.hp = P_BASE_HP;
	data->player.inv_det = 1.0f / P_POV;
}

void	setup_textures(t_game *game)
{
	if (game->texts.ceiling.img != NULL)
		game->texts.draw_mode |= M_CEIL_TEXTURE;
	if (game->texts.floor.img != NULL)
		game->texts.draw_mode |= M_FL_TEXTURE;
}
