/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:49:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/19 17:01:34 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	initialize_data( t_mlx_data *data)
{
	ft_bzero(data, sizeof(t_mlx_data));
	data->screen.win_h = WIN_HEIGHT;
	data->screen.win_w = WIN_WIDTH;
	data->screen.half_w = WIN_WIDTH / 2;
}
