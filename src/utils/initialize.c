/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 15:49:46 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 12:44:16 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	initialize_data( t_game *data)
{
	ft_bzero(data, sizeof(t_game));
	data->screen.win_h = WIN_HEIGHT;
	data->screen.win_w = WIN_WIDTH;
	data->screen.half_w = WIN_WIDTH / 2;
}
