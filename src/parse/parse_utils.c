/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 14:18:34 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/27 09:54:21 by vtrofyme         ###   ########.fr       */
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

int	parse_rgb(t_game *game, char *str)
{
	int		r;
	int		g;
	int		b;
	char	**split;
	int		i;

	split = ft_split(str, ',');
	if (!split || !split[0] || !split[1] || !split[2])
		clean_exit(game, "Invalid RGB format", MAP_ERROR);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		clean_exit(game, "RGB out of range", MAP_ERROR);
	i = 0;
	while (i < 3)
		free(split[i++]);
	free(split);
	return ((r << 16) | (g << 8) | b);
}

int	is_map_start(char *line)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] != ' ' && line[i] != '0' && line[i] != '1'
			&& line[i] != 'N' && line[i] != 'S' && line[i] != 'E'
			&& line[i] != 'W')
			return (0);
		if (line[i] != ' ')
			flag = 1;
		i++;
	}
	return (flag);
}

void	set_player(t_player *p, char c, int x, int y)
{
	p->pos.x = x + 0.5f;
	p->pos.y = y + 0.5f;
	if (c == 'N')
	{
		p->facing = (t_pos){0, -1};
		p->camera = (t_pos){1, 0};
	}
	else if (c == 'S')
	{
		p->facing = (t_pos){0, 1};
		p->camera = (t_pos){-1, 0};
	}
	else if (c == 'E')
	{
		p->facing = (t_pos){1, 0};
		p->camera = (t_pos){0, 1};
	}
	else if (c == 'W')
	{
		p->facing = (t_pos){-1, 0};
		p->camera = (t_pos){0, -1};
	}
}
