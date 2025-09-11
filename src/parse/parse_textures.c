/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 20:35:50 by ikulik            #+#    #+#             */
/*   Updated: 2025/09/11 21:19:28 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	handle_line_3(t_game *game, t_parse_ctx *ctx);
static void	handle_line_2(t_game *game, t_parse_ctx *ctx);
static void	handle_color_line(t_game *game, t_parse_ctx *ctx);
static void	load_texture(t_game *game, char *path,
				t_img *dest, t_parse_ctx *ctx);

void	handle_line(t_game *game, t_parse_ctx *ctx)
{
	if (ft_strncmp(ctx->line, "NO", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.wall_n, ctx);
	else if (ft_strncmp(ctx->line, "SO", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.wall_s, ctx);
	else if (ft_strncmp(ctx->line, "WE", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.wall_w, ctx);
	else if (ft_strncmp(ctx->line, "EA", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.wall_e, ctx);
	else if (ft_strncmp(ctx->line, "DR", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.door, ctx);
	else if (ft_strncmp(ctx->line, "QF", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->anim_prot.walk_front.img, ctx);
	else if (ft_strncmp(ctx->line, "QB", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->anim_prot.walk_back.img, ctx);
	else
		handle_line_2(game, ctx);
}

static void	handle_line_2(t_game *game, t_parse_ctx *ctx)
{
	if (ft_strncmp(ctx->line, "QA", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->anim_prot.action.img, ctx);
	else if (ft_strncmp(ctx->line, "FL", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.floor, ctx);
	else if (ft_strncmp(ctx->line, "CE", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.ceiling, ctx);
	else if (ft_strncmp(ctx->line, "DW", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.door_w, ctx);
	else if (ft_strncmp(ctx->line, "HP", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->texts.hp, ctx);
	else if (ft_strncmp(ctx->line, "F", 1) == 0
		|| ft_strncmp(ctx->line, "C", 1) == 0)
		handle_color_line(game, ctx);
	else
		handle_line_3(game, ctx);
}

static void	handle_line_3(t_game *game, t_parse_ctx *ctx)
{
	if (ft_strncmp(ctx->line, "QL", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->anim_prot.walk_left.img, ctx);
	else if (ft_strncmp(ctx->line, "QR", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->anim_prot.walk_right.img, ctx);
	else if (ft_strncmp(ctx->line, "PG", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&(game->texts.bans.img[LOSE]), ctx);
	else if (ft_strncmp(ctx->line, "PW", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&(game->texts.bans.img[WIN]), ctx);
	else if (ft_strncmp(ctx->line, "PI", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&(game->texts.bans.img[INTRO]), ctx);
	else if (ft_strncmp(ctx->line, "EX", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&(game->anim_prot.exit.img), ctx);
	else
		parser_error(game, ctx, "Invalid line in .cub");
}

static void	load_texture(t_game *game, char *path,
		t_img *dest, t_parse_ctx *ctx)
{
	if (dest->img != NULL)
		parser_error(game, ctx, "Texture redefined");
	dest->img = mlx_xpm_file_to_image(game->mlx, path,
			&dest->width, &dest->height);
	if (!dest->img)
		parser_error(game, ctx, "Texture load failed");
	dest->addr = (int *)mlx_get_data_addr(dest->img, &(dest->bpp),
			&(dest->line_length), &(dest->endian));
}

static void	handle_color_line(t_game *game, t_parse_ctx *ctx)
{
	if (ft_strncmp(ctx->line, "F", 1) == 0)
		game->texts.bot_color = parse_rgb(game, ctx);
	else if (ft_strncmp(ctx->line, "C", 1) == 0)
		game->texts.top_color = parse_rgb(game, ctx);
}
