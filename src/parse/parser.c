/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtrofyme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 12:17:44 by vtrofyme          #+#    #+#             */
/*   Updated: 2025/08/22 00:27:13 by vtrofyme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	int count = 0;
	char *line;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, "Cannot open .cub file", MAP_ERROR);
	line = get_next_line(fd);
	while (line)
	{
		char *trimmed = ft_strtrim(line, " \n");
		free(line);
		line = trimmed;
		if (is_map_line(line))
			count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

int parse_cub(t_game *game, char *path)
{
	int		fd;
	char	*line;
	char	**map_lines;
	int		map_count;
	int		total_map_lines;
	char	*trimmed;
	int		i;

	map_count = 0;
	total_map_lines = count_map_lines(game, path);
	map_lines = malloc(sizeof(char *) * (total_map_lines + 1));
	if (!map_lines)
		clean_exit(game, "Malloc failed", MAP_ERROR);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		clean_exit(game, "Cannot open .cub file", MAP_ERROR);
	line = get_next_line(fd);
	while (line)
	{
		trimmed = ft_strtrim(line, " \n");
		free(line);
		line = trimmed;
		if (ft_strncmp(line, "NO", 2) == 0)
			load_texture(game, skip_spaces(line + 2), &game->texts.wall_n);
		else if (ft_strncmp(line, "SO", 2) == 0)
			load_texture(game, skip_spaces(line + 2), &game->texts.wall_s);
		else if (ft_strncmp(line, "WE", 2) == 0)
			load_texture(game, skip_spaces(line + 2), &game->texts.wall_w);
		else if (ft_strncmp(line, "EA", 2) == 0)
			load_texture(game, skip_spaces(line + 2), &game->texts.wall_e);
		else if (ft_strncmp(line, "F", 1) == 0)
			game->texts.bot_color = parse_rgb(game, skip_spaces(line + 1));
		else if (ft_strncmp(line, "C", 1) == 0)
			game->texts.top_color = parse_rgb(game, skip_spaces(line + 1));
		else if (is_map_line(line))
			map_lines[map_count++] = line;
		else
		{
			free(line);
			free(map_lines);
			clean_exit(game, "Invalid line in .cub", MAP_ERROR);
		}
		line = get_next_line(fd);
	}
	close(fd);
	parse_map_lines(game, map_lines, map_count);
	i = 0;
	while (i < map_count)
		free(map_lines[i++]);
	free(map_lines);
	return (0);
}
