/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:40:16 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/30 15:11:53 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	initialize_door(t_game *game, int row, int column, int ind_door);

int	count_items(t_game *game, char item)
{
	int	ind_line;
	int	ind_col;
	int	result;

	ind_line = 1;
	result = 0;
	while (ind_line < game->map.height)
	{
		ind_col = 0;
		while (ind_col < game->map.width)
		{
			if (game->map.map[ind_line][ind_col] == item)
				result++;
			ind_col++;
		}
		ind_line++;
	}
	return (result);
}

void	add_doors(t_game *game)
{
	int	ind_line;
	int	ind_col;
	int	ind_door;

	ind_line = 0;
	ind_door = 0;
	game->num_doors = count_items(game, 'D');
	if (game->num_doors == 0)
		return ;
	game->doors = ft_calloc(game->num_doors, sizeof(t_door));
	if (game->doors == NULL)
		close_game(game);
	while (++ind_line < game->map.height)
	{
		ind_col = 0;
		while (ind_col < game->map.width - 1)
		{
			if (game->map.map[ind_line][ind_col] == 'D')
			{
				if (initialize_door(game, ind_line, ind_col, ind_door))
					ind_door++;
			}
			ind_col++;
		}
	}
}

bool	initialize_door(t_game *game, int row, int column, int ind_door)
{
	if (game->map.map[row - 1][column] == '1'
		&& game->map.map[row + 1][column] == '1')
		game->doors[ind_door].type = D_TYPE_VERT;
	else if (game->map.map[row][column - 1] == '1'
		&& game->map.map[row][column + 1] == '1')
		game->doors[ind_door].type = D_TYPE_HOR;
	else
	{
		game->map.map[row][column] = '1';
		(game->num_doors)--;
		return (false);
	}
	game->doors[ind_door].x = column;
	game->doors[ind_door].y = row;
	game->doors[ind_door].state = D_STATE_CLOSED;
	game->doors[ind_door].width = 1;
	game->doors[ind_door].last_open = game->screen.last_frame_time;
	return (true);
}
