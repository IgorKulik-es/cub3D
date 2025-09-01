/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemies_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/30 16:07:13 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/30 17:55:49 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	initialize_enemy(t_game *game, int row, int column, int index);

void	load_enemies(t_game *game)
{
	int	ind_row;
	int	ind_column;
	int	ind_enemy;

	ind_row = 0;
	ind_enemy = 0;
	game->num_enemies = count_items(game, 'Q');
	if (game->num_enemies == 0)
		return ;
	game->enemies = ft_calloc(game->num_enemies, sizeof(t_entity));
	if (game->enemies == NULL)
		close_game(game);
	set_anim_frames(game, &(game->enemy_prot.walk_front));
	set_anim_frames(game, &(game->enemy_prot.walk_back));
	set_anim_frames(game, &(game->enemy_prot.action));
	while (ind_row < game->map.height)
	{
		ind_column = 1;
		while (ind_column < game->map.width)
		{
			if (game->map.map[ind_row][ind_column] == 'Q')
				initialize_enemy(game, ind_row, ind_column, ind_enemy);
			ind_column++;
		}
		ind_row++;
	}
}

void	initialize_enemy(t_game *game, int row, int column, int index)
{
	copy_anim(game, &(game->enemy_prot.walk_front),
		&(game->enemies[index].anims[WALK_FRONT]));
	copy_anim(game, &(game->enemy_prot.walk_back),
		&(game->enemies[index].anims[WALK_BACK]));
	copy_anim(game, &(game->enemy_prot.action),
		&(game->enemies[index].anims[ACTION]));
	game->enemies[index].face.x = (row + column) % 2;
	game->enemies[index].face.y = (row + column + 1) % 2;
	game->enemies[index].mode = WALK_FRONT;
	game->enemies[index].pos.x = column + 0.5f;
	game->enemies[index].pos.y = row + 0.5f;
}
