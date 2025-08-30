/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:49:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/22 15:19:45 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	initialize_data(t_game *data)
{
	ft_bzero(data, sizeof(t_game));
	data->screen.win_h = WIN_HEIGHT;
	data->screen.win_w = WIN_WIDTH;
	data->screen.half_w = WIN_WIDTH / 2;
	data->screen.last_frame_time = get_time();
	data->player.moving = 0;
	data->player.rotating = 0;
	data->player.inv_det = 1.0f / P_POV;
}
