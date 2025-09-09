/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:17:44 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/09/09 15:24:30 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	handle_line_2(t_game *game, t_parse_ctx *ctx)
{
	if (ft_strncmp(ctx->line, "QA", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->enemy_prot.action.img, ctx);
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
		parser_error(game, ctx, "Invalid line in .cub");
}

static void	handle_line(t_game *game, t_parse_ctx *ctx)
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
			&game->enemy_prot.walk_front.img, ctx);
	else if (ft_strncmp(ctx->line, "QB", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&game->enemy_prot.walk_back.img, ctx);
	else if (ft_strncmp(ctx->line, "PG", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&(game->texts.bans.img[LOSE]), ctx);
	else if (ft_strncmp(ctx->line, "PW", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&(game->texts.bans.img[WIN]), ctx);
	else if (ft_strncmp(ctx->line, "PI", 2) == 0)
		load_texture(game, skip_spaces(ctx->line + 2),
			&(game->texts.bans.img[INTRO]), ctx);
	else
		handle_line_2(game, ctx);
}

static void	parse_textures_and_colors(t_game *game, int fd, t_parse_ctx *ctx)
{
	char	*trimmed;

	ctx->line = get_next_line(fd);
	while (ctx->line && !is_map_start(ctx->line))
	{
		trimmed = ft_strtrim(ctx->line, " \n");
		free(ctx->line);
		ctx->line = trimmed;
		if (ctx->line[0] == '\0')
		{
			free(ctx->line);
			ctx->line = get_next_line(fd);
			continue ;
		}
		handle_line(game, ctx);
		free(ctx->line);
		ctx->line = get_next_line(fd);
	}
}

static void	read_map_lines(int fd, t_parse_ctx *ctx)
{
	while (ctx->line)
	{
		ctx->map_lines[ctx->map_count++] = ctx->line;
		ctx->line = get_next_line(fd);
	}
}

int	parse_cub(t_game *game, char *path)
{
	t_parse_ctx	ctx;
	int			fd;
	int			total_map_lines;

	ctx.map_count = 0;
	total_map_lines = count_map_lines(game, path);
	ctx.map_lines = malloc(sizeof(char *) * total_map_lines);
	if (!ctx.map_lines)
		clean_exit(game, "Malloc failed", MAP_ERROR);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parser_error(game, &ctx, "Cannot open .cub file");
	parse_textures_and_colors(game, fd, &ctx);
	read_map_lines(fd, &ctx);
	close(fd);
	parse_map_lines(game, &ctx);
	validate_map(game, &ctx);
	clean_double_array(ctx.map_lines, ctx.map_count);
	return (0);
}
