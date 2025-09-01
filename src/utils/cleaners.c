/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/01 20:01:57 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_entities(t_game *game);
static void	free_textures(t_game *game);

int	close_game(t_game *data)
{
	mlx_do_key_autorepeaton(data->mlx);
	if (data->screen.img)
		mlx_destroy_image(data->mlx, data->screen.img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	clean_exit(data, "OK", 0);
	return (0);
}

void	clean_exit(t_game *game, char *error, int exit_code)
{
	if (exit_code != 0)
	{
		if (exit_code == EXIT_FAILURE)
			write(2, "cube3D: ", 8);
		if (exit_code == MAP_ERROR)
			write(2, "Error: ", 7);
		if (error)
			write(2, error, ft_strlen(error));
		write(2, "\n", 1);
	}
	free_textures(game);
	free_entities(game);
	if (game->map.map)
		clean_double_array(game->map.map, game->map.height);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (game->doors)
		free(game->doors);
	exit(exit_code);
}

static void	free_textures(t_game *game)
{
	int	index;

	index = -1;
	free_texture(game->mlx, &(game->texts.wall_n));
	free_texture(game->mlx, &(game->texts.wall_s));
	free_texture(game->mlx, &(game->texts.wall_w));
	free_texture(game->mlx, &(game->texts.wall_e));
	free_texture(game->mlx, &(game->texts.door));
	free_texture(game->mlx, &(game->enemy_prot.action.img));
	free_texture(game->mlx, &(game->enemy_prot.walk_back.img));
	free_texture(game->mlx, &(game->enemy_prot.walk_front.img));
	while (++index < game->enemy_prot.action.num_fr
		&& game->enemy_prot.action.frames != NULL)
		free_texture(game->mlx, &(game->enemy_prot.action.frames[index]));
	index = -1;
	while (++index < game->enemy_prot.action.num_fr
		&& game->enemy_prot.walk_back.frames != NULL)
		free_texture(game->mlx, &(game->enemy_prot
				.walk_back.frames[index]));
	index = -1;
	while (++index < game->enemy_prot.action.num_fr
		&& game->enemy_prot.walk_front.frames != NULL)
		free_texture(game->mlx, &(game->enemy_prot
				.walk_front.frames[index]));
}

static void	free_entities(t_game *game)
{
	int	ind_ent;
	int	ind_anim;

	ind_ent = 0;
	if (game->enemies == NULL)
		return ;
	while (ind_ent < game->num_enemies)
	{
		ind_anim = 0;
		while (ind_anim < NUM_ANIM)
		{
			safe_free((void **)&game->enemies[ind_ent].anims[ind_anim].frames);
			ind_anim++;
		}
		ind_ent++;
	}
	safe_free((void **)&game->enemy_prot.action.frames);
	safe_free((void **)&game->enemy_prot.walk_back.frames);
	safe_free((void **)&game->enemy_prot.walk_front.frames);
	safe_free((void **)&(game->enemies));
}
