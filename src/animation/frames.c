/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 15:51:39 by ikulik            #+#    #+#             */
/*   Updated: 2025/08/30 16:07:47 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			&(frame->width), &(frame->endian));
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
	anim->num_fr = anim->img.width / anim->img.height;
	anim->frames = ft_calloc(anim->num_fr, sizeof(t_img));
	if (anim->frames == NULL)
		close_game(game);
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
		close_game(game);
	copy->num_fr = proto->num_fr;
	copy->last_frame = game->screen.last_frame_time;
	while (index < proto->num_fr)
	{
		copy->frames[index] = &(proto->frames[index]);
		index++;
	}
}
