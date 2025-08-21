/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:49:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 17:24:17 by ikulik           ###   ########.fr       */
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
	data->moving = 0;
}
