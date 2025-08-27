/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/27 09:46:27 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/27 11:45:17 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || (*str >= 9 && *str <= 13)))
		str++;
	return (str);
}

void	load_texture(t_game *game, char *path, t_img *dest, t_parse_ctx *ctx)
{
	dest->img = mlx_xpm_file_to_image(game->mlx, path,
			&dest->width, &dest->height);
	if (!dest->img)
		parser_error(game, ctx, "Texture load failed");
	dest->addr = (int *)mlx_get_data_addr(dest->img, &(dest->bpp),
			&(dest->line_length), &(dest->endian));
}

void	handle_color_line(t_game *game, t_parse_ctx *ctx)
{
	if (ft_strncmp(ctx->line, "F", 1) == 0)
		game->texts.bot_color = parse_rgb(game, ctx);
	else if (ft_strncmp(ctx->line, "C", 1) == 0)
		game->texts.top_color = parse_rgb(game, ctx);
}

static void	validate_cell(t_game *game, t_parse_ctx *ctx, int x, int y)
{
	char	c;

	c = game->map.map[y][x];
	if (c != '1' && c != '0' && c != 'N' && c != 'S'
		&& c != 'E' && c != 'W' && c != ' ' && c != '\n')
	{
		clean_double_array(ctx->map_lines, ctx->map_count);
		clean_exit(game, "Invalid character in map", MAP_ERROR);
	}
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		if (y == 0 || x == 0 || y == game->map.height - 1
			|| x == game->map.width - 1)
		{
			clean_double_array(ctx->map_lines, ctx->map_count);
			clean_exit(game, "Map not closed at border", MAP_ERROR);
		}
		if (game->map.map[y - 1][x] == ' ' || game->map.map[y + 1][x] == ' '
			|| game->map.map[y][x - 1] == ' ' || game->map.map[y][x + 1] == ' ')
		{
			clean_double_array(ctx->map_lines, ctx->map_count);
			clean_exit(game, "Map not closed near space", MAP_ERROR);
		}
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
