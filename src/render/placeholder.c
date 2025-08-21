/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:25:53 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/21 17:07:17 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	create_dummy_map(t_game *data)
{
	int	i;
	int	j;

	i = 0;
	data->map.width = 20;
	data->map.height = 20;
	data->map.map = malloc (data->map.height * sizeof(char *));
	while (i < 20)
	{
		data->map.map[i] = malloc (data->map.width * sizeof(char));
		data->map.map[i][0] = '1';
		data->map.map[i][data->map.width - 1] = '1';
		j = 1;
		while (j < data->map.width - 1)
		{
			if (i == 0 || i == data->map.height - 1)
				data->map.map[i][j] = '1';
			else
				data->map.map[i][j] = '0';
			j++;
		}
		i++;
	}
	data->map.map[1][3] = '0';
	data->map.map[3][1] = '0';
	data->player.pos.x = 1.5f;
	data->player.pos.y = 1.5f;
	data->player.facing.x = 0.0f;
	data->player.facing.y = 1.0f;
	data->player.camera.x = 1.66f;
	data->player.camera.y = 0.0f;
	data->player.camera = rotate_vector(data->player.camera, -M_PI * 0.0f);
	data->player.facing = rotate_vector(data->player.facing, -M_PI * 0.0f);
}
