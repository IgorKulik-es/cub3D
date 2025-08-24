/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:17:44 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/24 21:46:30 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parser_error(t_game *game, t_parse_ctx *ctx, char *msg)
{
	if (ctx && ctx->line)
		free(ctx->line);
	if (ctx && ctx->map_lines)
		clean_double_array(ctx->map_lines, ctx->map_count);
	clean_exit(game, msg, MAP_ERROR);
}

void parse_map_lines(t_game *game, char **lines, int count)
{
	int width;
	int i;
	int x;
	int y;
	char c;

	width = 0;
	i = 0;
	while (i < count)
	{
		if ((int)ft_strlen(lines[i]) > width)
			width = ft_strlen(lines[i]);
		i++;
	}
	game->map.height = count;
	game->map.width = width;
	game->map.map = malloc(sizeof(char *) * count);
	if (!game->map.map)
		clean_exit(game, "Malloc failed", MAP_ERROR);
	y = 0;
	while (y < count)
	{
		game->map.map[y] = malloc(sizeof(char) * (width + 1));
		if (!game->map.map[y])
			clean_exit(game, "Malloc failed", MAP_ERROR);
		x = 0;
		while (x < width)
		{
			if (x < (int)ft_strlen(lines[y]))
				c = lines[y][x];
			else
				c = ' ';
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				set_player(&game->player, c, x, y);
				c = '0';
			}
			game->map.map[y][x] = c;
			x++;
		}
		game->map.map[y][width] = '\0';
		y++;
	}
}

char *skip_spaces(char *str)
{
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	return (str);
}

int count_map_lines(t_game *game, char *path)
{
	int fd;
	int count;
	char *line;

	count = 0;
	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, "Cannot open .cub file", MAP_ERROR);
	line = get_next_line(fd);
	while (line)
	{
		if (is_map_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

void	validate_map(t_game *game, char **map_lines, int map_count)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	// for (int i = 0; i < game->map.height; i++)
	// printf("'%s'\n", game->map.map[i]);
	while ( y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			c = game->map.map[y][x];
			if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
			{
				if (y == 0 || x == 0 || y == game->map.height - 1 || x == game->map.width - 1)
				{
					clean_double_array(map_lines, map_count);
					clean_exit(game, "Map not closed at border", MAP_ERROR);
				}
				if (game->map.map[y-1][x] == ' ' || game->map.map[y+1][x] == ' ' ||
					game->map.map[y][x-1] == ' ' || game->map.map[y][x+1] == ' ')
				{
					printf("x = %d, y = %d\n", x, y);
					clean_double_array(map_lines, map_count);
					clean_exit(game, "Map not closed near space", MAP_ERROR);
				}
			}
			x++;
		}
		y++;
	}
}
static void	handle_color_line(t_game *game, char *line)
{
	if (ft_strncmp(line, "F", 1) == 0)
		game->texts.bot_color = parse_rgb(game, skip_spaces(line + 1));
	else if (ft_strncmp(line, "C", 1) == 0)
		game->texts.top_color = parse_rgb(game, skip_spaces(line + 1));
}

int parse_cub(t_game *game, char *path)
{
	t_parse_ctx	ctx;
	int			fd;
	int			total_map_lines;
	char		*trimmed;

	ctx.map_count = 0;
	total_map_lines = count_map_lines(game, path);
	ctx.map_lines = malloc(sizeof(char *) * (total_map_lines));
	if (!ctx.map_lines)
		clean_exit(game, "Malloc failed", MAP_ERROR);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		parser_error(game, &ctx, "Cannot open .cub file");
	ctx.line = get_next_line(fd);
	while (ctx.line)
	{
		if (!is_map_line(ctx.line))
		{
			trimmed = ft_strtrim(ctx.line, " \n");
			free(ctx.line);
			ctx.line = trimmed;
		}
		if (ctx.line[0] == '\0')
		{
			free(ctx.line);
			ctx.line = get_next_line(fd);
			continue ;
		}
		if (ft_strncmp(ctx.line, "NO", 2) == 0)
			load_texture(game, skip_spaces(ctx.line + 2), &game->texts.wall_n, &ctx);
		else if (ft_strncmp(ctx.line, "SO", 2) == 0)
			load_texture(game, skip_spaces(ctx.line + 2), &game->texts.wall_s, &ctx);
		else if (ft_strncmp(ctx.line, "WE", 2) == 0)
			load_texture(game, skip_spaces(ctx.line + 2), &game->texts.wall_w, &ctx);
		else if (ft_strncmp(ctx.line, "EA", 2) == 0)
			load_texture(game, skip_spaces(ctx.line + 2), &game->texts.wall_e, &ctx);
			else if (ft_strncmp(ctx.line, "F", 1) == 0 || ft_strncmp(ctx.line, "C", 1) == 0)
			handle_color_line(game, ctx.line);
		else if (is_map_line(ctx.line))
		{
			ctx.map_lines[ctx.map_count++] = ctx.line;
			ctx.line = get_next_line(fd);
			continue ;
		}
		else
			parser_error(game, &ctx, "Invalid line in .cub");
		free(ctx.line);
		ctx.line = get_next_line(fd);
	}
	close(fd);
	parse_map_lines(game, ctx.map_lines, ctx.map_count);
	validate_map(game, ctx.map_lines, ctx.map_count);
	clean_double_array(ctx.map_lines, ctx.map_count);
	return (0);
}
