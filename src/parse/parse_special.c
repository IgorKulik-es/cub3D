/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:40:16 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/28 12:19:09 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	count_doors(t_game *game)
{
	int	ind_line;
	int	ind_col;

	ind_line = 1;
	game->num_doors = 0;
	while (ind_line < game->map.height)
	{
		ind_col = 0;
		while (ind_col < game->map.width)
		{
			if (game->map.map[ind_line][ind_col] == 'D')
				(game->num_doors)++;
			ind_col++;
		}
		ind_line++;
	}
	if (game->num_doors > 0)
	{
		game->doors = malloc (game->num_doors * sizeof(t_door));
		if (game->doors == NULL)
			close_game(game);
		ft_bzero(game->doors, game->num_doors * sizeof (t_door));
	}
}

void	add_doors(t_game *game)
{
	int	ind_line;
	int	ind_col;
	int	ind_door;

	ind_line = 0;
	ind_door = 0;
	while (++ind_line < game->map.height)
	{
		ind_col = 0;
		while (ind_col < game->map.width)
		{
			if (game->map.map[ind_line][ind_col] == 'D')
			{
				game->doors[ind_door].x = ind_col;
				game->doors[ind_door].y = ind_line;
				if (game->map.map[ind_line - 1][ind_col] == '1')
					game->doors[ind_door].type = D_TYPE_VERT;
				game->doors[ind_door].state = 1;
				game->doors[ind_door].width = 1;
				game->doors[ind_door].last_open = game->screen.last_frame_time;
				ind_door++;
			}
			ind_col++;
		}
	}
}
