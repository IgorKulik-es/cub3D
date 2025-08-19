/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:25:53 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/19 20:10:22 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3D.h"

void	create_dummy_map(t_mlx_data *data)
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
		data->map.map[i][data->map.width -1] = '1';
		j = 1;
		while (j < data->map.width - 1)
		{
			data->map.map[i][j] = '0';
			j++;
		}
		i++;
	}
	data->player.facing.x = 1.0f;
	data->player.facing.y = 0.0f;
	data->player.pos.x = 10.5f;
	data->player.pos.y = 10.5f;
	data->player.camera.x = 0.0f;
	data->player.camera.y = 1.0f;
}
