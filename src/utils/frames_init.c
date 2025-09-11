/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:51:39 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 18:22:12 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	create_screen(t_game *game)
{
	t_screen	*screen;
	int			dummy;

	screen = &(game->screen);
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "cub3D");
	screen->img = mlx_new_image(game->mlx, screen->win_w, screen->win_h);
	screen->pixels = (int *)mlx_get_data_addr(screen->img,
			&dummy, &dummy, &dummy);
	game->scr_upscaled.img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	game->scr_upscaled.addr = (int *)mlx_get_data_addr(game->scr_upscaled.img,
			&(game->scr_upscaled.bpp), &(game->scr_upscaled.line_length),
			&(game->scr_upscaled.endian));
	game->scr_upscaled.width = WIN_WIDTH;
	game->scr_upscaled.height = WIN_HEIGHT;
}

void	get_frame(t_game *game, t_anim_p *anim, int ind_frame)
{
	int		pix_orig;
	int		column;
	int		row;
	t_img	*frame;

	row = -1;
	frame = &(anim->frames[ind_frame]);
	pix_orig = anim->img.height * ind_frame;
	frame->img = mlx_new_image(game->mlx, anim->img.height, anim->img.height);
	frame->addr = (int *)mlx_get_data_addr(frame->img, &(frame->bpp),
			&(frame->line_length), &(frame->endian));
	frame->height = anim->img.height;
	frame->width = frame->height;
	while (++row < anim->img.height)
	{
		column = -1;
		while (++column < anim->img.height)
		{
			frame->addr[row * frame->height + column]
				= anim->img.addr[pix_orig];
			pix_orig++;
		}
		pix_orig += anim->img.height * (anim->num_fr - 1);
	}
}

void	set_anim_frames(t_game *game, t_anim_p *anim)
{
	int	ind_frame;

	ind_frame = 0;
	if (anim->img.height != 0)
		anim->num_fr = anim->img.width / anim->img.height;
	else
		clean_exit(game, "animation file error", EXIT_FAILURE);
	anim->frames = ft_calloc(anim->num_fr, sizeof(t_img));
	if (anim->frames == NULL)
		clean_exit(game, "malloc", EXIT_FAILURE);
	while (ind_frame < anim->num_fr)
	{
		get_frame(game, anim, ind_frame);
		anim->frames[ind_frame].width /= anim->frames[ind_frame].bpp;
		ind_frame++;
	}
}

void	copy_anim(t_game *game, t_anim_p *proto, t_anim *copy)
{
	int	index;

	index = 0;
	copy->frames = malloc (proto->num_fr * sizeof(t_img *));
	if (copy->frames == NULL)
		clean_exit(game, "malloc", EXIT_FAILURE);
	copy->num_fr = proto->num_fr;
	copy->last_frame = game->screen.last_frame_time;
	copy->time_per_frame = (float)P_ANIM_SPEED / copy->num_fr;
	while (index < proto->num_fr)
	{
		copy->frames[index] = &(proto->frames[index]);
		index++;
	}
}

void	setup_textures(t_game *game)
{
	int		size;

	size = game->screen.win_w / WIN_UI_SCALE;
	if (game->texts.hp.img != NULL)
		resize_texture(game, &game->texts.hp, size, size);
	if (game->texts.bans.img[INTRO].img)
		stretch_to_screen_width(game, &(game->texts.bans.img[INTRO]));
	if (game->texts.bans.img[WIN].img)
		stretch_to_screen_width(game, &(game->texts.bans.img[WIN]));
	if (game->texts.bans.img[LOSE].img)
		stretch_to_screen_width(game, &(game->texts.bans.img[LOSE]));
	if (game->texts.bans.img[LOSE].img != NULL)
		game->texts.draw_mode |= M_GAME_OVER_PL;
	if (game->texts.bans.img[WIN].img != NULL)
		game->texts.draw_mode |= M_VICTORY_PL;
	if (game->texts.bans.img[INTRO].img != NULL)
		game->texts.draw_mode |= M_INTRO_PL;
	if (game->texts.ceiling.img != NULL)
		game->texts.draw_mode += M_CEIL_TEXTURE;
	if (game->texts.floor.img != NULL)
		game->texts.draw_mode += M_FL_TEXTURE;
	if (game->texts.hp.img != NULL)
		game->texts.draw_mode |= M_VISIBLE_HP;
}
