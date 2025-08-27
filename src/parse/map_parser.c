/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:39:31 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/27 10:02:58 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_map_width(t_parse_ctx *ctx)
{
	int	width;
	int	i;
	int	len;

	width = 0;
	i = 0;
	while (i < ctx->map_count)
	{
		len = ft_strlen(ctx->map_lines[i]);
		if (len > width)
			width = len;
		i++;
	}
	return (width);
}

static void	alloc_map_memory(t_game *game, t_parse_ctx *ctx, int width)
{
	int	i;

	game->map.height = ctx->map_count;
	game->map.width = width;
	game->map.map = malloc(sizeof(char *) * ctx->map_count);
	if (!game->map.map)
		parser_error(game, ctx, "Malloc failed");
	i = 0;
	while (i < ctx->map_count)
		game->map.map[i++] = NULL;
}

static void	fill_map_line(t_game *game, t_parse_ctx *ctx, int y, int *pl_count)
{
	int		x;
	char	c;

	game->map.map[y] = malloc(sizeof(char) * (game->map.width + 1));
	if (!game->map.map[y])
		parser_error(game, ctx, "Malloc failed");
	x = -1;
	while (++x < game->map.width)
	{
		if (x < (int)ft_strlen(ctx->map_lines[y]))
			c = ctx->map_lines[y][x];
		else
			c = ' ';
		if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		{
			(*pl_count)++;
			if (*pl_count > 1)
				parser_error(game, ctx, "Multiple player positions found");
			set_player(&game->player, c, x, y);
			c = '0';
		}
		game->map.map[y][x] = c;
	}
	game->map.map[y][game->map.width] = '\0';
}

void	parse_map_lines(t_game *game, t_parse_ctx *ctx)
{
	int	width;
	int	y;
	int	player_count;

	player_count = 0;
	width = get_map_width(ctx);
	alloc_map_memory(game, ctx, width);
	y = 0;
	while (y < ctx->map_count)
	{
		fill_map_line(game, ctx, y, &player_count);
		y++;
	}
}

int	count_map_lines(t_game *game, char *path)
{
	int		fd;
	int		count;
	char	*line;
	int		in_map;

	count = 0;
	in_map = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, "Cannot open .cub file", MAP_ERROR);
	line = get_next_line(fd);
	while (line)
	{
		if (!in_map && is_map_start(line))
			in_map = 1;
		if (in_map)
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}
