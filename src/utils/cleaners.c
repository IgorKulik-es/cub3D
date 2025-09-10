/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaners.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 18:54:06 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/10 14:28:55 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	free_entities(t_game *game);
static void	free_textures(t_game *game);
static void	free_anim_frames(t_game *game);
static void	free_other_anim_frames(t_game *game);

void	clean_exit(t_game *game, char *error, int exit_code)
{
	if (exit_code)
		error_message(error, exit_code);
	free_textures(game);
	free_entities(game);
	if (game->map.map)
		clean_double_array(game->map.map, game->map.height);
	if (game->screen.img)
		mlx_destroy_image(game->mlx, game->screen.img);
	if (game->scr_upscaled.img)
		mlx_destroy_image(game->mlx, game->scr_upscaled.img);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->doors)
		free(game->doors);
	mlx_do_key_autorepeaton(game->mlx);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(exit_code);
}

static void	free_textures(t_game *game)
{
	free_texture(game->mlx, &(game->texts.wall_n));
	free_texture(game->mlx, &(game->texts.wall_s));
	free_texture(game->mlx, &(game->texts.wall_w));
	free_texture(game->mlx, &(game->texts.wall_e));
	free_texture(game->mlx, &(game->texts.door));
	free_texture(game->mlx, &(game->texts.door_w));
	free_texture(game->mlx, &(game->texts.hp));
	free_texture(game->mlx, &(game->texts.floor));
	free_texture(game->mlx, &(game->texts.ceiling));
	free_texture(game->mlx, &(game->texts.bans.img[INTRO]));
	free_texture(game->mlx, &(game->texts.bans.img[WIN]));
	free_texture(game->mlx, &(game->texts.bans.img[LOSE]));
	free_texture(game->mlx, &(game->anim_prot.action.img));
	free_texture(game->mlx, &(game->anim_prot.walk_back.img));
	free_texture(game->mlx, &(game->anim_prot.walk_front.img));
	free_texture(game->mlx, &(game->anim_prot.exit.img));
	free_anim_frames(game);
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
	safe_free((void **)&game->anim_prot.action.frames);
	safe_free((void **)&game->anim_prot.walk_back.frames);
	safe_free((void **)&game->anim_prot.walk_front.frames);
	safe_free((void **)&game->anim_prot.walk_left.frames);
	safe_free((void **)&game->anim_prot.walk_right.frames);
	safe_free((void **)&game->anim_prot.exit.frames);
	safe_free((void **)&(game->enemies));
}

static void	free_anim_frames(t_game *game)
{
	int	index;

	index = -1;
	while (++index < game->anim_prot.action.num_fr
		&& game->anim_prot.action.frames != NULL)
		free_texture(game->mlx, &(game->anim_prot.action.frames[index]));
	index = -1;
	while (++index < game->anim_prot.walk_back.num_fr
		&& game->anim_prot.walk_back.frames != NULL)
		free_texture(game->mlx, &(game->anim_prot
				.walk_back.frames[index]));
	index = -1;
	while (++index < game->anim_prot.walk_front.num_fr
		&& game->anim_prot.walk_front.frames != NULL)
		free_texture(game->mlx, &(game->anim_prot
				.walk_front.frames[index]));
	index = -1;
	while (++index < game->anim_prot.walk_left.num_fr
		&& game->anim_prot.walk_left.frames != NULL)
		free_texture(game->mlx, &(game->anim_prot
				.walk_left.frames[index]));
	free_other_anim_frames(game);
}

static void	free_other_anim_frames(t_game *game)
{
	int	index;

	index = -1;
	while (++index < game->anim_prot.walk_right.num_fr
		&& game->anim_prot.walk_right.frames != NULL)
		free_texture(game->mlx, &(game->anim_prot
				.walk_right.frames[index]));
	index = -1;
	while (++index < game->anim_prot.exit.num_fr
		&& game->anim_prot.exit.frames != NULL)
		free_texture(game->mlx, &(game->anim_prot
				.exit.frames[index]));
}
