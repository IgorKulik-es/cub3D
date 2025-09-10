/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikulik <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:46:27 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/09/10 14:31:10 by ikulik           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	return (str);
}

static void	check_neighbors(t_game *g, t_parse_ctx *ctx, int x, int y)
{
	if (g->map.map[y - 1][x] == ' ' || g->map.map[y + 1][x] == ' '
		|| g->map.map[y][x - 1] == ' ' || g->map.map[y][x + 1] == ' '
		|| g->map.map[y - 1][x] == '\n' || g->map.map[y + 1][x] == '\n'
		|| g->map.map[y][x - 1] == '\n' || g->map.map[y][x + 1] == '\n')
	{
		clean_double_array(ctx->map_lines, ctx->map_count);
		clean_exit(g, "Map not closed near space", MAP_ERROR);
	}
}

static void	validate_cell(t_game *g, t_parse_ctx *ctx, int x, int y)
{
	char	c;

	c = g->map.map[y][x];
	if (c != '1' && c != '0' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ' && c != '\n'
		&& c != 'D' && c != 'Q' && c != 'X')
	{
		clean_double_array(ctx->map_lines, ctx->map_count);
		clean_exit(g, "Invalid character in map", MAP_ERROR);
	}
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W' || c == 'D')
	{
		if (y == 0 || x == 0 || y == g->map.height - 1 || x == g->map.width - 1)
		{
			clean_double_array(ctx->map_lines, ctx->map_count);
			clean_exit(g, "Map not closed at border", MAP_ERROR);
		}
		check_neighbors(g, ctx, x, y);
	}
}

void	validate_map(t_game *game, t_parse_ctx *ctx)
{
	int	y;
	int	x;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (x < game->map.width)
		{
			validate_cell(game, ctx, x, y);
			x++;
		}
		y++;
	}
}
