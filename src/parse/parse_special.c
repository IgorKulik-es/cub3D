/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_special.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 17:40:16 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/28 13:59:59 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	initialize_door(t_game *game, int row, int column, int ind_door);

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

	ind_line = 1;
	ind_door = 0;
	while (ind_line < game->map.height)
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
		ind_line++;
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
